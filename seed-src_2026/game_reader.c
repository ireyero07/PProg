/**
 * @brief It implements the game reader module
 *
 * @file game_reader.c
 * @author Ivan
 * @version 0
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "space.h"
#include "game.h"

/**
 * Private functions
 */

/**
 * @brief Adds a space to the game 
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param space a pointer to the space structure
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_add_space(Game *game, Space *space);

/**
 * @brief Gets the id of the space at a given position
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param position the position of the space
 * @return Id of the space
 */
Id game_reader_get_space_id_at(Game *game, int position);

/**
 * @brief It loads the game spaces from a file
 * @author Ivan
 *
 * This function reads a file containing the description of the spaces
 * and adds them to the game structure.
 *
 * @param game a pointer to the game structure
 * @param filename the name of the file with the spaces information
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_spaces(Game *game, const char *filename);


/**
 * Game_reader code
 */

/**
 * @brief It creates a game from a file
 */
Status game_reader_create_from_file(Game *game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_reader_get_space_id_at(game, 0));
  game_set_object_location(game, game_reader_get_space_id_at(game, 0));

  return OK;
}


/**
 * @brief Adds a space to the game
 */
Status game_reader_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

/**
 * @brief Gets the id of the space at a given position
 */
Id game_reader_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/**
 * @brief It loads the spaces from a file
 */
Status game_reader_load_spaces(Game *game, const char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;

  /* Error control */
  if (!game || !filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  /* Read the file line by line */
  while (fgets(line, WORD_SIZE, file)) {

    /* Check if the line defines a space */
    if (strncmp("#s:", line, 3) == 0) {

      /* Parse the space data */
      toks = strtok(line + 3, "|");
      id = atol(toks);

      toks = strtok(NULL, "|");
      strcpy(name, toks);

      toks = strtok(NULL, "|");
      north = atol(toks);

      toks = strtok(NULL, "|");
      east = atol(toks);

      toks = strtok(NULL, "|");
      south = atol(toks);

      toks = strtok(NULL, "|");
      west = atol(toks);

#ifdef DEBUG
      printf("Read: s:%ld|%s|%ld|%ld|%ld|%ld\n",
             id, name, north, east, south, west);
#endif

      /* Create the space and add it to the game */
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_reader_add_space(game, space);
      }
    }
  }

  /* Check read errors */
  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  return status;
}