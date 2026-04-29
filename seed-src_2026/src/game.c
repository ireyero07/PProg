/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG && Ivan
 * @version 1
 * @date 10-02-2026
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

/**
 * @brief Game
 *
 * This struct stores all the information related to the game state.
 */
struct _Game
{
  Player *players[MAX_PLAYERS];         /*!< Pointer to the player of the game */
  int n_players;                        /*!< Number of player in the game */
  int turn;                             /*!< Position in the array of players of the one who is playing at the moment */
  Interface_Data *intdata[MAX_PLAYERS]; /*!< Array of pointers to the interface data of each player */
  Object *object[MAX_OBJECTS];          /*!< Array of pointers to the object of the game */
  int n_objects;                        /*!< Number of objects currently in the game */
  Character *character[MAX_CHARACTERS]; /*!< Array of pointers to the character of the game */
  int n_characters;                     /*!< Number of characters currently in the game */
  Space *spaces[MAX_SPACES];            /*!< Array of pointers to the spaces of the game */
  int n_spaces;                         /*!< Number of spaces currently in the game */
  Link *links[MAX_LINKS];               /*!< Array of pointers to the links of the game */
  int n_links;                          /*!< Number of links currently in the game */
  Bool finished;                        /*!< Flag that indicates if the game has finished */
  Bool deterministic;                   /*!< Flag that indicates if the game is deterministic */
};

/**
 * @brief It creates a new game and initializes its members
 */
Game *game_create()
{
  int i;
  Game *game = NULL;

  game = (Game *)malloc(sizeof(Game));
  if (!game)
    return NULL;

  for (i = 0; i < MAX_PLAYERS; i++)
  {
    game->players[i] = NULL;
  }

  for (i = 0; i < MAX_PLAYERS; i++)
  {
    game->intdata[i] = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    game->object[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    game->character[i] = NULL;
  }

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    game->links[i] = NULL;
  }

  game->n_players = 0;
  game->turn = 0;
  game->n_objects = 0;
  game->n_characters = 0;
  game->n_spaces = 0;
  game->n_links = 0;
  game->finished = FALSE;
  game->deterministic = FALSE;

  /* ---------------- GAME STATE ---------------- */

  game->finished = FALSE;

  return game;
}

/**
 * @brief It destroys the game, freeing all allocated memory
 */
Status game_destroy(Game *game)
{
  int i = 0;

  if (!game)
    return ERROR;

  /* Destroy the player */
  for (i = 0; i < game->n_players; i++)
  {
    player_destroy(game->players[i]);
  }

  /* Destroy the interface_data */
  for (i = 0; i < game->n_players; i++)
  {
    interface_data_destroy(game->intdata[i]);
  }

  /* Destroy the objects */
  for (i = 0; i < game->n_objects; i++)
  {
    object_destroy(game->object[i]);
  }

  /* Destroy the characters */
  for (i = 0; i < game->n_characters; i++)
  {
    character_destroy(game->character[i]);
  }

  /* Destroy all the spaces */
  for (i = 0; i < game->n_spaces; i++)
  {
    space_destroy(game->spaces[i]);
  }

  /* Destroy the links */
  for (i = 0; i < game->n_links; i++)
  {
    link_destroy(game->links[i]);
  }

  free(game);

  return OK;
}

/*-------------------SPACE-----------------------*/
/**
 * @brief Adds a space to the game.
 */
