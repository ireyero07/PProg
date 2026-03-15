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
 * @brief Moves the player to the next space.
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 */
void game_actions_next(Game *game);

/**
 * @brief Moves the player to the previous space.
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 */
void game_actions_back(Game *game);

/**
 * @brief The player takes the object from the space if there is an object.
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated
 */
void game_actions_take(Game *game, Command *cmd);

/**
 * @brief The player drops the object on the space if the player has it.
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated
 */
void game_actions_drop(Game *game);

/**
 * @brief Moves the player to the space on the left
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 */
void game_actions_left(Game *game);

/**
 * @brief Moves the player to the space on the right
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 */
void game_actions_right(Game *game);

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

    case NEXT:
      game_actions_next(game);
      break;

    case BACK:
      game_actions_back(game);
      break;

    case TAKE:
      game_actions_take(game,command);
      break;

    case DROP:
      game_actions_drop(game);
      break;

    case LEFT:
    game_actions_left(game);
    break;

    case RIGHT:
    game_actions_right(game);
    break;

    case ATTACK:
    game_actions_attack(game);
    break;

    case CHAT:
    game_actions_chat(game);
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

void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  if (!game) {
    return;
  }

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    game_set_last_action(game, ERROR);
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));

  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }

  return;
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  if (!game) {
    return;
  }

  space_id = game_get_player_location(game);

  if (space_id == NO_ID) {
    game_set_last_action(game, ERROR);
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));

  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }

  return;
}

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

  if (obj_id != NO_ID && player_get_object(game_get_player(game)) == NO_ID && space_has_object(space, obj_id) == TRUE) {
    space_del_object(space, obj_id);
    player_set_object(game_get_player(game), obj_id);
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }
}

void game_actions_drop(Game *game){
  Id player_location = NO_ID;
  Id obj_id = NO_ID;

  if (!game) {
    return;
  }

  player_location = game_get_player_location(game);
  
  if (player_get_object(game_get_player(game)) != NO_ID) {
    obj_id = player_get_object(game_get_player(game));
    player_set_object(game_get_player(game), NO_ID);

    space_add_object(game_get_space(game, player_location), obj_id);
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }
}

void game_actions_left(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  if (!game) {
    return;
  }

  space_id = game_get_player_location(game);

  if (space_id == NO_ID) {
    game_set_last_action(game, ERROR);
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }

  return;
}

void game_actions_right(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  if (!game) {
    return;
  }

  space_id = game_get_player_location(game);

  if (space_id == NO_ID) {
    game_set_last_action(game, ERROR);
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }
}

void game_actions_attack(Game *game) {
  Id player_loc = game_get_player_location(game);
  Space *space = game_get_space(game, player_loc);
  Id space_id = space_get_id(space);
  Character *enemy = NULL;
  int roll;

  if (!game || !space || space_id == NO_ID) {
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
    if (player_get_health(p) <= 0) {
      printf("Game Over (╥﹏╥)\n");
      game_set_finished(game, TRUE);
    } 
  } else {
    character_set_health(enemy, character_get_health(enemy) - 1);
  }
  if (character_get_health(enemy) <= 0) character_set_gdesc(enemy, " ");

  game_set_last_action(game, OK);
}

void game_actions_chat(Game *game) {
  Id player_loc = game_get_player_location(game);
  Space *space = game_get_space(game, player_loc);
  Character *friend = NULL;

  if (!game || !space) {
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

