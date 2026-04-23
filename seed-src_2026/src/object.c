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
  Id id;                          /*!< Id number of the object, it must be unique */
  char name[WORD_SIZE + 1];       /*!< Name of the object */
  char description[MAX_DESC];     /*!< Description of the object */
  int health;                     /*!< The amount of health that the object cures */
  Bool movable;                   /*!< If the object is movable or not */
  Id dependency;                  /*!< The Id of the object that is needed to pick this object */
  Id open;                        /*!< The Id of the link that can be opened with this object */
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
  newObject->health = 0;
  newObject->movable = FALSE;
  newObject->dependency = NO_ID;
  newObject->open = NO_ID;

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
* @brief It sets the description of an object
*/
Status object_set_description(Object* object, char* description) {
  if (!object || !description) {
    return ERROR;
  }

  if (!strcpy(object->description, description)) {
    return ERROR;
  }
  return OK;
}

/*
* @brief It gets the description of an object
*/
const char* object_get_description(Object* object){
  if(!object){
    return NULL;
  }
  return object->description;
}

/*
* @brief It sets the health of an object
*/
Status object_set_health(Object *object, int health){
  if(!object){
    return ERROR;
  }

  object->health = health;

  return OK;
}

/*
* @brief It gets the health of an object
*/
int object_get_health(Object* object){
  if(!object){
    return -1;
  }
  return object->health;
}

/*
* @brief It sets if an object is movable
*/
Status object_set_movable(Object *object, Bool movable){
  if(!object){
    return ERROR;
  }

  object->movable = movable;

  return OK;
}

/*
* @brief It gets if an object is movable
*/
Bool object_get_movable(Object* object){
  if(!object){
    return FALSE;
  }
  return object->movable;
}

/*
* @brief It sets the dependency of an object
*/
Status object_set_dependency(Object *object, Id dependency){
  if(!object || dependency<0){
    return ERROR;
  }

  object->dependency = dependency;

  return OK;
}

/*
* @brief It gets the dependency of an object
*/
Id object_get_dependency(Object* object){
  if(!object){
    return NO_ID;
  }
  return object->dependency;
}

/*
* @brief It sets the Id that an object can open
*/
Status object_set_open(Object *object, Id open){
  if(!object || open<0){
    return ERROR;
  }

  object->open = open;

  return OK;
}

/*
* @brief It gets the Id that the object can open
*/
Id object_get_open(Object* object){
  if(!object){
    return NO_ID;
  }
  return object->open;
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
