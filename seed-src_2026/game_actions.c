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
void game_actions_take(Game *game);

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
      game_actions_take(game);
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

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_take(Game *game){
  Id player_location = NO_ID;
  Id obj_id = NO_ID;
  Space *space = NULL;

  if (!game) {
    return;
  }
  
  player_location = game_get_player_location(game);
  space = game_get_space(game, player_location);
  obj_id = set_get_id_at(space_get_objects(space), 0);

  if (obj_id != NO_ID && player_get_object(game_get_player(game)) == NO_ID) {
    space_del_object(space, obj_id);
    player_set_object(game_get_player(game), obj_id);
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
  }
}

void game_actions_left(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_right(Game *game){
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_attack(Game *game){
  Id player_loc = game_get_player_location(game);
  Id ch_id = space_get_character(game_get_space(game, player_loc));
  Character *enemy;


  if (!game || ch_id == NO_ID) {
    return;
  }
  
  enemy = game_get_character(game,ch_id);

  if(!enemy || character_get_friendly(enemy) || character_get_health(enemy)<= 0){
    return;
  }

  int roll = rand() % 10;
  if(roll <= 4){
    player_set_health(game_get_player(game), player_get_health(game_get_player(game))-1);
  }
  else{
    character_set_health(enemy,character_get_health(enemy)-1);
  }

  return;
}

void game_actions_chat(Game *game){
  Id player_loc = game_get_player_location(game);
  Id ch_id = space_get_character(game_get_space(game, player_loc));
  Character *friend;

  if (!game || ch_id == NO_ID) {
    return;
  }
  
  friend = game_get_character(game,ch_id);

  if(!friend || character_get_friendly(friend)){
    return;
  }
  
  printf("Friend says: %s\n", character_get_message(friend));

  return;
}

