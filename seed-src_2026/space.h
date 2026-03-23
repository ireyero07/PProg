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

#define GDESC_LINES 5
#define GDESC_LENGTH 9
#define MAX_OBJECTS_SPACE 2

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
 * @return id of the object in this space, or NULL if there is none
 */
Set *space_get_objects(Space* space);

/**
 * @brief It gets the list of ids of the objects
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return list of ids of the objects, or NULL if there is none
 */
Id* space_get_objects_ids (Space *space);

/**
 * @brief It gets the number of object in the space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return number of object in the space, or -1 if there is none
 */
long space_get_number_objects(Space *space);

/**
 * @brief Adds a character to a space
 *
 * Inserts a character identifier into the space character set.
 *
 * @param space Pointer to the space
 * @param character Character id
 * @return OK if successful, ERROR otherwise
 */
Status space_add_character(Space* space, Id character);

/**
 * @brief Removes a character from a space
 *
 * Deletes a character identifier from the space character set.
 *
 * @param space Pointer to the space
 * @param character Character id
 * @return OK if successful, ERROR otherwise
 */
Status space_del_character(Space* space, Id character);

/**
 * @brief It gets the id of the character contained in the space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return id of the character in this space, or NO_ID if there is none
 */
Set* space_get_character(Space* space);

/**
 * @brief Checks whether a character is in a space
 *
 * Searches the character set to determine if the character
 * is located in the space.
 *
 * @param space Pointer to the space
 * @param character Character id
 * @return TRUE if the character is in the space, FALSE otherwise
 */
Bool space_has_character(Space* space, Id character);

/**
 * @brief Sets one line of the graphic description of the space.
 *
 * The graphic description is composed of 5 lines of 9 characters each.
 *
 * @param space Pointer to the space.
 * @param gdesc String containing the ASCII representation.
 * @param line Line number (0-4).
 * @return OK if successful, ERROR otherwise.
 */
Status space_set_gdesc(Space* space, char *gdesc, int line);

/**
 * @brief Returns one line of the graphic description.
 *
 * @param space Pointer to the space.
 * @param line Line number (0-4).
 * @return Pointer to the line string or NULL if error.
 */
const char* space_get_gdesc(Space* space, int line);

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


