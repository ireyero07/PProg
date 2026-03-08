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


/**
 * Private functions
 */

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
Status game_reader_load(Game *game, const char *filename);


/**
 * Game_reader code
 */

/**
 * @brief It creates a game from a file
 */
Status game_reader_create_from_file(Game **game, char *filename) {
  Space *space = NULL;

  if (!game || !filename) return ERROR;

  *game = game_create();
  if (!*game) {
    return ERROR;
  }

  if (game_reader_load(*game, filename) == ERROR) {
    game_destroy(*game);
    *game = NULL;
    return ERROR;
  }

  space = game_get_space_at(*game, 0);
  if (!space) {
    game_destroy(*game);
    *game = NULL;
    return ERROR;
  }

  game_set_player_location(*game, space_get_id(space));

  return OK;
}

/**
 * @brief It loads the spaces from a file
 */
Status game_reader_load(Game *game, const char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[GDESC_LINES][GDESC_LENGTH + 1] = {""};
  char *toks = NULL;
  Id idSpace = NO_ID, idObject = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Object *object = NULL;
  Status status = OK;
  int i;

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
      idSpace = atol(toks);

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

      for(i = 0; i < GDESC_LINES; i++){
        toks = strtok(NULL, "|");
        if (toks) {
          strncpy(gdesc[i],toks,GDESC_LENGTH);
          gdesc[i][GDESC_LENGTH] = '\0';
        }
        else {
          gdesc[i][0] = '\0';
        }
      }

#ifdef DEBUG
      printf("Read: s:%ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s|%s|%s|\n",
             idSpace, name, north, east, south, west, gdesc[0],  gdesc[1], gdesc[2], gdesc[3], gdesc[4]);
#endif

      /* Create the space and add it to the game */
      space = space_create(idSpace);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        
        for(i = 0; i < GDESC_LINES; i++){
          if(gdesc[i][0] != '\0'){
            space_set_gdesc(space,gdesc[i],i);
          }
        }

        game_add_space(game, space);
      }
    } 
    /* Check if the line defines an object */
    else if (strncmp("#o:", line, 3) == 0) {

      /* Parse the space data */
      toks = strtok(line + 3, "|");
      idObject = atol(toks);

      toks = strtok(NULL, "|");
      strcpy(name, toks);

      toks = strtok(NULL, "|");
      idSpace = atol(toks);

#ifdef DEBUG
      printf("Read: o:%ld|%s|%ld\n",
             idObject, name, idSpace);
#endif

      /* Create the object and add it to the space */
      object = object_create(idObject);
      if (object != NULL) {
        object_set_name(object, name);
        game_add_object(game, object);
        space = game_get_space(game, idSpace);

        if (space) {
          space_add_object(space, idObject);
        }
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
