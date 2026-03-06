/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG && Ivan
 * @version 0
 * @date 25-02-2026
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                                            /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];                         /*!< Name of the space */
  Id north;                                         /*!< Id of the space at the north */
  Id south;                                         /*!< Id of the space at the south */
  Id east;                                          /*!< Id of the space at the east */
  Id west;                                          /*!< Id of the space at the west */
  Set *objects;                                     /*!< Set of objects in the space*/
  Set *characters;                                  /*!< Ser of characters in the space*/
  char gdesc[GDESC_LINES][GDESC_LENGTH + 1];        /*!< Graphic description of the space (5x9) */
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space* space_create(Id id) {
  Space* newSpace = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newSpace = (Space*)calloc(1, sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  
  newSpace->objects = set_create();
    if (!newSpace->objects) {
        free(newSpace);
        return NULL;
    }

  newSpace->characters = set_create();
    if (!newSpace->characters) {
        set_destroy(newSpace->objects);
        free(newSpace);
        return NULL;
    }

    for (int i = 0; i < GDESC_LINES; i++) {
      newSpace->gdesc[i][0] = '\0';
    }

  return newSpace;
}

Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);
  set_destroy(space->characters);

  free(space);
  return OK;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Status space_add_object(Space* space, Id object){
  if(!space || object == NO_ID)
    return ERROR;

  return set_add(space->objects, object);
}

Status space_del_object(Space* space, Id object){
  if(!space || object == NO_ID)
    return ERROR;

  return set_del(space->objects, object);
}

Set* space_get_objects(Space* space){
  if(!space)
    return NULL;

  return space->objects;
}

Bool space_has_object(Space* space, Id object){
  if(!space || object == NO_ID)
    return FALSE;

  if (set_find(space->objects, object) == -1)
    return FALSE;

  return TRUE;
}

Status space_add_character(Space* space, Id character){
  if(!space || character == NO_ID)
    return ERROR;

  return set_add(space->characters, character);
}

Status space_del_character(Space* space, Id character){
  if(!space || character == NO_ID)
    return ERROR;

  return set_del(space->characters, character);
}

Set* space_get_character(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->characters;
}

Bool space_has_character(Space* space, Id character){
  if(!space || character == NO_ID)
    return FALSE;

  if (set_find(space->characters, character) == -1)
    return FALSE;

  return TRUE;
}

Status space_set_gdesc(Space* space, char *gdesc, int line){
  if (!space || !gdesc || line < 0 || line >= GDESC_LINES) return ERROR;

  strncpy(space->gdesc[line], gdesc, GDESC_LENGTH);
  space->gdesc[line][GDESC_LENGTH] = '\0';

  return OK;
}

const char* space_get_gdesc(Space* space, int line){
  if (!space || line < 0 || line >= GDESC_LINES) return NULL;

  return space->gdesc[line];
}

Status space_print(Space* space) {
  Id idaux = NO_ID;

  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print objects in the space */
  fprintf(stdout, "---> Objects in the space: ");
  set_print(space->objects);

  /* 4. Print characters in the space */
  fprintf(stdout, "---> Characters in the space: ");
  set_print(space->characters);

  /* 5. Print graphic description */
  fprintf(stdout, "---> Graphic description:\n");
  for (int i = 0; i < GDESC_LINES; i++) {
    fprintf(stdout, "%s\n", space->gdesc[i]);
  }

  return OK;
}

