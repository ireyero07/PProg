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
 * @return the id of the player
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
 * @brief It sets the location of the player
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @param id the id number of the space where the player is located
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_location(Player* player, Id id);

/**
 * @brief It gets the location of the player
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @return the id number of the space where the player is located
 */
Id player_get_location(Player* player);

/**
 * @brief It sets the object carried by the player
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @param id the id number of the object carried by the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object(Player* player, Id id);

/**
 * @brief It gets the object carried by the player
 * @author Jian Feng Yin Chen
 *
 * @param player a pointer to the player
 * @return the id number of the object carried by the player
 */
Id player_get_object(Player* player);

/**
 * @brief It prints the player information
 * @author Jian Feng Yin Chen
 *
 * This function shows the id, name, location and carried object of the player.
 *
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player* player);

#endif
