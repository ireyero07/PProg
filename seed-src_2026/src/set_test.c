/**
 * @brief It tests set module
 *
 * @file set_test.c
 * @author Mijangos Alvarez, Ivan
 * @version 0.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 23 /*!< Total number of set tests */

/**
 * @brief Main function for SET unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv)
{

  int test = 0;
  int all = 1;

  if (argc < 2)
  {
    printf("Running all test for module Set:\n");
  }
  else
  {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS)
    {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)
    test1_set_create();
  if (all || test == 2)
    test1_set_destroy();
  if (all || test == 3)
    test2_set_destroy();
  if (all || test == 4)
    test1_set_add();
  if (all || test == 5)
    test2_set_add();
  if (all || test == 6)
    test3_set_add();
  if (all || test == 7)
    test1_set_del();
  if (all || test == 8)
    test2_set_del();
  if (all || test == 9)
    test3_set_del();
  if (all || test == 10)
    test1_set_print();
  if (all || test == 11)
    test2_set_print();
  if (all || test == 12)
    test3_set_print();
  if (all || test == 13)
    test1_set_get_id_at();
  if (all || test == 14)
    test2_set_get_id_at();
  if (all || test == 15)
    test3_set_get_id_at();
  if (all || test == 16)
    test1_set_get_n_ids();
  if (all || test == 17)
    test2_set_get_n_ids();
  if (all || test == 18)
    test1_set_get_list_ids();
  if (all || test == 19)
    test2_set_get_list_ids();
  if (all || test == 20)
    test3_set_get_list_ids();
  if (all || test == 21)
    test1_set_find();
  if (all || test == 22)
    test2_set_find();
  if (all || test == 23)
    test3_set_find();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_set_create()
{
  int result;
  Set *s;
  s = set_create();
  result = s != NULL;
  PRINT_TEST_RESULT(result);
  set_destroy(s);
}

void test1_set_destroy()
{
  Status result;
  Set *s = set_create();
  result = set_destroy(s);
  PRINT_TEST_RESULT(result == OK);
}

void test2_set_destroy()
{
  Status result;
  Set *s = NULL;
  result = set_destroy(s);
  PRINT_TEST_RESULT(result == ERROR);
}

void test1_set_add()
{
  Status result;
  Set *s = set_create();
  result = set_add(s, 20);
  PRINT_TEST_RESULT(result == OK);
  set_destroy(s);
}

void test2_set_add()
{
  Status result;
  Set *s = NULL;
  result = set_add(s, 20);
  PRINT_TEST_RESULT(result == ERROR);
}

void test3_set_add()
{
  Status result;
  Set *s = set_create();
  set_add(s, 20);
  result = set_add(s, 20);
  PRINT_TEST_RESULT(result == ERROR);
  set_destroy(s);
}

void test1_set_del()
{
  Status result;
  Set *s = set_create();
  set_add(s, 20);
  result = set_del(s, 20);
  PRINT_TEST_RESULT(result == OK);
  set_destroy(s);
}

void test2_set_del()
{
  Status result;
  Set *s = NULL;
  result = set_del(s, 20);
  PRINT_TEST_RESULT(result == ERROR);
}

void test3_set_del()
{
  Status result;
  Set *s = set_create();
  result = set_del(s, NO_ID);
  PRINT_TEST_RESULT(result == ERROR);
  set_destroy(s);
}

void test1_set_print()
{
  Status result;
  Set *s = set_create();
  result = set_print(s);
  PRINT_TEST_RESULT(result == OK);
  set_destroy(s);
}

void test2_set_print()
{
  Status result;
  Set *s = set_create();
  set_add(s, 10);
  result = set_print(s);
  PRINT_TEST_RESULT(result == OK);
  set_destroy(s);
}

void test3_set_print()
{
  Status result;
  Set *s = NULL;
  result = set_print(s);
  PRINT_TEST_RESULT(result == ERROR);
}

void test1_set_get_id_at()
{
  Set *set = NULL;
  set = set_create();
  PRINT_TEST_RESULT(set_get_id_at(set, 1) == NO_ID);
  set_destroy(set);
}

void test2_set_get_id_at()
{
  Set *set = NULL;
  PRINT_TEST_RESULT(set_get_id_at(set, 1) == NO_ID);
}

void test3_set_get_id_at()
{
  Set *set = NULL;
  long i;
  set = set_create();
  for (i = 0; i < 5; i++)
  {
    set_add(set, i);
  }
  PRINT_TEST_RESULT(set_get_id_at(set, 3) != NO_ID);
  set_destroy(set);
}

void test1_set_get_n_ids()
{
  Set *set = NULL;
  long i;
  set = set_create();
  for (i = 0; i < 5; i++)
  {
    set_add(set, i);
  }
  PRINT_TEST_RESULT(set_get_n_ids(set) == 5);
  set_destroy(set);
}

void test2_set_get_n_ids()
{
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_n_ids(s) == -1);
}

void test1_set_get_list_ids()
{
  Set *set = NULL;
  set = set_create();
  PRINT_TEST_RESULT(set_get_list_ids(set) != NULL);
  set_destroy(set);
}

void test2_set_get_list_ids()
{
  Set *set = NULL;
  PRINT_TEST_RESULT(set_get_list_ids(set) == NULL);
}

void test3_set_get_list_ids()
{
  Set *set = NULL;
  long i;
  set = set_create();
  for (i = 0; i < 5; i++)
  {
    set_add(set, i);
  }
  PRINT_TEST_RESULT(set_get_list_ids(set) != NULL);
  set_destroy(set);
}

void test1_set_find(){
  Set *set = NULL;
  set = set_create();
  set_add(set, 1);
  PRINT_TEST_RESULT(set_find(set, 1) == 0);
  set_destroy(set);
}

void test2_set_find(){
  Set *set = NULL;
  PRINT_TEST_RESULT(set_find(set, 1) == -1);
}

void test3_set_find(){
  Set *set = NULL;
  set = set_create();
  PRINT_TEST_RESULT(set_find(set, 1) == -1);
  set_destroy(set);
}