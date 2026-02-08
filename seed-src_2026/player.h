/**
 * @brief Player management module
 *
 * @file player.h
 * @author Jian Feng Yin Chen
 * @version 0
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Jian Feng Yin Chen
 *
 * @param id the identification number for the new player
 * @return a new player, initialized
 */
Player* player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player* player);

/**
 * @brief It gets the id of a player
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @return the id of player
 */
Id player_get_id(Player* player);

/**
 * @brief It sets the name of a player
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief It gets the name of a player
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @return a string with the name of the player
 */
const char* player_get_name(Player* player);

/**
 * @brief It sets the id of the space located at the north from the player location
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @param id the id number of the space from the player location located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_north(Player* player, Id id);

/**
 * @brief It gets the id of the space located at the north from the player location
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @return the id number of the space located at the north from the player location
 */
Id player_get_north(Player* player);

/**
 * @brief It sets the id of the space located at the south from the player location
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @param id the id number of the space from the player location located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_south(Player* player, Id id);

/**
 * @brief It gets the id of the space located at the south from the player location
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @return the id number of the space located at the south from the player location
 */
Id player_get_south(Player* player);

/**
 * @brief It sets the id of the space located at the east from the player location
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @param id the id number of the space from the player location located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_east(Player* player, Id id);

/**
 * @brief It gets the id of the space located at the east from the player location
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @return the id number of the space located at the east from the player location
 */
Id player_get_east(Player* player);

/**
 * @brief It sets the id of the space located at the west from the player location
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @param id the id number of the space from the player location located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_west(Player* player, Id id);

/**
 * @brief It gets the id of the space located at the west from the player location
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @return the id number of the space located at the west from the player location
 */
Id player_get_west(Player* player);

/**
 * @brief It sets whether the player has an object or not
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @param value a boolean, specifying if in the player there is an object (TRUE) or not (FALSE)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object(Player* player, Bool value);

/**
 * @brief It gets whether the player has an object or not
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @return a boolean, specifying if the player has an object (TRUE) or not (FALSE)
 */
Bool player_get_object(Player* player);

/**
 * @brief It prints the player information
 * @author Jian Feng Yin Chen
 *
 * This function shows the id and name of the player, the spaces that surround it and whether it has an object or not.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player* player);


#endif