/**
 * @brief It defines the inventory module interface
 * @file inventory.h
 * @author Ivan
 * @version 0
 * @date 22-02-2026
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

#define MAX_OBJS 10


typedef struct _Inventory Inventory;

Inventory* space_create();

Status inventory_destroy(Inventory* inventory);

int inventory_get_n_objects(Inventory* inventory);

Status inventory_set_n_objects(Inventory* inventory, int n_objects);

Status inventory_add_object(Inventory* inventory, Id object);

Status inventory_del_object(Inventory* inventory, Id object);

Set* inventory_get_objects(Inventory* inventory);

Bool inventory_has_object(Inventory* inventory, Id object);

Id* inventory_get_objects_ids (Inventory* inventory);

long inventory_get_number_objects(Inventory* inventory);

#endif