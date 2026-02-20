/**
 * @brief Character management module
 *
 * @file character.h
 * @author Jian Feng Yin Chen
 * @version 0
 * @date 20-02-2026
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

typedef struct _Character Character;

/**
 * @brief It creates a new character, allocating memory and initializing its members
 * @author Jian Feng Yin Chen
 *
 * @param id the identification number for the new character
 * @return a new character, initialized
 */
Character* character_create(Id id);

/**
 * @brief It destroys a character, freeing its memory
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return OK if successful, ERROR if not
 */
Status character_destroy(Character* character);

/**
 * @brief It gets the id of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return the id of the character, NO_ID if error
 */
Id character_get_id(Character* character);

/**
 * @brief It gets the name of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return the name of the character, NULL if error
 */
const char* character_get_name(Character* character);

/**
 * @brief It gets the graphical description of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return the graphical description, NULL if error
 */
const char* character_get_gdesc(Character* character);

/**
 * @brief It gets the health of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return the health, -1 if error
 */
int character_get_health(Character* character);

/**
 * @brief It gets if a character is friendly
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return TRUE if friendly, FALSE if not, FALSE if error
 */
Bool character_get_friendly(Character* character);

/**
 * @brief It gets the message of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return the message, NULL if error
 */
const char* character_get_message(Character* character);

/**
 * @brief It sets the id of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param id the new identification number
 * @return OK if successful, ERROR if not
 */
Status character_set_id(Character* character, Id id);

/**
 * @brief It sets the name of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param name the new name
 * @return OK if successful, ERROR if not
 */
Status character_set_name(Character* character, char* name);

/**
 * @brief It sets the graphical description of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param gdesc the new graphical description
 * @return OK if successful, ERROR if not
 */
Status character_set_gdesc(Character* character, char* gdesc);

/**
 * @brief It sets the health of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param health the new health value
 * @return OK if successful, ERROR if not
 */
Status character_set_health(Character* character, int health);

/**
 * @brief It sets if a character is friendly
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param friendly TRUE if friendly, FALSE if not
 * @return OK if successful, ERROR if not
 */
Status character_set_friendly(Character* character, Bool friendly);

/**
 * @brief It sets the message of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param message the new message
 * @return OK if successful, ERROR if not
 */
Status character_set_message(Character* character, char* message);

/**
 * @brief It prints a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return OK if successful, ERROR if not
 */
Status character_print(Character* character);

#endif