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

#define MAX_SPACES 100
#define MAX_OBJECTS 10
#define MAX_CHARACTERS 10

/**
 * @brief Game
 *
 * This struct stores all the information related to the game state.
 */
struct _Game {
  Player *player;                /*!< Pointer to the player of the game */
  Object *object[MAX_OBJECTS];   /*!< Array of pointers to the object of the game */
  int n_objects;                 /*!< Number of objects currently in the game */
  Character *character[MAX_CHARACTERS];  /*!< Array of pointers to the character of the game */
  int n_characters;              /*!< Number of characters currently in the game */
  Space *spaces[MAX_SPACES];     /*!< Array of pointers to the spaces of the game */
  int n_spaces;                  /*!< Number of spaces currently in the game */
  Command *last_cmd;             /*!< Last command introduced by the player */
  Bool finished;                 /*!< Flag that indicates if the game has finished */
  Status last_action_status;     /*!< Status of the last action */
  char last_chat[WORD_SIZE];     /*!< Stores the last chat message generated in the game */
};


/**
 * @brief It creates a new game and initializes its members
 */
Game *game_create() {
  int i;
  Game *game = NULL;
  Character *character;

  game = (Game *)malloc(sizeof(Game));
  if (!game) return NULL;

  game->player = NULL;
  game->last_cmd = NULL;

  for (i = 0; i < MAX_SPACES; i++)
    game->spaces[i] = NULL;

  for (i = 0; i < MAX_OBJECTS; i++)
    game->object[i] = NULL;

  for (i = 0; i < MAX_CHARACTERS; i++)
    game->character[i] = NULL;

  game->n_spaces = 0;
  game->n_objects = 0;
  game->n_characters = 0;

  /* ---------------- PLAYER ---------------- */

  game->player = player_create(1);
  if (!game->player) {
    free(game);
    return NULL;
  }

  player_set_health(game->player, 5);

  /* ---------------- CHARACTER 1 (FRIEND) ---------------- */

  character = character_create(2);
  if (!character) {
    player_destroy(game->player);
    free(game);
    return NULL;
  }

  character_set_health(character, 3);
  character_set_friendly(character, TRUE);
  character_set_message(character, "Bienvenido a esta apasionante aventura");
  character_set_location(character, 13);

  game->character[game->n_characters] = character;
  game->n_characters++;

  /* ---------------- CHARACTER 2 (ENEMY) ---------------- */

  character = character_create(3);
  if (!character) {
    player_destroy(game->player);
    free(game);
    return NULL;
  }

  character_set_health(character, 2);
  character_set_friendly(character, FALSE);
  character_set_location(character, 14);

  game->character[game->n_characters] = character;
  game->n_characters++;

  /* ---------------- COMMAND ---------------- */

  game->last_cmd = command_create();
  if (!game->last_cmd) {
    player_destroy(game->player);
    free(game);
    return NULL;
  }

  /* ---------------- GAME STATE ---------------- */

  game->finished = FALSE;
  game->last_action_status = ERROR;

  strcpy(game->last_chat, "");

  return game;
}

/**
 * @brief It destroys the game, freeing all allocated memory
 */
Status game_destroy(Game *game) {
  int i = 0;

  if (!game) return ERROR;

  /* Destroy all the spaces */
  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

 /* Destroy the player */
  player_destroy(game->player); 

  /* Destroy the objects */
  for (i = 0; i < game->n_objects; i++) {
    object_destroy(game->object[i]);
  }

  /* Destroy the characters */
    for (i = 0; i < game->n_characters; i++) {
      character_destroy(game->character[i]);
    }

  /* Destroy the last command */
  command_destroy(game->last_cmd);

  free(game);

  return OK;
}

/*-------------------SPACE-----------------------*/
/**
 * @brief Adds a space to the game.
 */
Status game_add_space(Game *game, Space *space) {
  if (!game || !space || game->n_spaces >= MAX_SPACES) return ERROR;

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

/**
 * @brief Gets a space by its position in the array.
 */
Space *game_get_space_at(Game *game, int position) {
  if (!game || position < 0 || position >= game->n_spaces) return NULL;

  return game->spaces[position];
}

/**
 * @brief Gets the number of spaces in the game.
 */
int game_get_n_spaces(Game *game) {
  if (!game) return -1;

  return game->n_spaces;
}

/**
 * @brief It gets a space by its id
 */
Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

/*-------------------OBJECT-----------------------*/
/**
 * @brief Gets the number of objects in the game.
 */
int game_get_n_objects(Game *game) {
  if (!game) return -1;

  return game->n_objects;
}

/**
 * @brief It gets a object by its id
 */
Object *game_get_object(Game *game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_objects; i++) {
    if (id == object_get_id(game->object[i])) {
      return game->object[i];
    }
  }

  return NULL;
}

/**
 * @brief Adds an object to the game
 */
Status game_add_object(Game *game, Object *object) {

  if (!game || !object) {
    return ERROR;
  }
  
  if (game->n_objects >= MAX_OBJECTS) {
    return ERROR;
  }

  game->object[game->n_objects] = object;
  game->n_objects++;

  return OK;
}

/**
 * @brief It gets the object location
 */
