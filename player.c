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
 * @brief Player
 *
 * This struct stores all the information of a player.
 */
struct _Player {
  Id id;                         /*!< Id number of the player */
  char name[WORD_SIZE + 1];      /*!< Name of the player */
  Id location;                   /*!< Space where the player is located */
  Id object;                     /*!< Object carried by the player */
};


/**
 * @brief It creates a new player
 */
Player* player_create(Id id) {
  Player* newPlayer = NULL;

  if (id == NO_ID) return NULL;

  newPlayer = (Player*)calloc(1, sizeof(Player));
  if (!newPlayer) return NULL;

  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->object = NO_ID;

  return newPlayer;
}


/**
 * @brief It destroys a player
 */
Status player_destroy(Player* player) {
  if (!player) return ERROR;

  free(player);
  return OK;
}


/**
 * @brief It gets the id of a player
 */
Id player_get_id(Player* player) {
  if (!player) return NO_ID;

  return player->id;
}


/**
 * @brief It sets the name of a player
 */
Status player_set_name(Player* player, char* name) {
  if (!player || !name) return ERROR;

  strcpy(player->name, name);
  return OK;
}


/**
 * @brief It gets the name of a player
 */
const char* player_get_name(Player* player) {
  if (!player) return NULL;

  return player->name;
}


/**
 * @brief It sets the location of the player
 */
Status player_set_location(Player* player, Id id) {
  if (!player || id == NO_ID) return ERROR;

  player->location = id;
  return OK;
}


/**
 * @brief It gets the location of the player
 */
Id player_get_location(Player* player) {
  if (!player) return NO_ID;

  return player->location;
}


/**
 * @brief It sets the object carried by the player
 */
Status player_set_object(Player* player, Id id) {
  if (!player) return ERROR;

  player->object = id;
  return OK;
}


/**
 * @brief It gets the object carried by the player
 */
Id player_get_object(Player* player) {
  if (!player) return NO_ID;

  return player->object;
}


/**
 * @brief It prints the player information
 */
Status player_print(Player* player) {

  if (!player) return ERROR;

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n",
          player->id, player->name);

  if (player->location != NO_ID)
    fprintf(stdout, "---> Location: %ld\n", player->location);
  else
    fprintf(stdout, "---> No location\n");

  if (player->object != NO_ID)
    fprintf(stdout, "---> Carrying object: %ld\n", player->object);
  else
    fprintf(stdout, "---> No object\n");

  return OK;
}