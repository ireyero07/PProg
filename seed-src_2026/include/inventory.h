/**
 * @brief It defines the inventory module interface
 * @file inventory.h
 * @author Jian Feng Yin Chen
 * @version 0
 * @date 17-03-2026
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

typedef struct _Inventory Inventory;

/**
 * @brief It creates a new inventory, allocating memory and initializing its members
 * @author Jian Feng Yin Chen
 *
 * @return a new inventory, initialized
 */
Inventory* inventory_create(int max_objs);

/**
 * @brief It destroys a inventory, freeing the allocated memory
 * @author Jian Feng Yin Chen
 *
 * @param inventory a pointer to the inventory that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_destroy(Inventory* inventory);

/**
 * @brief It gets the number of objects of a inventory
 * @author Jian Feng Yin Chen
 *
 * @param inventory a pointer to the inventory
 * @return  the number of objects in the inventory
 */
int inventory_get_max_objs(Inventory* inventory);

/**
 * @brief It sets the number of objects of the inventory
 * @author Jian Feng Yin Chen
 *
 * @param inventory a pointer to the inventory
 * @return  OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_set_max_objs(Inventory* inventory, int n_objects);

/**
 * @brief Adds an object to a inventory
 * @author Jian Feng Yin Chen
 * Inserts an object identifier into the inventory object set.
 *
 * @param inventory Pointer to the inventory
 * @param object Object id
 * @return OK if successful, ERROR otherwise
 */
Status inventory_add_object(Inventory* inventory, Id object);

/**
 * @brief Removes an object from a inventory
 * @author Jian Feng Yin Chen
 * Deletes an object identifier from the inventory object set.
 *
 * @param inventory Pointer to the inventory
 * @param object Object id
 * @return OK if successful, ERROR otherwise
 */
Status inventory_del_object(Inventory* inventory, Id object);

/**
 * @brief It gets the id of the object contained in the inventory
 * @author Jian Feng Yin Chen
 *
 * @param inventory a pointer to the inventory
 * @return id of the object in this sinventory, or NULL if there is none
 */
Set* inventory_get_objects(Inventory* inventory);

/**
 * @brief Checks whether an object is in a inventory
 * @author Jian Feng Yin Chen
 * Searches the object set to determine if the object
 * is located in the inventory.
 *
 * @param inventory Pointer to the inventory
 * @param object Object id
 * @return TRUE if the object is in the inventory, FALSE otherwise
 */
Bool inventory_has_object(Inventory* inventory, Id object);

/**
 * @brief It gets the list of ids of the objects
 * @author Jian Feng Yin Chen
 *
 * @param inventory a pointer to the inventory
 * @return list of ids of the objects, or NULL if there is none
 */
Id* inventory_get_objects_ids (Inventory* inventory);

/**
 * @brief It gets the number of object in the inventory
 * @author Jian Feng Yin Chen
 *
 * @param inventory a pointer to the inventory
 * @return number of object in the inventory, or -1 if there is none
 */
long inventory_get_number_objects(Inventory* inventory);

/**
 * @brief It prints the inventory information
 * @author Jian Feng Yin Chen
 *.
 * @param inventory a pointer to the inventory
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_print(Inventory* inventory);

#endif