/**
 * @brief It implements the player
 *
 * @file player.c
 * @author Jian Feng Yin Chen
 * @version 0
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Player structure
 *
 * This struct stores all the information of the player.
 */
struct _Player {
  Id id;                        /*!< Id number of the player, it must be unique */
  char name[WORD_SIZE + 1];     /*!< Name of the player */
  Id north;                     /*!< Id of the north connection from player location */
  Id south;                     /*!< Id of the south connection from player location */
  Id east;                      /*!< Id of the east connection from player location */
  Id west;                      /*!< Id of the west connection from player location */
  Bool object;                  /*!< Whether the player has an object or not */
};

Player* player_create(Id id) {
  Player* newPlayer = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newPlayer = (Player*)calloc(1, sizeof(Player));
  if (newPlayer == NULL) {
    return NULL;
  }

  /* Initialization of an empty player */
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->north = NO_ID;
  newPlayer->south = NO_ID;
  newPlayer->east = NO_ID;
  newPlayer->west = NO_ID;
  newPlayer->object = FALSE;

  return newPlayer;
}

Status player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  free(player);
  return OK;
}

Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

Status player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

Status player_set_north(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->north = id;
  return OK;
}

Id player_get_north(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->north;
}

Status player_set_south(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->south = id;
  return OK;
}

Id player_get_south(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->south;
}

Status player_set_east(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->east = id;
  return OK;
}

Id player_get_east(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->east;
}

Status player_set_west(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->west = id;
  return OK;
}

Id player_get_west(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->west;
}

Status player_set_object(Player* player, Bool value) {
  if (!player) {
    return ERROR;
  }
  player->object = value;
  return OK;
}

Bool player_get_object(Player* player) {
  if (!player) {
    return FALSE;
  }
  return player->object;
}

Status player_print(Player* player) {
  Id idaux = NO_ID;

  /* Error Control */
  if (!player) {
    return ERROR;
  }

  /* 1. Print the id and the name of the player */
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  /* 2. For each direction of the player location, print its link */
  idaux = player_get_north(player);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = player_get_south(player);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = player_get_east(player);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = player_get_west(player);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if the player has the object or not */
  if (player_get_object(player)) {
    fprintf(stdout, "---> Player has object.\n");
  } else {
    fprintf(stdout, "---> Player has no object.\n");
  }

  return OK;
}