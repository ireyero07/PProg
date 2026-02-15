/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG && Ivan
 * @version 1
 * @date 10-02-2026
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

  if (!game) return ERROR;

  /* Initialize the spaces array */
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  
  game->player = player_create(1);
  if (!game->player) return ERROR;

  game->object = object_create(1);
    if (!game->object) {
      player_destroy(game->player);
      return ERROR;
    }

  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

/**
 * @brief It destroys the game, freeing all allocated memory
 */
Status game_destroy(Game *game) {
  int i = 0;

  if (!game) return ERROR;

  /* Destroy all the spaces */
  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  /* Destroy the player */
  player_destroy(game->player);

  /* Destroy the object */
  object_destroy(game->object);

  /* Destroy the last command */
  command_destroy(game->last_cmd);

  return OK;
}

/**
 * @brief It gets a space by its id
 */
Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) {
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
  if (!game || !game->player)
    return NO_ID;

  return player_get_location(game->player);
}


/**
 * @brief It sets the player location
 */
Status game_set_player_location(Game *game, Id id) {
  if (!game || !game->player || id == NO_ID)
    return ERROR;

  return player_set_location(game->player, id);
}

/**
 * @brief It gets the object location
 */
Id game_get_object_location(Game *game) {
  int i;

  if (!game)
    return NO_ID;

    /* Si el jugador tiene el objeto */
  if (player_get_object(game->player) != NO_ID)
    return player_get_location(game->player);

    /* Buscar en los espacios */
  for (i = 0; i < game->n_spaces; i++) {
    if (space_get_object(game->spaces[i]) != NO_ID)
      return space_get_id(game->spaces[i]);
  }

  return NO_ID;
}

/**
 * @brief It sets the object location
 */
Status game_set_object_location(Game *game, Id id) {
  int i;
  Space *space;

    if (!game || id == NO_ID) return ERROR;

    /* 1. Remove the item from the player if they had it. */
    if (player_get_object(game->player) != NO_ID) {
        player_set_object(game->player, NO_ID);
    }

    /* 2. Remove the object from all the spaces */
    for (i = 0; i < game->n_spaces; i++) {
        if (space_get_object(game->spaces[i]) != NO_ID) {
            space_set_object(game->spaces[i], NO_ID);
        }
    }

    /* 3. Place the object in the new space */
    space = game_get_space(game, id);
    if (!space)
      return ERROR;

    space_set_object(space, object_get_id(game->object));

    return OK;
}

/**
 * @brief It gets the last command
 */
Command* game_get_last_command(Game *game) {
  if (!game) return NULL;
  
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

  player_print(game->player);
  object_print(game->object);
}

