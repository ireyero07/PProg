/**
 * @brief It defines the set module
 * @file set.c
 * @author Ivan
 * @version 0
 * @date 22-02-2026
 * @copyright GNU Public License
 */

#include "set.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Set structure
 */
struct _Set {
  Id ids[MAX_IDS];
  int n_ids;
};

/**
 * @brief Creates a new set
 */
Set* set_create() {
  Set *newSet = NULL;
  int i;

  newSet = (Set*)calloc(1, sizeof(Set));
  if (!newSet) return NULL;

  newSet->n_ids = 0;

  for (i = 0; i < MAX_IDS; i++)
    newSet->ids[i] = NO_ID;

  return newSet;
}

/**
 * @brief Destroys a set
 */
Status set_destroy(Set* set) {
  if (!set) return ERROR;

  free(set);
  return OK;
}

/**
 * @brief Adds an id to the set
 */
Status set_add(Set* set, Id id) {
  int i;

  if (!set || id == NO_ID || set->n_ids >= MAX_IDS) return ERROR;

  /* avoid duplicates */
  for (i = 0; i < set->n_ids; i++)
    if (set->ids[i] == id)
      return ERROR;

  set->ids[set->n_ids] = id;
  set->n_ids++;

  return OK;
}

/**
 * @brief Deletes an id from the set
 */
Status set_del(Set* set, Id id) {
  int i, pos = -1;

  if (!set) return ERROR;

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) {
      pos = i;
      break;
    }
  }

  if (pos == -1) return ERROR;

  /* compact array */
  for (i = pos; i < set->n_ids - 1; i++) {
    set->ids[i] = set->ids[i + 1];
  }

  set->n_ids--;

  return OK;
}

/**
 * @brief Checks if id exists
 */
Bool set_find(Set* set, Id id) {
  int i;

  if (!set) return FALSE;

  for (i = 0; i < set->n_ids; i++)
    if (set->ids[i] == id)
      return TRUE;

  return FALSE;
}

/**
 * @brief Gets number of ids
 */
int set_get_n_ids(Set* set) {
  if (!set) return -1;

  return set->n_ids;
}

/**
 * @brief Gets id at position
 */
Id set_get_id_at(Set* set, int position) {
  if (!set || position < 0 || position >= set->n_ids)
    return NO_ID;

  return set->ids[position];
}

/**
 * @brief Prints set information
 */
Status set_print(Set* set) {
  int i;

  if (!set) return ERROR;

  printf("Set: ");

  for (i = 0; i < set->n_ids; i++)
    printf("%ld ", set->ids[i]);

  printf("\n");

  return OK;
}