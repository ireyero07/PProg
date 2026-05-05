/**
 * @brief It tests character module
 *
 * @file character_test.c
 * @author Gonzalez Hijano, Ivan
 * @version 0.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "character_test.h"
#include "test.h"

#define MaX_TESTS 39 /*!< Total number of character tests */

/**
 * @brief Main function for CHaRaCTER unit tests.
 *
 * You may execute aLL or a SINGLE test
 *   1.- No parameter -> aLL test are executed
 *   2.- a number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv)
{

  int test = 0;
  int all = 1;

  if (argc < 2)
  {
    printf("Running all test for module Character:\n");
  }
  else
  {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MaX_TESTS)
    {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)
    test1_character_create();
  if (all || test == 2)
    test2_character_create();

  if (all || test == 3)
    test1_character_destroy();
  if (all || test == 4)
    test2_character_destroy();

  if (all || test == 5)
    test1_character_get_id();
  if (all || test == 6)
    test2_character_get_id();

  if (all || test == 7)
    test1_character_set_name();
  if (all || test == 8)
    test2_character_set_name();

  if (all || test == 9)
    test1_character_get_name();
  if (all || test == 10)
    test2_character_get_name();

  if (all || test == 11)
    test1_character_set_gdesc();
  if (all || test == 12)
    test2_character_set_gdesc();
  if (all || test == 13)
    test3_character_set_gdesc();

  if (all || test == 14)
    test1_character_get_gdesc();
  if (all || test == 15)
    test2_character_get_gdesc();

  if (all || test == 16)
    test1_character_set_health();
  if (all || test == 17)
    test2_character_set_health();
  if (all || test == 18)
    test3_character_set_health();

  if (all || test == 19)
    test1_character_get_health();
  if (all || test == 20)
    test2_character_get_health();

  if (all || test == 21)
    test1_character_set_message();
  if (all || test == 22)
    test2_character_set_message();
  if (all || test == 23)
    test3_character_set_message();

  if (all || test == 24)
    test1_character_get_message();
  if (all || test == 25)
    test2_character_get_message();

  if (all || test == 26)
    test1_character_set_friendly();
  if (all || test == 27)
    test2_character_set_friendly();

  if (all || test == 28)
    test1_character_get_friendly();
  if (all || test == 29)
    test2_character_get_friendly();

  if (all || test == 30)
    test1_character_print();
  if (all || test == 31)
    test2_character_print();

  if (all || test == 32)
    test1_character_get_location();
  if (all || test == 33)
    test2_character_get_location();

  if (all || test == 34)
    test1_character_set_location();
  if (all || test == 35)
    test2_character_set_location();
  if (all || test == 36)
    test3_character_set_location();

  if (all || test == 37)
    test1_character_set_id();
  if (all || test == 38)
    test2_character_set_id();
  if (all || test == 39)
    test3_character_set_id();
  
  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_character_create()
{
  Character *c = NULL;
  PRINT_TEST_RESULT((c = character_create(1)) != NULL);
  character_destroy(c);
}
void test2_character_create()
{
  PRINT_TEST_RESULT(character_create(NO_ID) == NULL);
}

void test1_character_destroy()
{
  Character *c = NULL;
  PRINT_TEST_RESULT(character_destroy(c) == ERROR);
}
void test2_character_destroy()
{
  Character *c = NULL;
  c = character_create(1);
  PRINT_TEST_RESULT(character_destroy(c) == OK);
}

void test1_character_get_id()
{
  Character *c = NULL;
  c = character_create(1);
  PRINT_TEST_RESULT(character_get_id(c) == 1);
  character_destroy(c);
}
void test2_character_get_id()
{
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

void test1_character_set_name()
{
  Character *c = NULL;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_name(c, "Nombre") == OK);
  character_destroy(c);
}
void test2_character_set_name()
{
  Character *c = NULL;
  char *name = NULL;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_name(c, name) == ERROR);
  character_destroy(c);
}

void test1_character_get_name()
{
  Character *c = NULL;
  c = character_create(1);
  character_set_name(c, "Nombre");
  PRINT_TEST_RESULT(character_get_name(c) != NULL);
  character_destroy(c);
}
void test2_character_get_name()
{
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test1_character_set_gdesc()
{
  Character *c = NULL;
  char big_gdesc[210];
  int i;
  c = character_create(1);
  for(i=0; i<210; i++){
    big_gdesc[i]='a';
  }
  PRINT_TEST_RESULT(character_set_gdesc(c, big_gdesc) == OK);
  character_destroy(c);
}
void test2_character_set_gdesc()
{
  Character *c = NULL;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_gdesc(c, "DESC") == OK);
  character_destroy(c);
}
void test3_character_set_gdesc()
{
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_gdesc(c, "DESC") == ERROR);
}

void test1_character_get_gdesc()
{
  Character *c = NULL;
  c = character_create(1);
  character_set_gdesc(c, "DESC");
  PRINT_TEST_RESULT(character_get_gdesc(c) != NULL);
  character_destroy(c);
}

void test2_character_get_gdesc()
{
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}

void test1_character_set_health()
{
  Status result;
  Character *c;
  c = character_create(5);
  result = character_set_health(c, 2);
  PRINT_TEST_RESULT(result == OK);
  character_destroy(c);
}
void test2_character_set_health()
{
  Status result;
  Character *c = NULL;
  result = character_set_health(c, 2);
  PRINT_TEST_RESULT(result == ERROR);
}
void test3_character_set_health()
{
  Status result;
  Character *c;
  c = character_create(5);
  result = character_set_health(c, -3);
  PRINT_TEST_RESULT(result == OK);
  character_destroy(c);
}

void test1_character_get_health()
{
  int result;
  Character *c;
  c = character_create(5);
  result = character_get_health(c);
  PRINT_TEST_RESULT(result != -1);
  character_destroy(c);
}
void test2_character_get_health()
{
  int result;
  Character *c = NULL;
  result = character_get_health(c);
  PRINT_TEST_RESULT(result == 0);
}

void test1_character_set_message()
{
  Status result;
  Character *c;
  c = character_create(5);
  result = character_set_message(c, "hola");
  PRINT_TEST_RESULT(result == OK);
  character_destroy(c);
}
void test2_character_set_message()
{
  Status result;
  Character *c;
  c = character_create(5);
  result = character_set_message(c, NULL);
  PRINT_TEST_RESULT(result == ERROR);
  character_destroy(c);
}
void test3_character_set_message()
{
  Status result;
  Character *c = NULL;
  result = character_set_message(c, "hola");
  PRINT_TEST_RESULT(result == ERROR);
}

void test1_character_get_message()
{
  Character *c;
  c = character_create(5);
  PRINT_TEST_RESULT(character_get_message(c) != NULL);
  character_destroy(c);
}
void test2_character_get_message()
{
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_message(c) == NULL);
}

void test1_character_set_friendly()
{
  Status result;
  Character *c;
  c = character_create(5);
  result = character_set_friendly(c, TRUE);
  PRINT_TEST_RESULT(result == OK);
  character_destroy(c);
}
void test2_character_set_friendly()
{
  Status result;
  Character *c = NULL;
  result = character_set_friendly(c, TRUE);
  PRINT_TEST_RESULT(result == ERROR);
}

void test1_character_get_friendly()
{
  Bool result;
  Character *c;
  c = character_create(5);
  result = character_get_friendly(c);
  PRINT_TEST_RESULT(result != -1);
  character_destroy(c);
}
void test2_character_get_friendly()
{
  Bool result;
  Character *c = NULL;
  result = character_get_friendly(c);
  PRINT_TEST_RESULT(result == FALSE);
}

void test1_character_print()
{
  Status result;
  Character *c;
  c = character_create(5);
  result = character_print(c);
  PRINT_TEST_RESULT(result == OK);
  character_destroy(c);
}
void test2_character_print()
{
  Status result;
  Character *c = NULL;
  result = character_print(c);
  PRINT_TEST_RESULT(result == ERROR);
}


/** @brief Tests character_get_location with NULL character */
void test1_character_get_location(){
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_location(c) == NO_ID);
}
/** @brief Tests character_get_location with valid character */
void test2_character_get_location(){
  Character *c = NULL;
  Id c_id=0;
  c=character_create(5);
  character_set_location(c, 5);
  c_id = character_get_location(c);
  PRINT_TEST_RESULT(c_id == 5);
  character_destroy(c);
}

/** @brief Tests character_set_location with valid parameters */
void test1_character_set_location(){
  Character *c = NULL;
  c=character_create(5);
  PRINT_TEST_RESULT(character_set_location(c, 5) == OK);
  character_destroy(c);
}

/** @brief Tests character_set_location with NO_ID */
void test2_character_set_location(){
  Character *c = NULL;
  c=character_create(5);
  PRINT_TEST_RESULT(character_set_location(c, NO_ID) == OK);
  character_destroy(c);
}

/** @brief Tests character_set_location with NULL character */
void test3_character_set_location(){
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_location(c, 5) == ERROR);
}

/** @brief Tests character_set_id with valid parameters */
void test1_character_set_id(){
  Character *c = NULL;
  c=character_create(5);
  PRINT_TEST_RESULT(character_set_id(c, 5) == OK);
  character_destroy(c);
}
/** @brief Tests character_set_id with NO_ID */
void test2_character_set_id(){
  Character *c = NULL;
  c=character_create(5);
  PRINT_TEST_RESULT(character_set_id(c, NO_ID) == ERROR);
  character_destroy(c);
}
/** @brief Tests character_set_id with NULL character */
void test3_character_set_id(){
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_id(c, 5) == ERROR);
}
