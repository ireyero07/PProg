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
 * @param cmd Pointer to the command that has been entered
 */
void game_actions_chat(Game *game, Command *cmd);

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
 * @param command Pointer to the command that has been entered
 */
void game_actions_inspect(Game *game, Command *cmd);

/**
 * @brief Command for recruiting a character
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 * @param command Pointer to the command that has been entered
 */
void game_actions_recruit(Game *game, Command *cmd);


/**
 * @brief Command for abandoning a character
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 * @param command Pointer to the command that has been entered
 */
void game_actions_abandon(Game *game, Command *cmd);

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
      game_actions_chat(game, command);
      break;

    case MOVE:
      game_actions_move(game, command);
      break;

    case INSPECT:
      game_actions_inspect(game, command);
      break;

    case RECRUIT:
      game_actions_recruit(game, command);
      break;

    case ABANDON:
      game_actions_abandon(game, command);
      break;

    case USE:
      game_actions_recruit(game, command);
      break;

    case OPEN:
      game_actions_abandon(game, command);
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
  Inventory *backpack=NULL;
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
  if (!space) {
    game_set_last_action(game, ERROR);
    return;
  }
  obj_id = game_get_object_id_by_name(game,object_name);

  if (obj_id != NO_ID  && space_has_object(space, obj_id) == TRUE) {
    backpack = player_get_backpack(game_get_player(game));
    if(inventory_get_number_objects(backpack) >= inventory_get_max_objs(backpack)){
      game_set_last_action(game,ERROR);
      return;
    }
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

  if (!space) {
    game_set_last_action(game, ERROR);
    return;
  }

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
  Player *player = NULL;
  Character *enemy = NULL, *follower = NULL;
  int roll, num_followers, attackers, random_attacker;

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

  player = game_get_player(game);
  num_followers= game_count_followers(game,player_get_id(player));
  attackers = 1 + num_followers;

  roll = rand() % 10;

  if(roll <= 4){
    random_attacker =rand() % attackers;
    if(random_attacker == 0){ 
      /* daño al jugador */
      player_set_health(player,player_get_health(player) - 1);
    } else { 
      /* daño a follower */
      follower = game_get_nth_follower(game,player_get_id(player), random_attacker - 1);
      if (follower) {
        character_set_health(follower, character_get_health(follower)-1);

        if (character_get_health(follower) <= 0) {
          character_set_following(follower, NO_ID);
          character_set_location(follower, NO_ID);
        }
      }
    }
  } else { 
    /* daño al enemigo */
      character_set_health(enemy, character_get_health(enemy)-attackers);
  }

  if (character_get_health(enemy) <= 0){
    character_set_location(enemy, NO_ID);
  }

  game_set_last_action(game, OK);
}

void game_actions_chat(Game *game, Command *cmd) {
  Id player_loc = NO_ID;
  Character *friend = NULL;
  Id chr_id = NO_ID;
  const char *chr_name;

  if (!game || !cmd) {
    game_set_last_action(game, ERROR);
    return;
  }

  chr_name = command_get_arg(cmd);
  if (!chr_name) {
    game_set_last_action(game, ERROR);
    game_set_last_chat(game, "");
    return;
  }

  player_loc = game_get_player_location(game);
  chr_id = game_get_character_id_by_name(game, chr_name);
  friend = game_get_character_by_id(game, chr_id);

  if (!friend || !character_get_friendly(friend) || character_get_location(friend) != player_loc) {
    game_set_last_action(game, ERROR);
    game_set_last_chat(game, "");
    return;
  }

  game_set_last_chat(game, character_get_message(friend));
  game_set_last_action(game, OK);
}

