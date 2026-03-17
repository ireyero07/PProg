/**
 * @brief It implements the inventory
 *
 * @file inventory.c
 * @author Jian Feng Yin Chen
 * @version 0
 * @date 17-03-2026
 * @copyright GNU Public License
 */

#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Inventory
 *
 * This struct stores all the information of a inventory.
 */
struct _Inventory {
    Set *objects;                                     /*!< Set of objects in the inventory*/
    int n_objects                                     /*!< Number of objects in the inventory*/
};

Inventory* space_create() {
  Inventory* newInventory = NULL;
  int i;

  newInventory = (Inventory*)calloc(1, sizeof(Inventory));
  if (newInventory == NULL) {
    return NULL;
  }

  newInventory->n_objects = 0;

  newInventory->objects = set_create();
    if (!newInventory->objects) {
        free(newInventory);
        return NULL;
    }

  return newInventory;
}

Status inventory_destroy(Inventory* inventory) {
  if (!inventory) {
    return ERROR;
  }

  set_destroy(inventory->objects);

  free(inventory);
  return OK;
}

int inventory_get_id(Inventory* inventory) {
  if (!inventory) {
    return NO_ID;
  }
  return inventory->n_objects;
}


Status inventory_set_name(Inventory* inventory, int n_objects) {
  if (!inventory || n_objects <= 0) {
    return ERROR;
  }

  inventory->n_objects = n_objects;

  return OK;
}

Status inventory_add_object(Inventory* inventory, Id object){
  if(!inventory || object == NO_ID)
    return ERROR;

  return set_add(inventory->objects, object);
}

Status inventory_del_object(Inventory* inventory, Id object){
  if(!inventory || object == NO_ID)
    return ERROR;

  return set_del(inventory->objects, object);
}

Set* inventory_get_objects(Inventory* inventory){
  if(!inventory)
    return NULL;

  return inventory->objects;
}

Bool inventory_has_object(Inventory* inventory, Id object){
  if(!inventory || object == NO_ID)
    return FALSE;

  if (set_find(inventory->objects, object) == -1)
    return FALSE;

  return TRUE;
}

Id* inventory_get_objects_ids (Inventory* inventory){
  if(!inventory) return NULL;

  return set_get_list_ids(inventory->objects);
}

long inventory_get_number_objects(Inventory* inventory){
  if(!inventory) return -1;

  return set_get_n_ids(inventory->objects);
}

Status inventory_print(Inventory* inventory) {
  if (!inventory) {
    return ERROR;
  }

  fprintf(stdout, "--> Number of objects in the inventory: %d\n", inventory->n_objects);

  fprintf(stdout, "---> Objects in the inventory: ");
  set_print(inventory->objects);

  return OK;
}