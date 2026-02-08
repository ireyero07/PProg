/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG && Ivan
 * @version 1
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "game_reader.h"

#define MAX_SPACES 100

/**
 * @brief Game
 *
 * This struct stores all the information related to the game state.
 */
typedef struct _Game {
  Id player_location;            /*!< Id of the space where the player is located */
  Id object_location;            /*!< Id of the space where the object is located */
  Space *spaces[MAX_SPACES];     /*!< Array of pointers to the spaces of the game */
  int n_spaces;                  /*!< Number of spaces currently in the game */
  Command *last_cmd;             /*!< Last command introduced by the player */
  Bool finished;                 /*!< Flag that indicates if the game has finished */
} Game;

/**
 * @brief It creates a new game and initializes its members
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_create(Game *game);

/**
 * @brief It destroys the game, freeing all allocated memory
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_destroy(Game *game);

/**
 * @brief It gets a space by its id
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param id the id of the space
 * @return a pointer to the space or NULL if it does not exist
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It gets the player location
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return the id of the space where the player is located
 */
Id game_get_player_location(Game *game);

/**
 * @brief It sets the player location
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param id the id of the new player location
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief It gets the object location
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return the id of the space where the object is located
 */
Id game_get_object_location(Game *game);

/**
 * @brief It sets the object location
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param id the id of the new object location
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_object_location(Game *game, Id id);

/**
 * @brief It gets the last command
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return a pointer to the last command
 */
Command* game_get_last_command(Game *game);

/**
 * @brief It sets the last command
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param command a pointer to the command
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief It gets the finished flag
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return TRUE if the game has finished or FALSE otherwise
 */
Bool game_get_finished(Game *game);

/**
 * @brief It sets the finished flag
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param finished the new value of the finished flag
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief It prints the game information
 * @author Ivan
 *
 * This function prints the information of all the spaces and the
 * current locations of the player and the object.
 *
 * @param game a pointer to the game structure
 */
void game_print(Game *game);

#endif
