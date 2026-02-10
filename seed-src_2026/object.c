/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Profesores PPROG && Ivan
 * @version 1
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Object
 *
 * This struct stores all the information of an object.
 */
struct _Object {
  Id id;                    /*!< Id number of the object, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the object */
};


/** 
 * @brief object_create allocates memory for a new object and initializes its members
 */
Object* object_create(Id id) {
  Object* newObject = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newObject = (Object*)calloc(1, sizeof(Object));
  if (newObject == NULL) {
    return NULL;
  }

  /* Initialization of an empty object*/
  newObject->id = id;
  newObject->name[0] = '\0';

  return newObject;
}

/**
 * @brief It destroys an object, freeing the allocated memory
 * */
Status object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  return OK;
}

/*
 * @brief It gets the id of an object
 */
Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

/*
* @brief It sets the name of an object
*/
Status object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }
  return OK;
}

/*
* @brief It gets the name of an object
*/
const char* object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

/*
 * @brief It prints the object information
 */
Status object_print(Object* object) {

  /* Error Control */
  if (!object) {
    return ERROR;
  }

  /* Print the id and the name of the object */
  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);


  return OK;
}
