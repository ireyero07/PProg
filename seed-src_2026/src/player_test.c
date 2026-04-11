/**
 * @brief It tests player module
 *
 * @file player_test.c
 * @author Jian Feng Yin Chen
 * @version 0.0
 * @date 17-03-2026
 * @copyright GNU Public License
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "player_test.h"
#include "test.h"
 
#define MAX_TESTS 36
 
int main(int argc, char** argv) {
  int test = 0;
  int all = 1;
 
  if (argc < 2) {
    printf("Running all test for module Player:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }
 
  if (all || test == 1) test1_player_create();
  if (all || test == 2) test2_player_create();
  if (all || test == 3) test1_player_get_id();
  if (all || test == 4) test2_player_get_id();
  if (all || test == 5) test1_player_set_name();
  if (all || test == 6) test2_player_set_name();
  if (all || test == 7) test3_player_set_name();
  if (all || test == 8) test1_player_get_name();
  if (all || test == 9) test2_player_get_name();
  if (all || test == 10) test1_player_set_location();
  if (all || test == 11) test2_player_set_location();
  if (all || test == 12) test1_player_get_location();
  if (all || test == 13) test2_player_get_location();
  if (all || test == 14) test1_player_add_object();
  if (all || test == 15) test2_player_add_object();
  if (all || test == 16) test3_player_add_object();
  if (all || test == 17) test1_player_del_object();
  if (all || test == 18) test2_player_del_object();
  if (all || test == 19) test3_player_del_object();
  if (all || test == 20) test1_player_has_object();
  if (all || test == 21) test2_player_has_object();
  if (all || test == 22) test3_player_has_object();
  if (all || test == 23) test1_player_get_objects();
  if (all || test == 24) test2_player_get_objects();
  if (all || test == 25) test1_player_get_backpack();
  if (all || test == 26) test2_player_get_backpack();
  if (all || test == 27) test1_player_get_health();
  if (all || test == 28) test2_player_get_health();
  if (all || test == 29) test1_player_set_health();
  if (all || test == 30) test2_player_set_health();
  if (all || test == 31) test1_player_set_gdesc();
  if (all || test == 32) test2_player_set_gdesc();
  if (all || test == 33) test1_player_get_gdesc();
  if (all || test == 34) test2_player_get_gdesc();
  if (all || test == 35) test1_player_destroy();
  if (all || test == 36) test2_player_destroy();

 
  PRINT_PASSED_PERCENTAGE;
 
  return 1;
}

void test1_player_create() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(p != NULL);
  player_destroy(p);
}
 
void test2_player_create() {
  Player *p = player_create(NO_ID, 3);
  PRINT_TEST_RESULT(p == NULL);
}

void test1_player_get_id() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_get_id(p) == 5);
  player_destroy(p);
}
 
void test2_player_get_id() {
  PRINT_TEST_RESULT(player_get_id(NULL) == NO_ID);
}

void test1_player_set_name() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_set_name(p, "knight") == OK);
  player_destroy(p);
}
 
void test2_player_set_name() {
  PRINT_TEST_RESULT(player_set_name(NULL, "knight") == ERROR);
}
 
void test3_player_set_name() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_set_name(p, NULL) == ERROR);
  player_destroy(p);
}

void test1_player_get_name() {
  Player *p = player_create(5, 3);
  player_set_name(p, "knight");
  PRINT_TEST_RESULT(strcmp(player_get_name(p), "knight") == 0);
  player_destroy(p);
}
 
void test2_player_get_name() {
  PRINT_TEST_RESULT(player_get_name(NULL) == NULL);
}

void test1_player_set_location() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_set_location(p, 10) == OK);
  player_destroy(p);
}
 
void test2_player_set_location() {
  PRINT_TEST_RESULT(player_set_location(NULL, 10) == ERROR);
}

void test1_player_get_location() {
  Player *p = player_create(5, 3);
  player_set_location(p, 10);
  PRINT_TEST_RESULT(player_get_location(p) == 10);
  player_destroy(p);
}
 
void test2_player_get_location() {
  PRINT_TEST_RESULT(player_get_location(NULL) == NO_ID);
}

void test1_player_add_object() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_add_object(p, 10) == OK);
  player_destroy(p);
}
 
void test2_player_add_object() {
  PRINT_TEST_RESULT(player_add_object(NULL, 10) == ERROR);
}
 
void test3_player_add_object() {
  Player *p = player_create(5, 1);
  player_add_object(p, 10);
  PRINT_TEST_RESULT(player_add_object(p, 20) == ERROR);
  player_destroy(p);
}

void test1_player_del_object() {
  Player *p = player_create(5, 3);
  player_add_object(p, 10);
  PRINT_TEST_RESULT(player_del_object(p, 10) == OK);
  player_destroy(p);
}
 
void test2_player_del_object() {
  PRINT_TEST_RESULT(player_del_object(NULL, 10) == ERROR);
}
 
void test3_player_del_object() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_del_object(p, 10) == ERROR);
  player_destroy(p);
}

void test1_player_has_object() {
  Player *p = player_create(5, 3);
  player_add_object(p, 10);
  PRINT_TEST_RESULT(player_has_object(p, 10) == TRUE);
  player_destroy(p);
}
 
void test2_player_has_object() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_has_object(p, 10) == FALSE);
  player_destroy(p);
}
 
void test3_player_has_object() {
  PRINT_TEST_RESULT(player_has_object(NULL, 10) == FALSE);
}

void test1_player_get_objects() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_get_objects(p) != NULL);
  player_destroy(p);
}
 
void test2_player_get_objects() {
  PRINT_TEST_RESULT(player_get_objects(NULL) == NULL);
}

void test1_player_get_backpack() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_get_backpack(p) != NULL);
  player_destroy(p);
}
 
void test2_player_get_backpack() {
  PRINT_TEST_RESULT(player_get_backpack(NULL) == NULL);
}

void test1_player_get_health() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_get_health(p) == 5); 
  player_destroy(p);
}
 
void test2_player_get_health() {
  PRINT_TEST_RESULT(player_get_health(NULL) == 0);
}

void test1_player_set_health() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_set_health(p, 10) == OK);
  player_destroy(p);
}
 
void test2_player_set_health() {
  PRINT_TEST_RESULT(player_set_health(NULL, 10) == ERROR);
}

void test1_player_set_gdesc() {
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_set_gdesc(p, "^C>") == OK);
  player_destroy(p);
}
 
void test2_player_set_gdesc() {
  PRINT_TEST_RESULT(player_set_gdesc(NULL, "^C>") == ERROR);
}

void test1_player_get_gdesc(){
  Player *p = player_create(5, 3);
  player_set_gdesc(p, "^C>");
  PRINT_TEST_RESULT(strcmp(player_get_gdesc(p), "^C>")==0);
  player_destroy(p);
}

void test2_player_get_gdesc(){
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_gdesc(p)==NULL);
}

void test1_player_destroy(){
  Player *p = player_create(5, 3);
  PRINT_TEST_RESULT(player_destroy(p)==OK);
}

void test2_player_destroy(){
  Player *p = NULL;
  PRINT_TEST_RESULT(player_destroy(p) == ERROR);
}