Id game_get_object_location(Game *game, Id id) {
  int i;

  if (!game)
    return NO_ID;

    /* Si el jugador tiene el objeto */
  if (player_get_object(game->player) == id)
    return game_get_player_location(game);

    /* Buscar en los espacios */
  for (i = 0; i < game->n_spaces; i++) {
    if (space_has_object(game->spaces[i], id))
      return space_get_id(game->spaces[i]);
  }

  return NO_ID;
}

/**
 * @brief It sets the object location
 */
Status game_set_object_location(Game *game, Id object_id, Id space_id) {
  int i;
  Space *space;

  if (!game || object_id == NO_ID || space_id == NO_ID)
    return ERROR;

  if (player_get_object(game->player) == object_id)
    player_set_object(game->player, NO_ID);

  for (i = 0; i < game->n_spaces; i++)
    space_del_object(game->spaces[i], object_id);

  space = game_get_space(game, space_id);
  if (!space) return ERROR;

  space_add_object(space, object_id);

  return OK;
}

/**
 * @brief It gets the object id by the object name
 */
Id game_get_object_id_by_name(Game *game, const char *name){
  int i;
  if (!game || !name) return NO_ID;

  for (i = 0; i < game->n_objects && i < MAX_OBJECTS; i++){
    if (game->object[i] && strcasecmp(object_get_name(game->object[i]),name) == 0){
      return object_get_id(game->object[i]);
    }
  }
  return NO_ID;
}

/**
 * @brief Gets an object by its position in the array
 */
Object *game_get_object_by_position(Game *game, int pos) {
  if (!game || pos < 0 || pos >= game->n_objects)
    return NULL;

  return game->object[pos];
}

/*-------------------CHARACTER-----------------------*/
/**
 * @brief It gets the character of the game
 */
Character *game_get_character(Game *game, Id id) {
  int i;

  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_characters; i++) {
    if (character_get_id(game->character[i]) == id)
      return game->character[i];
  }

  return NULL;
}

/**
 * @brief It gets the character location
 */
Id game_get_character_location(Game *game, Id id) {
  Character *character = game_get_character(game, id);

  if (!character)
    return NO_ID;

  return character_get_location(character);
}

/**
 * @brief It sets the character location
 */
Status game_set_character_location(Game *game, Id char_id, Id space_id) {
  Character *character = game_get_character(game, char_id);

  if (!game || !character || space_id == NO_ID)
    return ERROR;

  return character_set_location(character, space_id);
}

/**
 * @brief Gets the number of character in the game.
 */
int game_get_n_characters(Game *game){
    if(!game) return -1;
    return game->n_characters;
}

/**
 * @brief Gets a character by its position in the array
 */
Character *game_get_character_by_position(Game *game, int pos) {

  if (!game || pos < 0 || pos >= game->n_characters)
    return NULL;

  return game->character[pos];
}

/*-------------------PLAYER-----------------------*/
/**
 * @brief It gets the player of the game
 */
Player *game_get_player(Game *game) {
  if (!game) {
    return NULL;
  }

  return game->player;
}

/**
 * @brief It gets the player location
 */
Id game_get_player_location(Game *game) {
  if (!game || !game->player)
    return NO_ID;

  return player_get_location(game->player);
}

/**
 * @brief It sets the player location
 */
Status game_set_player_location(Game *game, Id id) {
  if (!game || !game->player || id == NO_ID)
    return ERROR;

  return player_set_location(game->player, id);
}

/*-------------------LAST COMMAND-----------------------*/
/**
 * @brief It gets the last command
 */
Command* game_get_last_command(Game *game) {
  if (!game) return NULL;
  
  return game->last_cmd;
}

/**
 * @brief It sets the last command
 */
Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;
  return OK;
}

/*-------------------FINISH-----------------------*/
/**
 * @brief It gets the finished flag
 */
Bool game_get_finished(Game *game) {
  return game->finished;
}

/**
 * @brief It sets the finished flag
 */
Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;
  return OK;
}

/*-----------------LAST ACTION---------------------*/
/**
 * @brief Gets the result of the last action executed
 */
Status game_get_last_action_status(Game *game){
  if (!game)
    return ERROR;

  return game->last_action_status;
}

/**
 * @brief Sets the result of the last action executed
 */
Status game_set_last_action_status(Game *game, Status status){
  if (!game)
    return ERROR;

  game->last_action_status = status;
  return OK;
}

/*-----------------LAST MESSAGE---------------------*/
/**
 * @brief Gets the last chat message stored in the game.
 */
char *game_get_last_chat(Game *game){

  if(!game)
    return NULL;

  return game->last_chat;
}

/**
 * @brief Sets the last chat message generated in the game.
 */
Status game_set_last_chat(Game *game, const char *msg){

  if(!game || !msg)
    return ERROR;

  strcpy(game->last_chat, msg);

  return OK;
}

/*-------------------PRINT-----------------------*/
/**
 * @brief It prints the game information
 */
void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces:\n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }
  printf("=> Player:\n");
  player_print(game->player);

  for (i = 0; i < game->n_characters; i++)
    character_print(game->character[i]);
  
  printf("=> Objects:\n");
  for (i = 0; i < game->n_objects; i++) {
    object_print(game->object[i]);
  }
}

