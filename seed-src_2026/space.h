/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Profesores PPROG && Ivan
 * @version 0
 * @date 25-02-2026
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"


typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status space_set_north(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space* space);

/**
 * @brief It sets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space* space);

/**
 * @brief It sets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space* space);

/**
 * @brief It sets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space* space);

/**
 * @brief Adds an object to a space
 *
 * Inserts an object identifier into the space object set.
 *
 * @param space Pointer to the space
 * @param object Object id
 * @return OK if successful, ERROR otherwise
 */
Status space_add_object(Space* space, Id object);

/**
 * @brief Removes an object from a space
 *
 * Deletes an object identifier from the space object set.
 *
 * @param space Pointer to the space
 * @param object Object id
 * @return OK if successful, ERROR otherwise
 */
Status space_del_object(Space* space, Id object);

/**
 * @brief Checks whether an object is in a space
 *
 * Searches the object set to determine if the object
 * is located in the space.
 *
 * @param space Pointer to the space
 * @param object Object id
 * @return TRUE if the object is in the space, FALSE otherwise
 */
Bool space_has_object(Space* space, Id object);

/**
 * @brief It gets the id of the object contained in the space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return id of the object in this space, or NO_ID if there is none
 */
Set *space_get_objects(Space* space);

/**
 * @brief It sets the id of the character contained in the space
 * @author Jian Feng Yin Chen
 *
 * @param space a pointer to the space
 * @param id id of the character in this space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_character(Space* space, Id id);

/**
 * @brief It gets the id of the character contained in the space
 * @author Jian Feng Yin Chen
 *
 * @param space a pointer to the space
 * @return id of the character in this space, or NO_ID if there is none
 */
Id space_get_character(Space* space);

/**
 * @brief Returns the id of the character if there is one in this space
 * @author Jian Feng Yin Chen
 *
 * @param space a pointer to the space
 * @return id of the character in the space, or NO_ID
 */
Id space_character_here(Space* space);

/**
 * @brief It prints the space information
 * @author Profesores PPROG
 *
 * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);

#endif


