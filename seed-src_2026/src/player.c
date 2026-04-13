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
struct _Player
{
  Id id;                            /*!< Id number of the player */
  char gdesc[MAX_PLAYER_GDESC + 1]; /*!< Graphic description of the player */
  int health;                       /*!< Health of the player */
  char name[WORD_SIZE + 1];         /*!< Name of the player */
  Id location;                      /*!< Space where the player is located */
  Inventory *backpack;              /*!< Inventory of the player */
};

/**
 * @brief It creates a new player
 */
Player *player_create(Id id, int max_objs)
{
  Player *newPlayer = NULL;
  int i;

  if (id == NO_ID)
    return NULL;

  newPlayer = (Player *)calloc(1, sizeof(Player));
  if (!newPlayer)
    return NULL;

  for (i = 0; i < 6; i++)
  {
    newPlayer->gdesc[i] = '\0';
  }
  newPlayer->health = 0;
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->backpack = inventory_create(max_objs);
  if (!newPlayer->backpack)
  {
    free(newPlayer);
    return NULL;
  }

  return newPlayer;
}

/**
 * @brief It destroys a player
 */
Status player_destroy(Player *player)
{
  if (!player)
    return ERROR;
  inventory_destroy(player->backpack);
  free(player);
  return OK;
}

/**
 * @brief It gets the id of a player
 */
Id player_get_id(Player *player)
{
  if (!player)
    return NO_ID;

  return player->id;
}

/**
 * @brief It sets the name of a player
 */
Status player_set_name(Player *player, char *name)
{
  if (!player || !name)
    return ERROR;

  strcpy(player->name, name);
  return OK;
}

/**
 * @brief It gets the name of a player
 */
const char *player_get_name(Player *player)
{
  if (!player)
    return NULL;

  return player->name;
}

/**
 * @brief It sets the location of the player
 */
Status player_set_location(Player *player, Id id)
{
  if (!player || id == NO_ID)
    return ERROR;

  player->location = id;
  return OK;
}

/**
 * @brief It gets the location of the player
 */
Id player_get_location(Player *player)
{
  if (!player)
    return NO_ID;

  return player->location;
}

Status player_del_object(Player *player, Id id)
{
  if (!player || id == NO_ID)
    return ERROR;

  return inventory_del_object(player->backpack, id);
}

Status player_add_object(Player *player, Id id)
{
  if (!player || id == NO_ID)
    return ERROR;

  return inventory_add_object(player->backpack, id);
}

Bool player_has_object(Player *player, Id id)
{
  if (!player || id == NO_ID)
    return FALSE;
  return inventory_has_object(player->backpack, id);
}

Id *player_get_objects(Player *player)
{
  if (!player)
    return NULL;

  return inventory_get_objects_ids(player->backpack);
}

Inventory *player_get_backpack(Player *player)
{
  if (!player)
    return NULL;

  return player->backpack;
}

int player_get_health(Player *player)
{
  if (!player)
    return 0;

  return player->health;
}

Status player_set_health(Player *player, int health)
{
  if (!player || health < 0)
    return ERROR;

  player->health = health;
  return OK;
}

const char *player_get_gdesc(Player *player)
{
  if (!player)
    return NULL;

  return player->gdesc;
}

Status player_set_gdesc(Player *player, char *gdesc)
{
  if (!player || !gdesc)
    return ERROR;

  strncpy(player->gdesc, gdesc, MAX_PLAYER_GDESC);
  player->gdesc[MAX_PLAYER_GDESC] = '\0';
  return OK;
}

/**
 * @brief It prints the player information
 */
Status player_print(Player *player)
{

  if (!player)
    return ERROR;

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n",
          player->id, player->name);

  if (player->location != NO_ID)
    fprintf(stdout, "---> Location: %ld\n", player->location);
  else
    fprintf(stdout, "---> No location\n");

  fprintf(stdout, "---> Backpack:\n");
  inventory_print(player->backpack);

  fprintf(stdout, "---> Health: %d\n", player->health);

  fprintf(stdout, "---> gdesc: %s\n", player->gdesc);

  return OK;
}
