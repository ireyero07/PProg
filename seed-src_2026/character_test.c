
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "character_test.h"
#include "test.h"

#define MAX_TESTS 30

int main(int argc, char** argv){
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }




    return 0;
}

void test1_character_create() {
  int result;
  Character *c;
  c = character_create(1);
  result=c!=NULL ;
  PRINT_TEST_RESULT(result);
  character_destroy(c);
}

void test2_character_create() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_get_id(c) == 1);
  character_destroy(c);
}

void test1_space_get_id() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_get_id(c) == 1);
  character_destroy(c);
}

void test2_space_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

void test1_character_get_name() {
  Character *c;
  c = character_create(1);
  character_set_name(c, "adios");
  PRINT_TEST_RESULT(strcmp(character_get_name(c), "adios") == 0);
  character_destroy(c);
}

void test2_character_get_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test1_character_get_gdesc(){
    Character *c;
    c=character_create(1);
    character_set_gdesc(c, " (o)1 ");
    PRINT_TEST_RESULT(strcmp(character_get_name(c), " (o)1 ") == 0);
    character_destroy(c);
}

void test2_character_get_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}




Status character_destroy(Character* character);

/**
 * @brief It gets the graphical description of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return the graphical description, NULL if error
 */
const char* character_get_gdesc(Character* character);

/**
 * @brief It gets the health of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return the health, -1 if error
 */
int character_get_health(Character* character);

/**
 * @brief It gets if a character is friendly
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return TRUE if friendly, FALSE if not, FALSE if error
 */
Bool character_get_friendly(Character* character);

/**
 * @brief It gets the message of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return the message, NULL if error
 */
const char* character_get_message(Character* character);

/**
 * @brief It sets the id of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param id the new identification number
 * @return OK if successful, ERROR if not
 */
Status character_set_id(Character* character, Id id);

/**
 * @brief It sets the name of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param name the new name
 * @return OK if successful, ERROR if not
 */
Status character_set_name(Character* character, char* name);

/**
 * @brief It sets the graphical description of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param gdesc the new graphical description
 * @return OK if successful, ERROR if not
 */
Status character_set_gdesc(Character* character, char* gdesc);

/**
 * @brief It sets the health of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param health the new health value
 * @return OK if successful, ERROR if not
 */
Status character_set_health(Character* character, int health);

/**
 * @brief It sets if a character is friendly
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param friendly TRUE if friendly, FALSE if not
 * @return OK if successful, ERROR if not
 */
Status character_set_friendly(Character* character, Bool friendly);

/**
 * @brief It sets the message of a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @param message the new message
 * @return OK if successful, ERROR if not
 */
Status character_set_message(Character* character, char* message);

/**
 * @brief It prints a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return OK if successful, ERROR if not
 */
Status character_print(Character* character);