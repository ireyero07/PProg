/**
 * @brief It defines the set module interface
 * @file set.h
 * @author Ivan
 * @version 0
 * @date 22-02-2026
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

#define MAX_IDS 100

typedef struct _Set Set;

/**
 * @brief Creates a new set
 * @author Ivan
 *
 * @return pointer to the new set or NULL if error
 */
Set* set_create();

/**
 * @brief Destroys a set
 * @author Ivan
 *
 * @param set a pointer to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_destroy(Set* set);

/**
 * @brief Adds an id to the set
 * @author Ivan
 *
 * @param set a pointer to set
 * @param id 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_add(Set* set, Id id);

/**
 * @brief Deletes an id from the set
 * @author Ivan
 *
 * @param set a pointer to set
 * @param id 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_del(Set* set, Id id);

/**
 * @brief Checks if an id belongs to the set
 * @author Ivan
 *
 * @param set a pointer to set
 * @param id
 * @return the position of the id if everithing goes well or -1 if there was some mistake
 */
int set_find(Set* set, Id id);

/**
 * @brief Gets number of ids stored
 * @author Ivan
 *
 * @param set a pointer to set
 * @return n_ids if everything goes well or -1 if there was some mistake
 */
int set_get_n_ids(Set* set);

/**
 * @brief Gets id at position
 * @author Ivan
 *
 * @param set a pointer to set
 * @param position an integer to the position 
 * @return position of the id if everything goes well or NO_ID if there was some mistake
 */
Id set_get_id_at(Set* set, int position);

/**
 * @brief Prints set information
 * @author Ivan
 *
 * @param set a pointer to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_print(Set* set);

#endif