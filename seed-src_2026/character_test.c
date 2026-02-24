
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



  if (all || test == 1) test1_character_create();
  if (all || test == 2) test2_character_create();
  if (all || test == 3) test1_character_get_id();
  if (all || test == 4) test2_character_get_id();
  if (all || test == 5) test1_character_get_name();
  if (all || test == 6) test2_character_get_name();
  if (all || test == 7) test1_character_get_gdesc();
  if (all || test == 8) test2_character_get_gdesc();
  if (all || test == 9) test1_character_get_health();
  if (all || test == 10) test2_character_get_health();
  if (all || test == 11) test1_character_get_friendly();
  if (all || test == 12) test2_character_get_friendly();
  if (all || test == 13) test1_character_get_message();
  if (all || test == 14) test2_character_get_message();
  if (all || test == 15) test1_character_set_name();
  if (all || test == 16) test2_character_set_name();
  if (all || test == 17) test1_character_set_gdesc();
  if (all || test == 18) test2_character_set_gdesc();
  if (all || test == 19) test1_character_set_health();
  if (all || test == 20) test2_character_set_health();
  if (all || test == 21) test1_character_set_friendly();
  if (all || test == 22) test2_character_set_friendly();
  if (all || test == 23) test1_character_set_message();
  if (all || test == 24) test2_character_set_message();


  PRINT_PASSED_PERCENTAGE;

  return 1;
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

void test1_character_get_id() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_get_id(c) == 1);
  character_destroy(c);
}

void test2_character_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

void test1_character_get_name() {
  Character *c;
  c = character_create(1);
  character_set_name(c, "hola");
  PRINT_TEST_RESULT(strcmp(character_get_name(c), "hola") == 0);
  character_destroy(c);
}

void test2_character_get_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test1_character_get_gdesc(){
  Character *c;
  c=character_create(1);
  character_set_gdesc(c, "hola");
  PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), "hola") == 0);
  character_destroy(c);
}

void test2_character_get_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}

void test1_character_get_health(){
  Character *c;
  c=character_create(1);
  character_set_health(c, 1);
  PRINT_TEST_RESULT(character_get_health(c) == 1);
  character_destroy(c);
}

void test2_character_get_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_health(c) == NULL);
}

void test1_character_get_friendly(){
  Character *c;
  c=character_create(1);
  character_set_friendly(c, TRUE);
  PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
  character_destroy(c);
}

void test2_character_get_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_friendly(c) == NULL);
}

void test1_character_get_message(){
  Character *c;
  c=character_create(1);
  character_set_message(c, "hola");
  PRINT_TEST_RESULT(strcmp(character_get_message(c), "hola") == 0);
  character_destroy(c);
}

void test2_character_get_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_message(c) == NULL);
}

void test1_character_set_name() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_name(c, "hola") == OK);
  character_destroy(c);
}

void test2_character_set_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_name(c, "hola") == ERROR);
}

void test1_character_set_gdesc() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_gdesc(c, "hola") == OK);
  character_destroy(c);
}

void test2_character_set_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_gdesc(c, "hola") == ERROR);
}

void test1_character_set_health() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_health(c, 1) == OK);
  character_destroy(c);
}

void test2_character_set_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_health(c, 1) == ERROR);
}

void test1_character_set_friendly() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK);
  character_destroy(c);
}

void test2_character_set_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR);
}

void test1_character_set_message() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_message(c, "hola") == OK);
  character_destroy(c);
}

void test2_character_set_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_message(c, "hola") == ERROR);
}

/**
 * @brief It prints a character
 * @author Jian Feng Yin Chen
 *
 * @param character a pointer to the character
 * @return OK if successful, ERROR if not
 */
Status character_print(Character* character);
