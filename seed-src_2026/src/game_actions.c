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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
 * @param cmd Pointer to the command that has been entered
 */
void game_actions_attack(Game *game, Command *cmd);

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
 * @brief Command for using an object
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 * @param command Pointer to the command that has been entered
 */
void game_actions_use(Game *game, Command *cmd);

/**
 * @brief Command for opening an object
 * @author Jian Feng Yin Chen
 *
 * @param game Pointer to the game to be updated.
 * @param command Pointer to the command that has been entered
 */
void game_actions_open(Game *game, Command *cmd);


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

Status game_actions_update(Game *game, Command *command)
{
  CommandCode cmd;

  game_set_last_command(game, command);
  game_set_narrator_msg(game, "");

  cmd = command_get_code(command);

  switch (cmd)
  {
  case UNKNOWN:
    game_actions_unknown(game);
    break;

  case EXIT:
    game_actions_exit(game);
    break;

  case TAKE:
    game_actions_take(game, command);
    break;

  case DROP:
    game_actions_drop(game, command);
    break;

  case ATTACK:
    game_actions_attack(game, command);
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
    game_actions_use(game, command);
    break;

  case OPEN:
    game_actions_open(game, command);
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

/*TAKE*/
void game_actions_take(Game *game, Command *cmd)
{
  Inventory *backpack = NULL;
  Id player_location = NO_ID;
  Id obj_id = NO_ID;
  Id *space_ids;
  Object *object;
  Space *space = NULL;
  int i, j;
  const char *object_name;

  if (!game || !cmd)
  {
    return;
  }

  object_name = command_get_arg(cmd);
  if (!object_name)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  space = game_get_space(game, player_location);
  if (!space)
  {
    game_set_last_action(game, ERROR);
    return;
  }
  obj_id = game_get_object_id_by_name(game, object_name);
  object = game_get_object(game, obj_id);
  space_ids = space_get_objects_ids(space);

  if (obj_id != NO_ID && space_has_object(space, obj_id) == TRUE && (player_has_object(game_get_player(game), object_get_dependency(object))==TRUE || object_get_dependency(object) == NO_ID) && object_get_movable(object) == TRUE)
  {
    backpack = player_get_backpack(game_get_player(game));
    if (inventory_get_number_objects(backpack) >= inventory_get_max_objs(backpack))
    {
      game_set_last_action(game, ERROR);
      return;
    }
    space_del_object(space, obj_id);
    if(player_has_object(game_get_player(game), object_get_dependency(object))==TRUE){
      player_del_object(game_get_player(game), object_get_dependency(object));
      for(i=0; i<space_get_number_objects(space); i++){
        for(j=601; j<=606; j++){
          if(space_ids[i] == j){
            space_del_object(space, j);
          }
        }
      }
    }
    player_add_object(game_get_player(game), obj_id);
    game_set_last_action(game, OK);
  }
  else
  {
    game_set_last_action(game, ERROR);
  }
}

/*DROP*/
void game_actions_drop(Game *game, Command *cmd)
{
  Id player_location = NO_ID;
  Id obj_id = NO_ID;
  Space *space = NULL;
  Player *player = NULL;
  const char *object_name;

  if (!game || !cmd)
  {
    return;
  }

  object_name = command_get_arg(cmd);
  if (!object_name)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  space = game_get_space(game, player_location);

  if (!space)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  player = game_get_player(game);
  obj_id = game_get_object_id_by_name(game, object_name);

  if (obj_id != NO_ID && player_has_object(player, obj_id) == TRUE)
  {
    space_add_object(space, obj_id);
    player_del_object(player, obj_id);
    game_set_last_action(game, OK);
  }
  else
  {
    game_set_last_action(game, ERROR);
  }
}

/*ATTACK*/
void game_actions_attack(Game *game, Command *cmd)
{
  Id player_loc = NO_ID;
  Space *space = NULL;
  Id space_id = NO_ID;
  Player *player = NULL;
  Character *enemy = NULL, *follower = NULL;
  int roll, num_followers, attackers, random_attacker, dmg;
  const char *enemy_name;
  Id enemy_id;
  char narrator[WORD_SIZE];
  char tmp[256];

  if (!game || !cmd)
  {
    return;
  }

  enemy_name = command_get_arg(cmd);
  if (!enemy_name || enemy_name[0] == '\0')
  {
    game_set_last_action(game, ERROR);
    return;
  }

  player_loc = game_get_player_location(game);
  space = game_get_space(game, player_loc);

  if (!space)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  space_id = space_get_id(space);
  if (space_id == NO_ID)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  enemy_id = game_get_character_id_by_name(game, enemy_name);
  enemy = game_get_character_by_id(game, enemy_id);

  if (!enemy || character_get_friendly(enemy) || character_get_health(enemy) <= 0 || character_get_location(enemy) != player_loc)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  player = game_get_player(game);
  num_followers = game_count_followers(game, player_get_id(player));
  attackers = 1 + num_followers;
  narrator[0] = '\0';

  if (game_get_deterministic(game))
  {
    dmg = attackers * 10;
    character_set_health(enemy, character_get_health(enemy) - dmg);
    sprintf(narrator, "[Attack] You deal %d damage to %s. ", dmg, character_get_name(enemy));
  }
  else
  {
    roll = rand() % 10;

    if (roll <= 4)
    {
      random_attacker = rand() % attackers;
      if (random_attacker == 0)
      {
        player_set_health(player, player_get_health(player) - 10);
        sprintf(narrator, "[Attack] %s counterattacks! %s receives 10 damage. ",
                character_get_name(enemy),
                player_get_name(player));
      }
      else
      {
        follower = game_get_nth_follower(game, player_get_id(player), random_attacker - 1);
        if (follower)
        {
          character_set_health(follower, character_get_health(follower) - 10);
          sprintf(narrator, "[Attack] %s counterattacks! %s receives 10 damage. ",
          character_get_name(enemy),
          character_get_name(follower));
          if (character_get_health(follower) <= 0)
          {
            character_set_following(follower, NO_ID);
            character_set_location(follower, NO_ID);
            sprintf(tmp, "%s has died. ", character_get_name(follower));
            strncat(narrator, tmp, WORD_SIZE - strlen(narrator) - 1);
          }
        }
      }
    }
    else
    {
      dmg = attackers * 10;
      character_set_health(enemy, character_get_health(enemy) - dmg);
      sprintf(narrator, "[Attack] You deal %d damage to %s. ", dmg, character_get_name(enemy));
    }
  }

  if (character_get_health(enemy) <= 0)
  {
    character_set_location(enemy, NO_ID);
    sprintf(tmp, "%s has been defeated! ", character_get_name(enemy));
    strncat(narrator, tmp, WORD_SIZE - strlen(narrator) - 1);

    if (character_get_boss(enemy) == TRUE && player_loc == 515)
    {
      game_set_finished(game, TRUE);
    }
  }

  game_set_narrator_msg(game, narrator);
  game_set_last_action(game, OK);
}

/*CHAT*/
void game_actions_chat(Game *game, Command *cmd)
{
  Id player_loc = NO_ID;
  Character *friend = NULL;
  Id chr_id = NO_ID;
  const char *chr_name;

  if (!game || !cmd)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  chr_name = command_get_arg(cmd);
  if (!chr_name)
  {
    game_set_last_action(game, ERROR);
    game_set_last_chat(game, "");
    return;
  }

  player_loc = game_get_player_location(game);
  chr_id = game_get_character_id_by_name(game, chr_name);
  friend = game_get_character_by_id(game, chr_id);

  if (!friend || !character_get_friendly(friend) || character_get_location(friend) != player_loc)
  {
    game_set_last_action(game, ERROR);
    game_set_last_chat(game, "");
    return;
  }

  game_set_last_chat(game, character_get_message(friend));
  game_set_last_action(game, OK);
}

/*MOVE*/
void game_actions_move(Game *game, Command *cmd)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  const char *arg;
  Player *player = NULL;
  Character *chr = NULL;
  int i;

  if (!game || !cmd)
  {
    return;
  }

  space_id = game_get_player_location(game);

  if (space_id == NO_ID)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  arg = command_get_arg(cmd);
  if (!arg)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  if ((strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0) && game_connection_is_open(game, space_id, N))
  {
    current_id = game_get_connection(game, space_id, N);
  }
  else if ((strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0) && game_connection_is_open(game, space_id, E))
  {
    current_id = game_get_connection(game, space_id, E);
  }
  else if ((strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0) && game_connection_is_open(game, space_id, S))
  {
    current_id = game_get_connection(game, space_id, S);
  }
  else if ((strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0) && game_connection_is_open(game, space_id, W))
  {
    current_id = game_get_connection(game, space_id, W);
  }
  else if ((strcmp(arg, "down") == 0 || strcmp(arg, "d") == 0) && game_connection_is_open(game, space_id, DOWN))
  {
    current_id = game_get_connection(game, space_id, DOWN);
  }
  else if ((strcmp(arg, "up") == 0 || strcmp(arg, "u") == 0) && game_connection_is_open(game, space_id, UP))
  {
    current_id = game_get_connection(game, space_id, UP);
  }

  else
  {
    current_id = NO_ID;
  }

  if (current_id != NO_ID)
  {
    player = game_get_player(game);
    if (!player)
    {
      game_set_last_action(game, ERROR);
      return;
    }

    if (strcmp(arg, "up") == 0 || strcmp(arg, "u") == 0) {
      player_set_floor(player, player_get_floor(player) + 1);
    }
    else if (strcmp(arg, "down") == 0 || strcmp(arg, "d") == 0) {
      player_set_floor(player, player_get_floor(player) - 1);
    }

    game_set_player_location(game, current_id, player_get_id(player));
    space_set_discovered(game_get_space(game, current_id), TRUE);

    for (i = 0; i < game_get_n_characters(game); i++)
    {
      chr = game_get_character_by_position(game, i);

      if (chr != NULL && character_get_following(chr) == player_get_id(player) && character_get_health(chr) > 0)
      {
        character_set_location(chr, current_id);
      }
    }
    game_set_last_action(game, OK);
  }
  else
  {
    game_set_last_action(game, ERROR);
  }

  return;
}

/*INSPECT*/
void game_actions_inspect(Game *game, Command *cmd)
{
  Id player_location = NO_ID;
  Id obj_id = NO_ID;
  Space *space = NULL;
  Player *player;
  const char *object_name;

  if (!game || !cmd)
  {
    return;
  }

  object_name = command_get_arg(cmd);
  if (!object_name)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  space = game_get_space(game, player_location);
  if (!space)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  obj_id = game_get_object_id_by_name(game, object_name);
  player = game_get_player(game);

  if (obj_id != NO_ID && (space_has_object(space, obj_id) == TRUE || player_has_object(player, obj_id)))
  {
    game_set_last_obj_desc(game, object_get_description(game_get_object(game, obj_id)));
    game_set_last_action(game, OK);
  }
  else
  {
    game_set_last_action(game, ERROR);
  }
  return;
}

/*RECRUIT*/
void game_actions_recruit(Game *game, Command *cmd)
{
  Id player_location = NO_ID;
  Id chr_id = NO_ID;
  Character *chr = NULL;
  Player *player;
  const char *chr_name;

  if (!game || !cmd)
  {
    return;
  }

  chr_name = command_get_arg(cmd);
  if (!chr_name)
  {
    game_set_last_action(game, ERROR);
    return;
  }
  player_location = game_get_player_location(game);
  chr_id = game_get_character_id_by_name(game, chr_name);
  player = game_get_player(game);
  chr = game_get_character_by_id(game, chr_id);

  if (player != NULL && chr != NULL && chr_id != NO_ID && character_get_location(chr) == player_location && character_get_friendly(chr) == TRUE && character_get_following(chr) == NO_ID)
  {
    character_set_following(chr, player_get_id(player));
    game_set_last_action(game, OK);
  }
  else
  {
    game_set_last_action(game, ERROR);
  }
  return;
}

/*ABANDON*/
void game_actions_abandon(Game *game, Command *cmd)
{
  Id player_location = NO_ID;
  Id chr_id = NO_ID;
  Character *chr = NULL;
  Player *player;
  const char *chr_name;

  if (!game || !cmd)
  {
    return;
  }

  chr_name = command_get_arg(cmd);
  if (!chr_name)
  {
    game_set_last_action(game, ERROR);
    return;
  }
  player_location = game_get_player_location(game);
  chr_id = game_get_character_id_by_name(game, chr_name);
  player = game_get_player(game);
  chr = game_get_character_by_id(game, chr_id);

  if (player != NULL && chr != NULL && chr_id != NO_ID && character_get_following(chr) == player_get_id(player))
  {
    character_set_following(chr, NO_ID);
    character_set_location(chr, player_location);
    game_set_last_action(game, OK);
  }
  else
  {
    game_set_last_action(game, ERROR);
  }
  return;
}

/*USE*/
void game_actions_use(Game *game, Command *cmd)
{
  char c_argument[WORD_SIZE] = "";
  char lower_arg[WORD_SIZE] = "";
  char obj_name[WORD_SIZE + 1] = "";
  char char_name[WORD_SIZE + 1] = "";
  Bool over_something_else = FALSE;
  Player *player = NULL;
  Character *character = NULL;
  Id object = NO_ID;
  char *sep = NULL;
  int i, obj_len;

  if (!game || !cmd)
  {
    return;
  }

  strncpy(c_argument, command_get_arg(cmd), WORD_SIZE - 1);
  c_argument[WORD_SIZE - 1] = '\0';

  if (c_argument[0] == '\0')
  {
    game_set_last_action(game, ERROR);
    return;
  }

  for (i = 0; c_argument[i]; i++)
    lower_arg[i] = tolower((unsigned char)c_argument[i]);
  lower_arg[i] = '\0';

  sep = strstr(lower_arg, " over ");
  if (sep)
  {
    obj_len = sep - lower_arg;
    strncpy(obj_name, c_argument, obj_len);
    obj_name[obj_len] = '\0';
    strncpy(char_name, c_argument + obj_len + 6, WORD_SIZE);
    char_name[WORD_SIZE] = '\0';
    over_something_else = TRUE;
  }
  else
  {
    strncpy(obj_name, c_argument, WORD_SIZE);
    obj_name[WORD_SIZE] = '\0';
    over_something_else = FALSE;
  }

  if (obj_name[0] == '\0')
  {
    game_set_last_action(game, ERROR);
    return;
  }

  player = game_get_player(game);
  if (player == NULL)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  object = (game_get_object_id_by_name(game, obj_name));
  if (inventory_has_object(player_get_backpack(player), object) != TRUE)
  {
    game_set_last_action(game, ERROR);
    return;
  }
  /*Use the object*/
  if(object_get_health(game_get_object(game, object))!=0){
    switch (over_something_else)
    {
    case TRUE:
      character = game_get_character_by_id(game, game_get_character_id_by_name(game, char_name));
      if (character == NULL || character_get_health(character) <= 0)
      {
        game_set_last_action(game, ERROR);
        return;
      }
      if (character_get_location(character) != game_get_player_location(game))
      {
        game_set_last_action(game, ERROR);
        return;
      }
      if (character_set_health(character, character_get_health(character) + object_get_health(game_get_object(game, object))) != OK)
      {
        game_set_last_action(game, ERROR);
        return;
      }
      player_del_object(player, object);
      break;

    case FALSE:

      if (player_set_health(player, player_get_health(player) + object_get_health(game_get_object(game, object))) != OK)
      {
        game_set_last_action(game, ERROR);
        return;
      }
      player_del_object(player, object);
      break;
    }

    game_set_last_action(game, OK);
  }else {
    game_set_last_action(game, ERROR);
  }
  return; 
}
/*OPEN*/
void game_actions_open(Game *game, Command *cmd)
{
  char c_argument[WORD_SIZE] = "";
  char lower_arg[WORD_SIZE] = "";
  char obj_name[WORD_SIZE + 1] = "";
  char link_name[WORD_SIZE + 1] = "";
  Player *player = NULL;
  Link *link = NULL;
  Id object = NO_ID;
  char *sep = NULL;
  int i, link_len;

  if (!game || !cmd)
  {
    return;
  }

  strncpy(c_argument, command_get_arg(cmd), WORD_SIZE - 1);
  c_argument[WORD_SIZE - 1] = '\0';

  for (i = 0; c_argument[i]; i++)
    lower_arg[i] = tolower((unsigned char)c_argument[i]);
  lower_arg[i] = '\0';

  sep = strstr(lower_arg, " with ");
  if (sep)
  {
    link_len = sep - lower_arg;
    strncpy(link_name, c_argument, link_len);
    link_name[link_len] = '\0';
    strncpy(obj_name, c_argument + link_len + 6, WORD_SIZE);
    obj_name[WORD_SIZE] = '\0';
  }
  else
  {
    game_set_last_action(game, ERROR);
    return;
  }

  if (link_name[0] == '\0' || obj_name[0] == '\0')
  {
    game_set_last_action(game, ERROR);
    return;
  }

  player = game_get_player(game);
  if (player == NULL)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  object = (game_get_object_id_by_name(game, obj_name));
  if (object == NO_ID)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  if ((inventory_has_object(player_get_backpack(player), object) != TRUE))
  {
    game_set_last_action(game, ERROR);
    return;
  }



  link = game_get_link_by_id(game, game_get_link_id_by_name(game, link_name));
  if (link == NULL)
  {
    game_set_last_action(game, ERROR);
    return;
  }
  if (link_get_open(link) == TRUE)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  if(link_get_id(link)!=(object_get_open(game_get_object(game, object)))){
    game_set_last_action(game, ERROR);
    return;
  }
  
  /*Use the object*/
  if (link_get_origin(link) != game_get_player_location(game))
  {
    game_set_last_action(game, ERROR);
    return;
  }

  if (link_set_open(link, TRUE) == ERROR || player_del_object(player, object) == ERROR)
  {
    game_set_last_action(game, ERROR);
    return;
  }

  game_set_last_action(game, OK);

  return;
}