void game_actions_move(Game *game, Command *cmd){
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  const char *arg;
  Player *player = NULL;
  Character *chr = NULL;
  int i;

  if (!game || !cmd) {
    return;
  }

  space_id = game_get_player_location(game);

  if (space_id == NO_ID) {
    game_set_last_action(game, ERROR);
    return;
  }

  arg = command_get_arg(cmd);
  if (!arg) {
    game_set_last_action(game, ERROR);
    return;
  }

  if((strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0) && game_connection_is_open(game, space_id, N)){
    current_id = game_get_connection(game, space_id, N);

  } else if ((strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0) && game_connection_is_open(game, space_id, E)){
    current_id = game_get_connection(game, space_id, E);

  } else if ((strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0) && game_connection_is_open(game, space_id, S)){
    current_id = game_get_connection(game, space_id, S);

  } else if ((strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0) && game_connection_is_open(game, space_id, W)){
    current_id = game_get_connection(game, space_id, W);

  } else if ((strcmp(arg, "down") == 0 || strcmp(arg, "d") == 0) && game_connection_is_open(game, space_id, DOWN)){
    current_id = game_get_connection(game, space_id, DOWN);

  } else if ((strcmp(arg, "up") == 0 || strcmp(arg, "u") == 0) && game_connection_is_open(game, space_id, UP)){
    current_id = game_get_connection(game, space_id, UP);

  } 
  
  else {
    current_id = NO_ID;
  }

  if (current_id != NO_ID) {
    player = game_get_player(game);
    if (!player) {
      game_set_last_action(game, ERROR);
      return;
    }

    game_set_player_location(game, current_id, player_get_id(player));
    space_set_discovered(game_get_space(game, current_id), TRUE);

    for (i = 0; i < game_get_n_characters(game); i++) {
      chr = game_get_character_by_position(game, i);

      if (chr != NULL && character_get_following(chr) == player_get_id(player) && character_get_health(chr) > 0) {
        character_set_location(chr, current_id);
      }
    }
    game_set_last_action(game, OK);

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
  if (!space) {
    game_set_last_action(game, ERROR);
    return;
  }

  obj_id = game_get_object_id_by_name(game,object_name);
  player = game_get_player(game);

  if (obj_id != NO_ID  && (space_has_object(space, obj_id) == TRUE || player_has_object(player, obj_id))) {
    game_set_last_obj_desc(game, object_get_description(game_get_object(game, obj_id)));
    game_set_last_action(game, OK);
  } else {
    game_set_last_action(game, ERROR);
  }
  return;
}

void game_actions_recruit(Game *game, Command *cmd){
  Id player_location = NO_ID;
  Id chr_id = NO_ID;
  Character *chr = NULL;
  Player *player;
  const char *chr_name;

  if(!game || !cmd){
    return;
  }

  chr_name = command_get_arg(cmd);
  if(!chr_name) {
    game_set_last_action(game, ERROR);
    return;
  }
  player_location = game_get_player_location(game);
  chr_id = game_get_character_id_by_name(game,chr_name);
  player = game_get_player(game);
  chr = game_get_character_by_id(game,chr_id);

  if(player != NULL && chr != NULL && chr_id != NO_ID && character_get_location(chr) == player_location && character_get_friendly(chr) == TRUE && character_get_following(chr) == NO_ID){
    character_set_following(chr,player_get_id(player));
    game_set_last_action(game, OK);
  } else{
    game_set_last_action(game, ERROR);
  }
  return;
}

void game_actions_abandon(Game *game, Command *cmd){
  Id player_location = NO_ID;
  Id chr_id = NO_ID;
  Character *chr = NULL;
  Player *player;
  const char *chr_name;

  if(!game || !cmd){
    return;
  }

  chr_name = command_get_arg(cmd);
  if(!chr_name) {
    game_set_last_action(game, ERROR);
    return;
  }
  player_location = game_get_player_location(game);
  chr_id = game_get_character_id_by_name(game,chr_name);
  player = game_get_player(game);
  chr = game_get_character_by_id(game,chr_id);

  if(player != NULL && chr != NULL && chr_id != NO_ID && character_get_following(chr) == player_get_id(player)){
    character_set_following(chr,NO_ID);
    character_set_location(chr,player_location);
    game_set_last_action(game, OK);
  } else{
    game_set_last_action(game, ERROR);
  }
  return;
}



void game_actions_use(Game *game, Command *cmd){
  char *token=NULL;
  char *c_argument=NULL;
  char obj_name[WORD_SIZE+1]="";
  char char_name[WORD_SIZE+1]="";
  Id player_location = NO_ID;
  int lenght;
  if(!game || !cmd){
    return;
  }

  c_argument = command_get_arg(cmd);
  if(!c_argument) {
    game_set_last_action(game, ERROR);
    return;
  }

  /*Splits the command argument to get the object name and the character name*/
  token = strtok(c_argument, " ");
  if(!token){
    game_set_last_action(game, ERROR);
    return;
  }
  lenght=strlen(token);
  if(lenght>WORD_SIZE){
    game_set_last_action(game, ERROR);
    return;
  }
  strncpy(obj_name, token, WORD_SIZE);
  obj_name[WORD_SIZE]='\0';
  token = strtok(NULL, " ");
  if(strcasecmp(token, "over")!=0||strcasecmp(token, "o")!=0){
    game_set_last_action(game, ERROR);
    return;
  }

/*AQUI ME QUEDO*/



  player_location = game_get_player_location(game);
  chr_id = game_get_character_id_by_name(game,chr_name);
  player = game_get_player(game);
  chr = game_get_character_by_id(game,chr_id);

  if(player != NULL && chr != NULL && chr_id != NO_ID && character_get_following(chr) == player_get_id(player)){
    character_set_following(chr,NO_ID);
    character_set_location(chr,player_location);
    game_set_last_action(game, OK);
  } else{
    game_set_last_action(game, ERROR);
  }
  return;
}