Status game_add_space(Game *game, Space *space)
{
  if (!game || !space || game->n_spaces >= MAX_SPACES)
    return ERROR;

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

/**
 * @brief Gets a space by its position in the array.
 */
Space *game_get_space_at(Game *game, int position)
{
  if (!game || position < 0 || position >= game->n_spaces)
    return NULL;

  return game->spaces[position];
}

/**
 * @brief Gets the number of spaces in the game.
 */
int game_get_n_spaces(Game *game)
{
  if (!game)
    return -1;

  return game->n_spaces;
}

/**
 * @brief It gets a space by its id
 */
Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

Bool game_space_have_characters(Game *game, Id space_id)
{

  if (game == NULL || space_id == NO_ID)
  {
    return FALSE;
  }
  if (set_get_n_ids(game_get_characters_by_space(game, space_id)) > 0)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

int game_space_number_of_enemies(Game *game, Id space_id)
{
  int i;
  Id *id_list = NULL;
  Set *characters = NULL;
  int n_ids, counter = 0;
  Character *ch = NULL;

  if (game == NULL || space_id == NO_ID)
  {
    return -1;
  }

  if (game_space_have_characters(game, space_id) == FALSE)
  {
    return 0;
  }

  if ((characters = game_get_characters_by_space(game, space_id)) == NULL)
  {
    return -1;
  }

  id_list = set_get_list_ids(characters);
  n_ids = set_get_n_ids(characters);
  for (i = 0; i < n_ids; i++)
  {
    ch = game_get_character_by_id(game, id_list[i]);
    if (character_get_health(ch) > 0)
    {
      if (character_get_friendly(ch) == FALSE)
      {
          counter++;
      }
    }
  }
  return counter;
}

int game_get_number_of_followers(Game *game, Player *player)
{
  int i, counter = 0;
  Id player_id = NO_ID;
  if (game == NULL || player == NULL)
  {
    return -1;
  }
  player_id = player_get_id(player);
  if (player_id == NO_ID)
  {
    return -1;
  }
  for (i = 0; i < game->n_characters; i++)
  {
    if (character_get_following(game->character[i]) == player_id)
    {
      if (character_get_health(game->character[i]) > 0)
        counter++;
    }
  }
  return counter;
}

Character *game_space_with_boss(Game *game, Space *space) /*We have define that the max number of bosses in a space is 1*/
{
  Set *character_set = NULL;
  Id *char_ids = NULL;
  int i, n_characters = 0;

  if (game == NULL || space == NULL)
  {
    return NULL;
  }
  character_set = space_get_character(space);
  char_ids = set_get_list_ids(character_set);
  n_characters = set_get_n_ids(character_set);
  for (i = 0; i < n_characters; i++)
  {
    if (character_get_boss(game_get_character(game, char_ids[i])) == TRUE)
    {
      return game_get_character(game, char_ids[i]);
    }
  }
  return NULL;
}

/*ACABAR*/
int game_get_number_of_boss_in_space(Game *game, Space *space)
{
  Set *char_set = NULL;
  Id *char_ids = NULL;
  int i = 0, n_characters = 0, n_bosses = 0;
  if (game == NULL || space == NULL)
  {
    return -1;
  }

  if (game_space_with_boss(game, space) == FALSE)
  {
    return 0;
  }

  char_set = space_get_character(space);
  char_ids = set_get_list_ids(char_set);
  n_characters = set_get_n_ids(char_set);
  for (i = 0; i < n_characters; i++)
  {
    if (character_get_boss(game_get_character(game, char_ids[i])) == TRUE)
    {
      n_bosses++;
    }
  }
  return n_bosses;
}

/*-------------------OBJECT-----------------------*/
/**
 * @brief Gets the number of objects in the game.
 */
int game_get_n_objects(Game *game)
{
  if (!game)
    return -1;

  return game->n_objects;
}

/**
 * @brief It gets a object by its id
 */
Object *game_get_object(Game *game, Id id)
{
  int i = 0;

  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < game->n_objects; i++)
  {
    if (id == object_get_id(game->object[i]))
    {
      return game->object[i];
    }
  }

  return NULL;
}

/**
 * @brief Adds an object to the game
 */
Status game_add_object(Game *game, Object *object)
{

  if (!game || !object)
  {
    return ERROR;
  }

  if (game->n_objects >= MAX_OBJECTS)
  {
    return ERROR;
  }

  game->object[game->n_objects] = object;
  game->n_objects++;

  return OK;
}

/**
 * @brief It gets the object location
 */
Id game_get_object_location(Game *game, Id id)
{
  int i;

  if (!game)
    return NO_ID;

  /* Si el jugador tiene el objeto */
  for (i = 0; i < game->n_players; i++)
  {
    if (player_has_object(game->players[i], id) == TRUE)
      return player_get_location(game->players[i]);
  }

  /* Buscar en los espacios */
  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_has_object(game->spaces[i], id))
      return space_get_id(game->spaces[i]);
  }

  return NO_ID;
}

/**
 * @brief It sets the object location
 */
Status game_set_object_location(Game *game, Id object_id, Id space_id)
{
  int i;
  Space *space;

  if (!game || object_id == NO_ID || space_id == NO_ID)
  {
    return ERROR;
  }
  for (i = 0; i < game->n_players; i++)
  {
    if (player_has_object(game->players[i], object_id))
    {
      player_del_object(game->players[i], object_id);
      return OK;
    }
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    space_del_object(game->spaces[i], object_id);
  }

  space = game_get_space(game, space_id);

  if (!space)
  {
    return ERROR;
  }

  space_add_object(space, object_id);

  return OK;
}

