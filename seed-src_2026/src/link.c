/**
 * @brief It implements the link module
 *
 * @file link.c
 * @author Ivan Reyero
 * @version 0
 * @date 25-02-2026
 * @copyright GNU Public License
 */

#include "link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief link
 *
 * This struct stores all the information of a link.
 */
struct _Link {
  Id id;                     /*!< Id number of the link, it must be unique */
  char name[WORD_SIZE + 1];  /*!< Name of the link */
  Id origin;                 /*!< Id origin of the link, it must be unique */
  Id destination;            /*!< Id destination of the link, it must be unique */
  Direction direction;       /*!< Direction of the link */
  Bool open;                 /*!< Bool (open or close) */
};

/** link_create allocates memory for a new link
 *  and initializes its members
 */
Link* link_create(Id id) {
  Link* newLink = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newLink = (Link*)calloc(1, sizeof(Link));
  if (newLink == NULL) {
    return NULL;
  }

  /* Initialization of an empty link*/
  newLink->id = id;
  newLink->name[0] = '\0';
  newLink->origin = NO_ID;
  newLink->destination = NO_ID;
  newLink->direction = NO_DIRECTION;
  newLink->open = FALSE; 

  return newLink;
}

Status link_destroy(Link* link) {
  if (!link) {
    return ERROR;
  }

  free(link);
  return OK;
}

Id link_get_id(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->id;
}

Status link_set_name(Link* link, char* name) {
  if (!link || !name) {
    return ERROR;
  }

  if (!strcpy(link->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* link_get_name(Link* link) {
  if (!link) {
    return NULL;
  }
  return link->name;
}

Status link_set_origin(Link* link, Id id) {
  if (!link || id == NO_ID) {
    return ERROR;
  }
  link->origin = id;
  return OK;
}

Id link_get_origin(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->origin;
}

Status link_set_destination(Link* link, Id id) {
  if (!link || id == NO_ID) {
    return ERROR;
  }
  link->destination = id;
  return OK;
}

Id link_get_destination(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->destination;
}

Status link_set_direction(Link *link, Direction direction) {
  if (!link || ((direction!=N) && (direction!=S) && (direction!=W) && (direction!=E))){
    return ERROR;
  }

  link->direction = direction;
  return OK;
}

Direction link_get_direction(Link *link) {
  if (!link) return NO_DIRECTION;

  return link->direction;
}

Status link_set_open(Link* link, Bool open){
  if (!link) return ERROR;

  link->open = open;
  return OK;
}

Bool link_get_open(Link* link){
  if (!link) return FALSE;

  return link->open;
}

Status link_print(Link* link) {
  const char *dir_str;

  if (!link) {
    return ERROR;
  }

  switch (link->direction) {
    case N: dir_str = "NORTH"; break;
    case S: dir_str = "SOUTH"; break;
    case E: dir_str = "EAST"; break;
    case W: dir_str = "WEST"; break;
    default: dir_str = "UNKNOWN"; break;
  }

  fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name);
  fprintf(stdout, " Origin: %ld\n", link->origin);
  fprintf(stdout, " Destination: %ld\n", link->destination);
  fprintf(stdout, " Direction: %s\n", dir_str);
  fprintf(stdout, " State: %s\n", link->open ? "OPEN" : "CLOSED");

  return OK;
}

