/** 
 * @brief It tests set module
 * @file set_test.c
 * @author Ivan
 * @version 0.0 
 * @date 25-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "set_test.h"
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

  if (all || test == 1) test1_set_create();
  if (all || test == 2) test2_set_create();
  if (all || test == 3) test1_set_add();
  if (all || test == 4) test2_set_add();
  if (all || test == 5) test3_set_add();
  if (all || test == 6) test1_set_del();
  if (all || test == 7) test2_set_del();
  if (all || test == 8) test3_set_del();
  if (all || test == 9) test1_set_find();
  if (all || test == 10) test2_set_find();
  if (all || test == 11) test1_set_get_n_ids();
  if (all || test == 12) test2_set_get_n_ids();
  if (all || test == 13) test1_set_get_id_at();
  if (all || test == 14) test2_set_get_id_at();
  if (all || test == 15) test1_set_print();
  if (all || test == 16) test2_set_print();

  PRINT_PASSED_PERCENTAGE;

  return 1;
  }

  void test1_set_create() {
    Set *s = set_create();
    PRINT_TEST_RESULT(s != NULL);
    set_destroy(s);
  }

  void test2_set_create() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_get_n_ids(s) == 0);
    set_destroy(s);
  }

  void test1_set_add() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_add(s, 5) == OK);
    set_destroy(s);
  }

  void test2_set_add() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_add(s, 5) == ERROR);
  }

  void test3_set_add() {
    Set *s = set_create();
    set_add(s, 5);
    PRINT_TEST_RESULT(set_add(s, 5) == ERROR);
    set_destroy(s);
  }

  void test1_set_del() {
    Set *s = set_create();
    set_add(s, 7);
    PRINT_TEST_RESULT(set_del(s, 7) == OK);
    set_destroy(s);
  }

  void test2_set_del() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_del(s, 9) == ERROR);
    set_destroy(s);
  }

  void test3_set_del() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_del(s, 3) == ERROR);
  }

  void test1_set_find() {
    Set *s = set_create();
    set_add(s, 11);
    PRINT_TEST_RESULT(set_find(s, 11) != -1);
    set_destroy(s);
  }

  void test2_set_find() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_find(s, 99) == -1);
    set_destroy(s);
  }

  void test1_set_get_n_ids() {
    Set *s = set_create();
    set_add(s, 1);
    PRINT_TEST_RESULT(set_get_n_ids(s) == 1);
    set_destroy(s);
  }

  void test2_set_get_n_ids() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_get_n_ids(s) == -1);
  }

  void test1_set_get_id_at() {
    Set *s = set_create();
    set_add(s, 22);
    PRINT_TEST_RESULT(set_get_id_at(s,0) == 22);
    set_destroy(s);
  }

  void test2_set_get_id_at() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_get_id_at(s,5) == NO_ID);
    set_destroy(s);
  }

  void test1_set_print() {
    Set *s = set_create();
    set_add(s, 3);
    PRINT_TEST_RESULT(set_print(s) == OK);
    set_destroy(s);
  }

  void test2_set_print() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_print(s) == ERROR);
  }