/**
 * @brief It gets the object id by the object name
 */
Id game_get_object_id_by_name(Game *game, const char *name)
{
  int i;
  if (!game || !name)
    return NO_ID;

  for (i = 0; i < game->n_objects && i < MAX_OBJECTS; i++)
  {
    if (game->object[i] && strcasecmp(object_get_name(game->object[i]), name) == 0)
    {
      return object_get_id(game->object[i]);
    }
  }
  return NO_ID;
}

/**
 * @brief Gets an object by its position in the array
 */
Object *game_get_object_by_position(Game *game, int pos)
{
  if (!game || pos < 0 || pos >= game->n_objects)
    return NULL;

  return game->object[pos];
}

/*-------------------CHARACTER-----------------------*/
/**
 * @brief It adds a character to the game
 */
Status game_add_character(Game *game, Character *character)
{

  if (!game || !character)
  {
    return ERROR;
  }
  if (game->n_characters >= MAX_CHARACTERS)
  {
    return ERROR;
  }

  game->character[game->n_characters] = character;
  game->n_characters++;

  return OK;
}

/**
 * @brief It gets the character of the game
 */
Character *game_get_character(Game *game, Id id)
{
  int i;

  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < game->n_characters; i++)
  {
    if (character_get_id(game->character[i]) == id)
      return game->character[i];
  }

  return NULL;
}

/**
 * @brief It gets the character location
 */
Id game_get_character_location(Game *game, Id id)
{
  Character *character = game_get_character(game, id);

  if (!character)
    return NO_ID;

  return character_get_location(character);
}

/**
 * @brief It sets the character location
 */
Status game_set_character_location(Game *game, Id char_id, Id space_id)
{
  Character *character = game_get_character(game, char_id);

  if (!game || !character || space_id == NO_ID)
    return ERROR;

  return character_set_location(character, space_id);
}

/**
 * @brief Gets the number of character in the game.
 */
int game_get_n_characters(Game *game)
{
  if (!game)
    return -1;
  return game->n_characters;
}

/**
 * @brief Gets a character by its position in the array
 */
Character *game_get_character_by_position(Game *game, int pos)
{

  if (!game || pos < 0 || pos >= game->n_characters)
    return NULL;

  return game->character[pos];
}

Set *game_get_characters_by_space(Game *game, Id space_id)
{
  Space *space = NULL;
  if (!game || space_id == NO_ID)
    return NULL;

  if ((space = game_get_space(game, space_id)) == NULL)
  {
    return NULL;
  }
  return space_get_character(space);
}

Character *game_get_character_by_id(Game *game, Id chr_id)
{
  int i;
  if (!game || chr_id == NO_ID)
    return NULL;
  for (i = 0; i < game->n_characters; i++)
  {
    if (character_get_id(game->character[i]) == chr_id)
    {
      return game->character[i];
    }
  }
  return NULL;
}

/**
 * @brief It gets the character id by the character name
 */
Id game_get_character_id_by_name(Game *game, const char *name)
{
  int i;
  if (!game || !name)
    return NO_ID;

  for (i = 0; i < game->n_characters && i < MAX_CHARACTERS; i++)
  {
    if (game->character[i] && strcasecmp(character_get_name(game->character[i]), name) == 0)
    {
      return character_get_id(game->character[i]);
    }
  }
  return NO_ID;
}

Character *game_get_nth_follower(Game *game, Id player_id, int n)
{
  int i, count = 0;

  if (!game || player_id == NO_ID || n < 0)
  {
    return NULL;
  }

  for (i = 0; i < game->n_characters; i++)
  {
    if (game->character[i] != NULL && character_get_following(game->character[i]) == player_id && character_get_health(game->character[i]) > 0)
    {
      if (count == n)
      {
        return game->character[i];
      }
      count++;
    }
  }

  return NULL;
}

/*-------------------PLAYER-----------------------*/
/**
 * @brief It adds a player to the game
 */
Status game_add_player(Game *game, Player *player)
{
  Interface_Data *intdata = NULL;
  if (!game || !player)
  {
    return ERROR;
  }

  intdata = interface_data_create();
  if (intdata == NULL)
  {
    return ERROR;
  }
  game->players[game->n_players] = player;
  if (game_add_interface_data(game, intdata) == ERROR)
  {
    interface_data_destroy(intdata);
    return ERROR;
  }
  game->n_players++;
  return OK;
}

