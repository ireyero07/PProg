/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @author Gonzalez Hijano, Ivan
 * @version 0.0
 * @date 11-04-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 36 /*!< Total number of object tests */

/**
 * @brief Main function for OBJECT unit tests.
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
    printf("Running all test for module Object:\n");
  }
  else
  {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS)
    {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)
    test1_object_create();
  if (all || test == 2)
    test2_object_create();
  if (all || test == 3)
    test1_object_set_name();
  if (all || test == 4)
    test2_object_set_name();
  if (all || test == 5)
    test3_object_set_name();
  if (all || test == 6)
    test1_object_set_description();
  if (all || test == 7)
    test2_object_set_description();
  if (all || test == 8)
    test3_object_set_description();
  if (all || test == 9)
    test1_object_destroy();
  if (all || test == 10)
    test2_object_destroy();
  if (all || test == 11)
    test1_object_get_id();
  if (all || test == 12)
    test2_object_get_id();
  if (all || test == 13)
    test1_object_get_name();
  if (all || test == 14)
    test2_object_get_name();
  if (all || test == 15)
    test1_object_get_description();
  if (all || test == 16)
    test2_object_get_description();
  if (all || test == 17)
    test1_object_print();
  if (all || test == 18)
    test2_object_print();
  if (all || test == 19)
    test1_object_set_health();
  if (all || test == 20)
    test2_object_set_health();
  if (all || test == 21)
    test1_object_get_health();
  if (all || test == 22)
    test2_object_get_health();
  if (all || test == 23)
    test1_object_set_movable();
  if (all || test == 24)
    test2_object_set_movable();
  if (all || test == 25)
    test1_object_get_movable();
  if (all || test == 26)
    test2_object_get_movable();
  if (all || test == 27)
    test1_object_set_dependency();
  if (all || test == 28)
    test2_object_set_dependency();
  if (all || test == 29)
    test3_object_set_dependency();
  if (all || test == 30)
    test1_object_get_dependency();
  if (all || test == 31)
    test2_object_get_dependency();
  if (all || test == 32)
    test1_object_set_open();
  if (all || test == 33)
    test2_object_set_open();
  if (all || test == 34)
    test3_object_set_open();
  if (all || test == 35)
    test1_object_get_open();
  if (all || test == 36)
    test2_object_get_open();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_object_create()
{
  int result;
  Object *o;
  o = object_create(5);
  result = o != NULL;
  PRINT_TEST_RESULT(result);
  object_destroy(o);
}

void test2_object_create()
{
  Object *o;
  o = object_create(4);
  PRINT_TEST_RESULT(object_get_id(o) == 4);
  object_destroy(o);
}

void test1_object_set_name()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_name(o, "hola") == OK);
  object_destroy(o);
}

void test2_object_set_name()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_name(o, "hola") == ERROR);
}

void test3_object_set_name()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
  object_destroy(o);
}

void test1_object_set_description()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_description(o, "description") == OK);
  object_destroy(o);
}

void test2_object_set_description()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_description(o, "description") == ERROR);
}

void test3_object_set_description()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_description(o, NULL) == ERROR);
  object_destroy(o);
}

void test1_object_destroy()
{
  Object *o = NULL;
  o = object_create(1);
  PRINT_TEST_RESULT(object_destroy(o) == OK);
}

void test2_object_destroy()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_destroy(o) == ERROR);
}

void test1_object_get_id()
{
  Object *o;
  o = object_create(25);
  PRINT_TEST_RESULT(object_get_id(o) == 25);
  object_destroy(o);
}

void test2_object_get_id()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}

void test1_object_get_name()
{
  Object *o;
  o = object_create(1);
  object_set_name(o, "adios");
  PRINT_TEST_RESULT(strcmp(object_get_name(o), "adios") == 0);
  object_destroy(o);
}

void test2_object_get_name()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_name(o) == NULL);
}

void test1_object_get_description()
{
  Object *o;
  o = object_create(1);
  object_set_description(o, "desc");
  PRINT_TEST_RESULT(strcmp(object_get_description(o), "desc") == 0);
  object_destroy(o);
}

void test2_object_get_description()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_description(o) == NULL);
}

void test1_object_print()
{
  Object *o;
  o = object_create(1);
  PRINT_TEST_RESULT(object_print(o) == OK);
  object_destroy(o);
}

void test2_object_print()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_print(o) == ERROR);
}

void test1_object_set_health()
{
  Object *obj = NULL;
  int health = 5;
  PRINT_TEST_RESULT(object_set_health(obj, health) == ERROR);
}

void test2_object_set_health()
{
  Object *obj = NULL;
  int health = 5;
  obj = object_create(10);
  PRINT_TEST_RESULT(object_set_health(obj, health) == OK);
  object_destroy(obj);
}

void test1_object_get_health()
{
  Object *obj = NULL;
  int health = 5;
  obj = object_create(10);
  object_set_health(obj, health);
  PRINT_TEST_RESULT(object_get_health(obj) == 5);
  object_destroy(obj);
}
void test2_object_get_health()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_health(obj) == -1);
}

void test1_object_set_movable()
{
  Object *obj = NULL;
  obj = object_create(10);
  PRINT_TEST_RESULT(object_set_movable(obj, TRUE) == OK);
  object_destroy(obj);
}

void test2_object_set_movable()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_movable(obj, TRUE) == ERROR);
}

void test1_object_get_movable()
{
  Object *obj = NULL;
  obj = object_create(10);
  object_set_movable(obj, TRUE);
  PRINT_TEST_RESULT(object_get_movable(obj) == TRUE);
  object_destroy(obj);
}

void test2_object_get_movable()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_movable(obj) == FALSE);
}

void test1_object_set_dependency()
{
  Object *obj = NULL;
  obj = object_create(10);
  PRINT_TEST_RESULT(object_set_dependency(obj, 10) == OK);
  object_destroy(obj);
}

void test2_object_set_dependency()
{
  Object *obj = NULL;
  obj = object_create(10);
  PRINT_TEST_RESULT(object_set_dependency(obj, -5) == ERROR);
  object_destroy(obj);
}

void test3_object_set_dependency()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_dependency(obj, -5) == ERROR);
}

void test1_object_get_dependency()
{
  Object *obj = NULL;
  obj = object_create(10);
  object_set_dependency(obj, 10);
  PRINT_TEST_RESULT(object_get_dependency(obj) == 10);
  object_destroy(obj);
}

void test2_object_get_dependency()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_dependency(obj) == NO_ID);
}

void test1_object_set_open()
{
  Object *obj = NULL;
  obj = object_create(10);
  PRINT_TEST_RESULT(object_set_open(obj, 10) == OK);
  object_destroy(obj);
}

void test2_object_set_open()
{
  Object *obj = NULL;
  obj = object_create(10);
  PRINT_TEST_RESULT(object_set_open(obj, -10) == ERROR);
  object_destroy(obj);
}

void test3_object_set_open()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_open(obj, 10) == ERROR);
}

void test1_object_get_open()
{
  Object *obj = NULL;
  obj = object_create(10);
  object_set_open(obj, 10);
  PRINT_TEST_RESULT(object_get_open(obj) == 10);
  object_destroy(obj);
}

void test2_object_get_open()
{
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_open(obj) == NO_ID);
}
