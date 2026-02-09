/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG && Ivan
 * @version 1
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief It creates a new game and initializes its members
 */
Status game_create(Game *game) {
  int i;

  /* Initialize the spaces array */
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  game->player_location = NO_ID;
  game->object_location = NO_ID;
  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

/**
 * @brief It destroys the game, freeing all allocated memory
 */
Status game_destroy(Game *game) {
  int i = 0;

  /* Destroy all the spaces */
  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  /* Destroy the last command */
  command_destroy(game->last_cmd);

  return OK;
}

/**
 * @brief It gets a space by its id
 */
Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

/**
 * @brief It gets the player location
 */
Id game_get_player_location(Game *game) {
  return game->player_location;
}


/**
 * @brief It sets the player location
 */
Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }

  game->player_location = id;
  return OK;
}

/**
 * @brief It gets the object location
 */
Id game_get_object_location(Game *game) {
  return game->object_location;
}


/**
 * @brief It sets the object location
 */
Status game_set_object_location(Game *game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }

  game->object_location = id;
  space_set_object(game_get_space(game, id), TRUE);

  return OK;
}

/**
 * @brief It gets the last command
 */
Command* game_get_last_command(Game *game) {
  return game->last_cmd;
}

/**
 * @brief It sets the last command
 */
Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;
  return OK;
}

/**
 * @brief It gets the finished flag
 */
Bool game_get_finished(Game *game) {
  return game->finished;
}

/**
 * @brief It sets the finished flag
 */
Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;
  return OK;
}

/**
 * @brief It prints the game information
 */
void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces:\n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int)game->object_location);
  printf("=> Player location: %d\n", (int)game->player_location);
}

