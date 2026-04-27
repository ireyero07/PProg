/**
 * @brief It defines the link module interface
 *
 * @file link.h
 * @author Ivan Reyero
 * @version 0
 * @date 23-03-2026
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef struct _Link Link; /*!< Opaque type representing a connection between two spaces */

/**
 * @brief It creates a new link, allocating memory and initializing its members
 * @author Ivan Reyero
 *
 * @param id the identification number for the new link
 * @return a new link, initialized
 */
Link* link_create(Id id);

/**
 * @brief It destroys a link, freeing the allocated memory
 * @author Ivan Reyero
 *
 * @param link a pointer to the link that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_destroy(Link* link);

/**
 * @brief It gets the id of a link
 * @author Ivan Reyero
 *
 * @param link a pointer to the link
 * @return the id of link
 */
Id link_get_id(Link* link);

/**
 * @brief It sets the name of a link
 * @author Ivan Reyero
 *
 * @param link a pointer to the link
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_name(Link* link, char* name);

/**
 * @brief It gets the name of a link
 * @author Ivan Reyero
 *
 * @param link a pointer to the link
 * @return  a string with the name of the link
 */
const char* link_get_name(Link* link);

/**
 * @brief It sets the id of the link located at the origin
 * @author Ivan Reyero
 *
 * @param link a pointer to the link
 * @param id the id number of the link located at the origin
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status link_set_origin(Link* link, Id id);

/**
 * @brief It gets the id of the link located at the origin
 * @author Ivan Reyero
 *
 * @param link a pointer to the link
 * @return the id number of the link located at the origin
 */
Id link_get_origin(Link* link);

/**
 * @brief It sets the id of the link located at the destination
 * @author Ivan Reyero
 *
 * @param link a pointer to the link
 * @param id the id number of the link located at the destination
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_destination(Link* link, Id id);

/**
 * @brief It gets the id of the link located at the destination
 * @author Ivan Reyero
 *
 * @param link a pointer to the link
 * @return the id number of the link located at the destination
 */
Id link_get_destination(Link* link);

/**
 * @brief Sets the direction of the link
 * @author Ivan Reyero
 *
 * @param link Pointer to the link
 * @param direction Direction (N, S, E, W)
 * @return OK if success, ERROR otherwise
 */
Status link_set_direction(Link *link, Direction direction);

/**
 * @brief Gets the direction of the link
 * @author Ivan Reyero
 *
 * @param link Pointer to the link
 * @return Direction of the link
 */
Direction link_get_direction(Link *link);

/**
 * @brief It sets if a link is open
 * @author Ivan Reyero
 *
 * @param link a pointer to the link
 * @param open TRUE if open, FALSE if not
 * @return OK if successful, ERROR if not
 */
Status link_set_open(Link* link, Bool open);

/**
 * @brief It gets if a link is open
 * @author Ivan Reyero
 *
 * @param link a pointer to the link
 * @return TRUE if open, FALSE if not
 */
Bool link_get_open(Link* link);

/**
 * @brief It prints the link information
 * @author Ivan Reyero
 *
 * This fucntion shows the id and name of the link, the links that surrounds it and wheter it has an object or not.
 * @param link a pointer to the link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_print(Link* link);

#endif