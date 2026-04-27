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
    Set *objs;                                     /*!< Set of objects in the inventory*/
    int max_objs;                                     /*!< Maximum number of objects in the inventory*/       
};

Inventory* inventory_create(int max_objs) {
  Inventory* newInventory = NULL;

  newInventory = (Inventory*)calloc(1, sizeof(Inventory));
  if (newInventory == NULL) {
    return NULL;
  }

  newInventory->max_objs = max_objs;

  newInventory->objs = set_create();
    if (!newInventory->objs) {
        free(newInventory);
        return NULL;
    }

  return newInventory;
}

Status inventory_destroy(Inventory* inventory) {
  if (!inventory) {
    return ERROR;
  }

  set_destroy(inventory->objs);

  free(inventory);
  return OK;
}

int inventory_get_max_objs(Inventory* inventory) {
  if (!inventory) {
    return -1;
  }
  return inventory->max_objs;
}


Status inventory_set_max_objs(Inventory* inventory, int max_objs) {
  if (!inventory || max_objs <= 0 || max_objs>MAX_IDS) {
    return ERROR;
  }

  inventory->max_objs = max_objs;

  return OK;
}

Status inventory_add_object(Inventory* inventory, Id object){
  if(!inventory || object == NO_ID || set_get_n_ids(inventory->objs) >= inventory->max_objs)
    return ERROR;

  return set_add(inventory->objs, object);
}

Status inventory_del_object(Inventory* inventory, Id object){
  if(!inventory || object == NO_ID)
    return ERROR;

  return set_del(inventory->objs, object);
}

Set* inventory_get_objects(Inventory* inventory){
  if(!inventory)
    return NULL;

  return inventory->objs;
}

Bool inventory_has_object(Inventory* inventory, Id object){
  if(!inventory || object == NO_ID)
    return FALSE;

  if (set_find(inventory->objs, object) == -1)
    return FALSE;

  return TRUE;
}

Id* inventory_get_objects_ids (Inventory* inventory){
  if(!inventory) return NULL;

  return set_get_list_ids(inventory->objs);
}

long inventory_get_number_objects(Inventory* inventory){
  if(!inventory) return -1;

  return set_get_n_ids(inventory->objs);
}

Status inventory_print(Inventory* inventory) {
  if (!inventory) {
    return ERROR;
  }

  fprintf(stdout, "--> Max objects: %d\n",inventory->max_objs);
  fprintf(stdout, "--> Current objects: %d\n",set_get_n_ids(inventory->objs));
  fprintf(stdout, "---> Objects in the inventory: ");
  set_print(inventory->objs);

  return OK;
}