/**
 * @brief It gets the player of the game
 */
Player *game_get_player(Game *game)
{
  if (!game)
  {
    return NULL;
  }

  return game->players[game->turn];
}

/**
 * @brief It gets the player location
 */
Id game_get_player_location(Game *game)
{
  if (!game)
    return NO_ID;

  return player_get_location(game_get_player(game));
}

/**
 * @brief It sets the player location
 */
Status game_set_player_location(Game *game, Id space_id, Id player_id)
{
  Player *player = NULL;
  if (!game || space_id == NO_ID || player_id == NO_ID)
  {
    return ERROR;
  }
  player = game_get_player_from_id(game, player_id);
  if (player != NULL)
  {
    player_set_location(player, space_id);
    return OK;
  }
  return ERROR;
}

Status game_next_turn(Game *game)
{
  if (game == NULL)
  {
    return ERROR;
  }
  game->turn = (game->turn + 1) % game->n_players;
  return OK;
}

int game_get_turn(Game *game)
{
  if (game == NULL)
  {
    return -1;
  }
  return game->turn;
}

int game_get_n_players(Game *game)
{
  if (game == NULL)
  {
    return -1;
  }
  return game->n_players;
}

Player *game_get_player_from_id(Game *game, Id id)
{
  int i;
  if (game == NULL || id == NO_ID)
  {
    return NULL;
  }
  for (i = 0; i < game->n_players; i++)
  {
    if (player_get_id(game->players[i]) == id)
    {
      return game->players[i];
    }
  }

  return NULL;
}

Bool game_is_any_player_death(Game *game)
{
  int i;
  if (game == NULL)
  {
    return TRUE;
  }
  for (i = 0; i < game->n_players; i++)
  {
    if (player_get_health(game->players[i]) <= 0)
    {
      return TRUE;
    }
  }
  return FALSE;
}

int game_count_followers(Game *game, Id player_id)
{
  int count = 0;
  int i = 0;
  Character *chr = NULL;
  if (!game || player_id == NO_ID)
  {
    return 0;
  }

  for (i = 0; i < game->n_characters; i++)
  {
    chr = game->character[i];
    if (chr != NULL && character_get_following(chr) == player_id && character_get_health(chr) > 0)
    {
      count++;
    }
  }
  return count;
}

/*----------------------LINK--------------------------*/
Status game_add_link(Game *game, Link *link)
{
  if (!game || !link)
    return ERROR;

  if (game->n_links >= MAX_LINKS)
    return ERROR;

  game->links[game->n_links] = link;
  game->n_links++;

  return OK;
}

Id game_get_connection(Game *game, Id space_id, Direction dir)
{
  int i;

  if (!game || space_id == NO_ID)
    return NO_ID;

  for (i = 0; i < game->n_links; i++)
  {
    if (link_get_origin(game->links[i]) == space_id && link_get_direction(game->links[i]) == dir)
    {
      return link_get_destination(game->links[i]);
    }
  }

  return NO_ID;
}

Bool game_connection_is_open(Game *game, Id space_id, Direction dir)
{
  int i;

  if (!game || space_id == NO_ID)
    return FALSE;

  for (i = 0; i < game->n_links; i++)
  {
    if (link_get_origin(game->links[i]) == space_id && link_get_direction(game->links[i]) == dir)
    {
      return link_get_open(game->links[i]);
    }
  }

  return FALSE;
}

Link *game_get_link_by_id(Game *game, Id link_id)
{
  int i;

  if (!game || link_id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < game->n_links; i++)
  {
    if (link_get_id(game->links[i]) == link_id)
      return game->links[i];
  }

  return NULL;
}

Id game_get_link_id_by_name(Game *game, const char *name)
{
  int i;
  if (!game || !name)
    return NO_ID;

  for (i = 0; i < game->n_links && i < MAX_LINKS; i++)
  {
    if (game->links[i] && strcasecmp(link_get_name(game->links[i]), name) == 0)
    {
      return link_get_id(game->links[i]);
    }
  }
  return NO_ID;
}

Link *game_get_link(Game *game, Id origin, Id destination)
{
  int i;
  if (game == NULL || origin == NO_ID || destination == NO_ID)
  {
    return NULL;
  }
  for (i = 0; i < game->n_links; i++)
  {
    if ((link_get_origin(game->links[i]) == origin) && (link_get_destination(game->links[i]) == destination))
    {
      return game->links[i];
    }
  }
  return NULL;
}

