/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG && Ivan
 * @version 1
 * @date 09-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "player.h"
#include "object.h"
#include "character.h"

typedef struct _Game Game;

/**
 * @brief It creates a new game and initializes its members
 * @author Ivan
 *
 * @return a pointer to the newly created game, or NULL if there was an error
 */
Game *game_create();

/**
 * @brief It destroys the game, freeing all allocated memory
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_destroy(Game *game);

/**
 * @brief Adds a space to the game.
 * @author Ivan
 *
 * @param game Pointer to the game.
 * @param space Pointer to the space to add.
 * @return OK if everything goes well, ERROR otherwise.
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief Gets a space by its position in the array.
 * @author Ivan
 *
 * @param game Pointer to the game.
 * @param position Position of the space.
 * @return Pointer to the space or NULL if invalid.
 */
Space *game_get_space_at(Game *game, int position);

/**
 * @brief Gets the number of spaces in the game.
 * @author Ivan
 *
 * @param game Pointer to the game.
 * @return Number of spaces.
 */
int game_get_n_spaces(Game *game);

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
 * @brief Gets the number of objects in the game.
 * @author Jian Feng
 *
 * @param game Pointer to the game.
 * @return Number of objects.
 */
int game_get_n_objects(Game *game);

/**
 * @brief It gets a object by its id
 * @author Jian Feng
 *
 * @param game a pointer to the game structure
 * @param id the id of the object
 * @return a pointer to the object or NULL if it does not exist
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief Adds an object to the game.
 * @author Ivan
 *
 * This function inserts a new object into the array of objects
 * stored in the game structure.
 * 
 * @param game Pointer to the game
 * @param object Pointer to the object to be added
 * @return OK if the object was added successfully, ERROR otherwise
 */
Status game_add_object(Game *game, Object *object);

/**
 * @brief It gets the object location
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return the id of the space where the object is located
 */
Id game_get_object_location(Game *game, Id id);

/**
 * @brief It sets the object location
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param object_id the id of the object
 * @param space_id the id of the space
 * @return It sets the object location, if everything goes well or ERROR if there was some mistake
 */
Status game_set_object_location(Game *game, Id object_id, Id space_id);

/**
 * @brief It gets the object id by the object name
 * @author Jian Feng
 *
 * @param game a pointer to the game structure
 * @param name the name of the object 
 * @return The id of the object, if everything goes well or NO_ID if there was some mistake
 */
Id game_get_object_id_by_name(Game *game, const char *name);

/**
 * @brief Gets an object by its position in the array
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param pos the position of the object in the game array
 * @return Pointer to the object if found, otherwise NULL
 */
Object *game_get_object_by_position(Game *game, int pos);

/**
 * @brief It gets the character of the game
 * @author Ivan
 *
 * This function returns a pointer to the character stored in the game.
 *
 * @param game a pointer to the game structure
 * @return a pointer to the character, or NULL if there was an error
 */
Character *game_get_character(Game *game, Id id);

/**
 * @brief It gets the character location
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return the id of the space where the character is located
 */
Id game_get_character_location(Game *game, Id id);

/**
 * @brief It sets the character location
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param char_id the id of the character
 * @param space_id the id of the space
 * @return It sets the character location, if everything goes well or ERROR if there was some mistake
 */
Status game_set_character_location(Game *game, Id char_id, Id space_id);

/**
 * @brief Gets the number of characters in the game.
 * @author Jian Feng
 *
 * @param game Pointer to the game.
 * @return Number of characters.
 */
int game_get_n_characters(Game *game);

/**
 * @brief Gets a character by its position in the array
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param pos the position of the character in the game array
 * @return Pointer to the character if found, otherwise NULL
 */
Character *game_get_character_by_position(Game *game, int pos);

/**
 * @brief It gets the player of the game
 * @author Ivan
 *
 * This function returns a pointer to the player stored in the game.
 *
 * @param game a pointer to the game structure
 * @return a pointer to the player, or NULL if there was an error
 */
Player *game_get_player(Game *game);

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
 * @brief Gets the result of the last action executed
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return Status of the last action if everything goes well or ERROR if there was some mistake
 */
Status game_get_last_action_status(Game *game);

/**
 * @brief Sets the result of the last action executed
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_last_action_status(Game *game, Status status);

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
