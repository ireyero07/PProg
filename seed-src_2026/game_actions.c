/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG && Jian Feng Yin Chen
 * @version 0
 * @date 02-02-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

/**
 * @brief Handles an unknown command.
 *
 * @author Jian Feng Yin Chen
 * @param game Pointer to the game.
 */
void game_actions_unknown(Game *game);

/**
 * @brief Handles the exit command.
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 */
void game_actions_exit(Game *game);

/**
 * @brief The player takes the object from the space if there is an object.
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated
 * @param cmd Pointer to the command that has been entered
 */
void game_actions_take(Game *game, Command *cmd);

/**
 * @brief The player drops the object on the space if the player has it.
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated
 */
void game_actions_drop(Game *game, Command *cmd);

/**
 * @brief The player attacks to the character
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 */
void game_actions_attack(Game *game);

/**
 * @brief The player chats with the character if the player is with a character
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 */
void game_actions_chat(Game *game);

/**
 * @brief The player moves north, east, south or west, depending on the input
 * @author Ivan Mijangos Alvarez
 *
 * @param game Pointer to the game to be updated.
 * @param cmd Pointer to the command that has been entered
 */
void game_actions_move(Game *game, Command *cmd);

/**
 * @brief Command for inspecting an object
 * @author Ivan Mijangos Alvarez
 *
 * @param game Pointer to the game to be updated.
 * @param cmd Pointer to the command that has been entered
 */
void game_actions_inspect(Game *game, Command *cmd);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case TAKE:
      game_actions_take(game,command);
      break;

    case DROP:
      game_actions_drop(game, command);
      break;

    case ATTACK:
    game_actions_attack(game);
    break;

    case CHAT:
    game_actions_chat(game);
    break;

    case MOVE:
    game_actions_move(game, command);
    break;

    case INSPECT:
    game_actions_inspect(game, command);
    break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_take(Game *game, Command *cmd){
  Id player_location = NO_ID;
  Id obj_id = NO_ID;
  Space *space = NULL;
  const char *object_name;

  if (!game || !cmd) {
    return;
  }
  
  object_name = command_get_arg(cmd);
  if(!object_name) {
    game_set_last_action(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  space = game_get_space(game, player_location);
  obj_id = game_get_object_id_by_name(game,object_name);

  if (obj_id != NO_ID  && space_has_object(space, obj_id) == TRUE) {
    space_del_object(space, obj_id);
    player_add_object(game_get_player(game), obj_id);
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }
}

void game_actions_drop(Game *game, Command *cmd){
  Id player_location = NO_ID;
  Id obj_id = NO_ID;
  Space *space = NULL;
  Player *player = NULL;
  const char *object_name;

  if (!game || !cmd) {
    return;
  }
  
  object_name = command_get_arg(cmd);
  if(!object_name) {
    game_set_last_action(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  space = game_get_space(game, player_location);
  player = game_get_player(game);
  obj_id = game_get_object_id_by_name(game,object_name);

  if (obj_id != NO_ID  && player_has_object(player, obj_id) == TRUE) {
    space_add_object(space, obj_id);
    player_del_object(player, obj_id);
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }
}

void game_actions_attack(Game *game) {
  Id player_loc = NO_ID;
  Space *space = NULL;
  Id space_id = NO_ID;
  Character *enemy = NULL;
  int roll;

  if (!game) {
    return;
  }

  player_loc = game_get_player_location(game);
  space = game_get_space(game, player_loc);

  if (!space) {
    game_set_last_action(game, ERROR);
    return;
  }

  space_id = space_get_id(space);
  if (space_id == NO_ID) {
    game_set_last_action(game, ERROR);
    return;
  }
  enemy = game_get_character_by_space(game,space_id);

  if (!enemy || character_get_friendly(enemy) || character_get_health(enemy) <= 0) {
    game_set_last_action(game, ERROR);
    return;
  }

  roll = rand() % 10;
  if (roll <= 4) {
    Player *p = game_get_player(game);
    player_set_health(p, player_get_health(p) - 1);
  } else {
    character_set_health(enemy, character_get_health(enemy) - 1);
  }
  if (character_get_health(enemy) <= 0) character_set_gdesc(enemy, " ");

  game_set_last_action(game, OK);
}

void game_actions_chat(Game *game) {
  Id player_loc = NO_ID;
  Space *space = NULL;
  Character *friend = NULL;

  if (!game) {
    game_set_last_action(game, ERROR);
    return;
  }

  player_loc = game_get_player_location(game);
  space = game_get_space(game, player_loc);

  if (!space) {
    game_set_last_action(game, ERROR);
    return;
  }

  friend = game_get_character_by_space(game, space_get_id(space));
  if (!friend || !character_get_friendly(friend)) {
    game_set_last_action(game, ERROR);
    return;
  }

  game_set_last_chat(game, character_get_message(friend));
  printf("%s",character_get_message(friend));
  game_set_last_action(game, OK);
}

void game_actions_move(Game *game, Command *cmd){
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  const char *arg;

  if (!game || !cmd) {
    return;
  }

  space_id = game_get_player_location(game);

  if (space_id == NO_ID) {
    game_set_last_action(game, ERROR);
    return;
  }

  arg = command_get_arg(cmd);

  if(strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0){

    current_id = game_get_connection(game, space_id, N);

  } else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0){

    current_id = game_get_connection(game, space_id, E);

  } else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0){

    current_id = game_get_connection(game, space_id, S);

  } else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0){

    current_id = game_get_connection(game, space_id, W);

  } else {

    current_id = NO_ID;

  }

  if (current_id != NO_ID) {
    game_set_player_location(game, current_id, player_get_id(game_get_player(game)));
    game_set_last_action(game, OK);
    space_set_discovered(game_get_space(game, current_id), TRUE);
  } else {
    game_set_last_action(game, ERROR);
  }
  
  return;
}

void game_actions_inspect(Game *game, Command *cmd){
  Id player_location = NO_ID;
  Id obj_id = NO_ID;
  Space *space = NULL;
  Player *player;
  const char *object_name;

  if(!game || !cmd){
    return;
  }
  
  object_name = command_get_arg(cmd);
  if(!object_name) {
    game_set_last_action(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  space = game_get_space(game, player_location);
  obj_id = game_get_object_id_by_name(game,object_name);
  player = game_get_player(game);

  if (obj_id != NO_ID  && (space_has_object(space, obj_id) == TRUE || player_has_object(player, obj_id))) {
    game_set_last_obj_desc(game, object_get_description(game_get_object(game, obj_id)));
    printf("%s",object_get_description(game_get_object(game, obj_id)));
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }

  game_set_last_command(game, cmd);
}