/**
 * @brief It implements the character
 *
 * @file character.c
 * @author Jian Feng Yin Chen
 * @version 0
 * @date 20-02-2026
 * @copyright GNU Public License
 */

#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Character
 *
 * This struct stores all the information of a character.
 */
struct _Character {
  Id id;                         /*!< Id number of the character */
  char name[WORD_SIZE + 1];      /*!< Name of the character */
  char gdesc[MAX_CHR_GDESC + 1];      /*!< Graphic description of the character */
  int health;                     /*!< Health of the character */
  Bool friendly;                  /*!< if the character is friendly */ 
  char message[WORD_SIZE + 1];   /*!< The message of the character */
  Id location;                   /*!< Location of the character*/
  Id following;                   /*!< The Id of the player that the character is following*/
};

/**
 * @brief It creates a new character
 */
Character* character_create(Id id) {
    Character* newCharacter = NULL;
    int i;

    if (id == NO_ID) return NULL;

    newCharacter = (Character*)calloc(1, sizeof(Character));
    if (!newCharacter) return NULL;

    newCharacter->id = id;
    newCharacter->name[0] = '\0';
    newCharacter->health = 5;

    for(i = 0; i<6; i++){
        newCharacter->gdesc[i]= '\0';
    }

    newCharacter->friendly = FALSE;
    newCharacter->message[0] = '\0';
    newCharacter->location = NO_ID;
    newCharacter->following = NO_ID;

  return newCharacter;
}

Status character_destroy(Character* character){
  if (!character) return ERROR;

  free(character);
  return OK;
}


Id character_get_id(Character* character){
  if (!character) return NO_ID;

  return character->id;
}

const char* character_get_name(Character* character){
  if (!character) return NULL;

  return character->name;
}

const char* character_get_gdesc(Character* character){
  if (!character) return NULL;

  return character->gdesc;
}

int character_get_health(Character* character){
  if (!character) return 0;

  return character->health;
}

Bool character_get_friendly(Character* character){
  if (!character) return FALSE;

  return character->friendly;
}

const char* character_get_message(Character* character){
  if (!character) return NULL;

  return character->message;
}

Id character_get_location(Character *character){
  if (!character)
    return NO_ID;

  return character->location;
}

Id character_get_following(Character *character){
  if (!character)
    return NO_ID;

  return character->location;
}

Status character_set_id(Character* character, Id id){
  if (!character || id == NO_ID) return ERROR;

  character->id = id;
  return OK;
}

Status character_set_name(Character* character, char* name){
  if (!character || !name) return ERROR;

  strcpy(character->name,name);
  return OK;
}

Status character_set_gdesc(Character* character, char* gdesc){
  if (!character || !gdesc) return ERROR;

  strncpy(character->gdesc, gdesc, MAX_CHR_GDESC);
  character->gdesc[MAX_CHR_GDESC]='\0';
  return OK;
}

Status character_set_health(Character* character, int health){
  if (!character || health < 0) return ERROR;

  character->health = health;
  return OK;
}
Status character_set_friendly(Character* character, Bool friendly){
if (!character) return ERROR;

character->friendly = friendly;
  return OK;
}

Status character_set_message(Character* character, char* message){
  if (!character || !message) return ERROR;

  strcpy(character->message, message);
  return OK;
}

Status character_set_location(Character *character, Id location){
  if (!character || location == NO_ID)
    return ERROR;

  character->location = location;

  return OK;
}

Status character_get_following(Character *character, Id following){
  if (!character || following == NO_ID);
    return ERROR;

  character->following = following;

  return OK;
}

Status character_print(Character* character){
  if (!character) return ERROR;

  fprintf(stdout, "--> Character (Id: %ld; Name: %s)\n", character->id, character->name);
  
  fprintf(stdout, "---> Health: %d\n", character->health);
  
  if (character->friendly == TRUE)
    fprintf(stdout, "---> Friendly: Yes\n");
  else
    fprintf(stdout, "---> Friendly: No\n");

  fprintf(stdout, "---> gdesc: %s\n", character->gdesc);

  fprintf(stdout, "---> Message: %s\n", character->message);

  if (character->following != NO_ID)
    fprintf(stdout, "---> Following player Id: %d\n",character->following);
  else
    fprintf(stdout, "---> Following no one\n");

    return OK;
} 