Id game_get_link_destination(Game *game, Id origin, Direction dir)
{
  int i;

  if (game == NULL || origin == NO_ID || dir == NO_DIRECTION)
  {
    return NO_ID;
  }

  for (i = 0; i < game->n_links; i++)
  {
    if ((link_get_origin(game->links[i]) == origin) && (link_get_direction(game->links[i]) == dir))
    {
      return link_get_destination(game->links[i]);
    }
  }

  return NO_ID;
}

/*-------------------LAST COMMAND-----------------------*/
/**
 * @brief It gets the last command
 */
Command *game_get_last_command(Game *game)
{
  if (!game)
    return NULL;

  return interface_data_get_last_cmd(game->intdata[game->turn]);
}

/**
 * @brief It sets the last command
 */
Status game_set_last_command(Game *game, Command *command)
{
  if (game == NULL || command == NULL)
  {
    return ERROR;
  }
  return interface_data_set_last_cmd(game->intdata[game->turn], command);
}

/*-------------------FINISH-----------------------*/
/**
 * @brief It gets the finished flag
 */
Bool game_get_finished(Game *game)
{
  return game->finished;
}

/**
 * @brief It sets the finished flag
 */
Status game_set_finished(Game *game, Bool finished)
{
  game->finished = finished;
  return OK;
}

/*-----------------LAST ACTION---------------------*/
/**
 * @brief Gets the result of the last action executed
 */
Status game_get_last_action(Game *game)
{
  if (!game)
    return ERROR;

  return interface_data_get_last_action_status(game->intdata[game->turn]);
}

/**
 * @brief Sets the result of the last action executed
 */
Status game_set_last_action(Game *game, Status status)
{
  if (!game)
  {
    return ERROR;
  }
  return interface_data_set_last_action_status(game->intdata[game->turn], status);
}

/*-----------------LAST MESSAGE---------------------*/
/**
 * @brief Gets the last chat message stored in the game.
 */
char *game_get_last_chat(Game *game)
{

  if (!game)
  {
    return NULL;
  }

  return interface_data_get_last_chat(game->intdata[game->turn]);
}

/**
 * @brief Sets the last chat message generated in the game.
 */
Status game_set_last_chat(Game *game, const char *msg)
{
  if (!game || !msg)
  {
    return ERROR;
  }

  return interface_data_set_last_chat(game->intdata[game->turn], msg);
}

/*-----------------LAST DESCRIPTION---------------------*/
/**
 * @brief Gets the last object description stored in the game.
 */
char *game_get_last_obj_desc(Game *game)
{

  if (!game)
    return NULL;

  return interface_data_get_last_desc(game->intdata[game->turn]);
}

/**
 * @brief Sets the last object description generated in the game.
 */
Status game_set_last_obj_desc(Game *game, const char *desc)
{
  if (!game || !desc)
    return ERROR;

  return interface_data_set_last_desc(game->intdata[game->turn], desc);
}

/*-------------------INTERFACE_DATA-----------------------*/
/**
 * @brief It adds an interface data to the game
 */
Status game_add_interface_data(Game *game, Interface_Data *intdata)
{
  if (game == NULL || intdata == NULL || game->n_players >= MAX_PLAYERS)
  {
    return ERROR;
  }

  game->intdata[game->n_players] = intdata;

  return OK;
}

/*-------------------DETERMINISTIC-----------------------*/
/**
 * @brief It sets the deterministic flag of the game
 */
Status game_set_deterministic(Game *game, Bool deterministic)
{
  if (!game)
    return ERROR;

  game->deterministic = deterministic;

  return OK;
}

/**
 * @brief It gets the deterministic flag of the game
 */
Bool game_get_deterministic(Game *game)
{
  if (!game)
    return FALSE;

  return game->deterministic;
}

/*-------------------PRINT-----------------------*/
/**
 * @brief It prints the game information
 */
void game_print(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces:\n");
  for (i = 0; i < game->n_spaces; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Players:\n");
  for (i = 0; i < game->n_players; i++)
  {
    player_print(game->players[i]);
  }

  for (i = 0; i < game->n_characters; i++)
    character_print(game->character[i]);

  printf("=> Objects:\n");
  for (i = 0; i < game->n_objects; i++)
  {
    object_print(game->object[i]);
  }
}
