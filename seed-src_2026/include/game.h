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

#define MAX_SPACES 100     /*!< Maximum number of spaces allowed in the game */
#define MAX_OBJECTS 10     /*!< Maximum number of objects allowed in the game */
#define MAX_CHARACTERS 10  /*!< Maximum number of characters allowed in the game */
#define MAX_LINKS 100      /*!< Maximum number of links allowed in the game */
#define MAX_PLAYERS 8      /*!< Maximum number of players allowed in the game */

#include "player.h"
#include "space.h"
#include "object.h"
#include "command.h"
#include "interface_data.h"
#include "types.h"
#include "character.h"
#include "link.h"

typedef struct _Game Game; /*!< Opaque type representing the game state */

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
 * @brief It says if an space have any characters or no
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @param id the id of the space
 * @return True or false
 */
Bool game_space_have_characters(Game *game, Id id);

/**
 * @brief It says if an space have any enemy characters or no
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @param id the id of the space
 * @return True or false
 */
Bool game_space_have_enemy_character(Game *game, Id space_id);

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
 * @param id the id of the object
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
 * @brief Adds a character to the game
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @param character a pointer to the character that you want to add
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief It gets the character of the game
 * @author Ivan
 *
 * This function returns a pointer to the character stored in the game.
 *
 * @param game a pointer to the game structure
 * @param id the id of the character
 * @return a pointer to the character, or NULL if there was an error
 */
Character *game_get_character(Game *game, Id id);

/**
 * @brief It gets the character location
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param id the id of the character
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
 * @brief Gets a character by its space id
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param space_id the id of the space
 * @return Pointer to the character if found, otherwise NULL
 */
Set *game_get_characters_by_space(Game *game, Id space_id);

/**
 * @brief Gets a character by its character id
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param chr_id the id of the character
 * @return Pointer to the character if found, otherSwise NULL
 */
Character *game_get_character_by_id(Game *game, Id chr_id);

/**
 * @brief It gets the character id by the character name
 * @author Jian Feng
 *
 * @param game a pointer to the game structure
 * @param name the name of the character 
 * @return The id of the character, if everything goes well or NO_ID if there was some mistake
 */
Id game_get_character_id_by_name(Game *game, const char *name);

/**
 * @brief Returns the nth follower of a given player.
 * @author Jian Feng
 *
 * @param game a pointer to the game structure
 * @param player_id ID of the player 
 * @param n Position of the follower to retrieve.
 * @return Pointer to the nth follower Character, or NULL if the player has fewer 
 */
Character *game_get_nth_follower(Game *game, Id player_id, int n);

/**
 * @brief Adds a player to the game
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @param player a pointer to the player that you want to add
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_player(Game *game, Player *player);

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
 * @param space_id the id of the new player location
 * @param player_id the id of the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status game_set_player_location(Game *game, Id space_id, Id player_id);

/**
 * @brief It increases the turn in the game structure
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_next_turn(Game *game);

/**
 * @brief It returns the position in the array of the actual player
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @return The position in the array of the actual player or -1 in case of ERROR
 */
int game_get_turn(Game *game);

/**
 * @brief It returns the number of players in a game
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @return The number of player in the game or -1 in case of ERROR
 */
int game_get_n_players(Game *game);

/**
 * @brief It returns the player with the requested id
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @param id the player id
 * @return The player with that id
 */
Player *game_get_player_from_id(Game *game, Id id);

/**
 * @brief It tells if any of the players death
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @return If there is any player death
 */
Bool game_is_any_player_death (Game *game);

/**
 * @brief It counts the amount of characters following th player
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @param player_id the player id
 * @return the amount of characters following th player
 */
int game_count_followers(Game *game, Id player_id);

/**
 * @brief Adds a link to the game
 * @author Ivan Reyero
 *
 * @param game Pointer to the game
 * @param link Pointer to the link to be added
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief Gets the destination space from a given space and direction
 * @author Ivan Reyero
 *
 * @param game Pointer to the game
 * @param space_id Id of the origin space
 * @param direction Direction of the desired connection
 * @return Id of the destination space if found, NO_ID otherwise
 */
Id game_get_connection(Game *game, Id space_id, Direction direction);

/**
 * @brief Checks if a connection is open or closed
 * @author Ivan Reyero
 *
 * @param game Pointer to the game
 * @param space_id Id of the origin space
 * @param direction Direction of the link
 * @return TRUE if the link is open, FALSE otherwise
 */
Bool game_connection_is_open(Game *game, Id space_id, Direction direction);

/**
 * @brief It gets a pointer to a link by its id
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param link_id Id of the link
 * @return a pointer to the link or NULL if something fails
 */
Link *game_get_link_by_id(Game *game, Id link_id);

/**
 * @brief It gets a pointer to a link by its name
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param name A constant char with the name of the link
 * @return The Id of the link or NO_ID if something fails
 */
Id game_get_link_id_by_name(Game *game, const char *name);

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
Status game_get_last_action(Game *game);

/**
 * @brief Sets the result of the last action executed
 * @author Ivan
 *
 * @param game a pointer to the game structure
 * @param status the status to set as the result of the last action
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_last_action(Game *game, Status status);

/**
 * @brief Gets the last chat message stored in the game.
 * @author Ivan
 *
 * This function returns the last chat text generated by a
 * friendly character. The graphic engine uses it to display
 * the message in the description area.
 *
 * @param game Pointer to the Game structure
 *
 * @return Pointer to the stored chat message, or NULL if game is NULL
 */
char *game_get_last_chat(Game *game);

/**
 * @brief Sets the last chat message generated in the game.
 * @author Ivan
 *
 * @param game Pointer to the Game structure
 * @param msg Text message generated by the character
 *
 * @return OK if the message was stored correctly, ERROR otherwise
 */
Status game_set_last_chat(Game *game, const char *msg);

/**
 * @brief Gets the last object description (inspect) stored in the game.
 * @author Ivan
 *
 * This function returns the last chat text generated by a
 * friendly character. The graphic engine uses it to display
 * the message in the description area.
 *
 * @param game Pointer to the Game structure
 *
 * @return Pointer to the stored chat message, or NULL if game is NULL
 */
char *game_get_last_obj_desc(Game *game);

/**
 * @brief Sets the last object description (inspect) generated in the game.
 * @author Ivan
 *
 * @param game Pointer to the Game structure
 * @param desc text description of the last inspected object
 *
 * @return OK if the message was stored correctly, ERROR otherwise
 */
Status game_set_last_obj_desc(Game *game, const char *desc);

/**
 * @brief It adds an interface data to the game
 * @author Ivan
 *
 * @param game Pointer to the Game structure
 * @param intdata Pointer ti the Interface_Data that wants to be added
 *
 * @return OK if the it is added correctly; ERROR otherwise
 */
Status game_add_interface_data(Game *game, Interface_Data *intdata);

/**
 * @brief It sets the deterministic flag of the game
 * @author Ivan
 *
 * @param game Pointer to the Game structure
 * @param deterministic the new value of the deterministic flag
 *
 * @return OK if the it is added correctly; ERROR otherwise
 */
Status game_set_deterministic(Game *game, Bool deterministic);

/**
 * @brief It gets the deterministic flag of the game
 * @author Ivan
 *
 * @param game Pointer to the Game structure
 *
 * @return TRUE if the game is deterministic, FALSE otherwise
 */
Bool game_get_deterministic(Game *game);

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
