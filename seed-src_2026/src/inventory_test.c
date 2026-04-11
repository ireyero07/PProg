/**
 * @brief It tests inventory module
 *
 * @file inventory_test.c
 * @author Jian Feng Yin Chen
 * @version 0.0
 * @date 20-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "inventory_test.h"
#include "test.h"

#define MAX_TESTS 24

int main(int argc, char **argv)
{
  int test = 0;
  int all = 1;

  if (argc < 2)
  {
    printf("Running all test for module Inventory:\n");
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
    test1_inventory_create();
  if (all || test == 2)
    test2_inventory_create();
  if (all || test == 3)
    test1_inventory_get_max_objs();
  if (all || test == 4)
    test2_inventory_get_max_objs();
  if (all || test == 5)
    test1_inventory_set_max_objs();
  if (all || test == 6)
    test2_inventory_set_max_objs();
  if (all || test == 7)
    test3_inventory_set_max_objs();
  if (all || test == 8)
    test1_inventory_add_object();
  if (all || test == 9)
    test2_inventory_add_object();
  if (all || test == 10)
    test3_inventory_add_object();
  if (all || test == 11)
    test1_inventory_del_object();
  if (all || test == 12)
    test2_inventory_del_object();
  if (all || test == 13)
    test3_inventory_del_object();
  if (all || test == 14)
    test1_inventory_has_object();
  if (all || test == 15)
    test2_inventory_has_object();
  if (all || test == 16)
    test3_inventory_has_object();
  if (all || test == 17)
    test1_inventory_get_objects();
  if (all || test == 18)
    test2_inventory_get_objects();
  if (all || test == 19)
    test1_inventory_get_number_objects();
  if (all || test == 20)
    test2_inventory_get_number_objects();
  if (all || test == 21)
    test1_inventory_destroy();
  if (all || test == 22)
    test2_inventory_destroy();
  if (all || test == 23)
    test1_inventory_ge23t_objects_ids();
  if (all || test == 24)
    test1_inventory_get_objects_ids();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_inventory_create()
{
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inv != NULL);
  inventory_destroy(inv);
}

void test2_inventory_create()
{
  Inventory *inv = inventory_create(3);
  PRINT_TEST_RESULT(inventory_get_max_objs(inv) == 3);
  inventory_destroy(inv);
}

void test1_inventory_get_max_objs()
{
  Inventory *inv = inventory_create(7);
  PRINT_TEST_RESULT(inventory_get_max_objs(inv) == 7);
  inventory_destroy(inv);
}

void test2_inventory_get_max_objs()
{
  PRINT_TEST_RESULT(inventory_get_max_objs(NULL) == -1);
}

void test1_inventory_set_max_objs()
{
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_set_max_objs(inv, 10) == OK);
  inventory_destroy(inv);
}

void test2_inventory_set_max_objs()
{
  PRINT_TEST_RESULT(inventory_set_max_objs(NULL, 10) == ERROR);
}

void test3_inventory_set_max_objs()
{
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_set_max_objs(inv, -1) == ERROR);
  inventory_destroy(inv);
}

void test1_inventory_add_object()
{
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_add_object(inv, 1) == OK);
  inventory_destroy(inv);
}

void test2_inventory_add_object()
{
  PRINT_TEST_RESULT(inventory_add_object(NULL, 1) == ERROR);
}

void test3_inventory_add_object()
{
  Inventory *inv = inventory_create(1);
  inventory_add_object(inv, 1);
  PRINT_TEST_RESULT(inventory_add_object(inv, 2) == ERROR);
  inventory_destroy(inv);
}

void test1_inventory_del_object()
{
  Inventory *inv = inventory_create(5);
  inventory_add_object(inv, 1);
  PRINT_TEST_RESULT(inventory_del_object(inv, 1) == OK);
  inventory_destroy(inv);
}

void test2_inventory_del_object()
{
  PRINT_TEST_RESULT(inventory_del_object(NULL, 1) == ERROR);
}

void test3_inventory_del_object()
{
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_del_object(inv, 1) == ERROR);
  inventory_destroy(inv);
}

void test1_inventory_has_object()
{
  Inventory *inv = inventory_create(5);
  inventory_add_object(inv, 10);
  PRINT_TEST_RESULT(inventory_has_object(inv, 10) == TRUE);
  inventory_destroy(inv);
}

void test2_inventory_has_object()
{
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_has_object(inv, 10) == FALSE);
  inventory_destroy(inv);
}

void test3_inventory_has_object()
{
  PRINT_TEST_RESULT(inventory_has_object(NULL, 10) == FALSE);
}

void test1_inventory_get_objects()
{
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_get_objects(inv) != NULL);
  inventory_destroy(inv);
}

void test2_inventory_get_objects()
{
  PRINT_TEST_RESULT(inventory_get_objects(NULL) == NULL);
}

void test1_inventory_get_number_objects()
{
  Inventory *inv = inventory_create(5);
  inventory_add_object(inv, 1);
  inventory_add_object(inv, 2);
  PRINT_TEST_RESULT(inventory_get_number_objects(inv) == 2);
  inventory_destroy(inv);
}

void test2_inventory_get_number_objects()
{
  PRINT_TEST_RESULT(inventory_get_number_objects(NULL) == -1);
}

void test1_inventory_destroy()
{
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_destroy(inv) == OK);
}

void test2_inventory_destroy()
{
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_destroy(inv) == ERROR);
}

void test1_inventory_get_objects_ids()
{
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_get_objects_ids(inv) == NULL);
}

void test2_inventory_get_objects_ids(){
  Inventory *inv = inventory_create(5);
  inventory_add_object(inv, 4);
  PRINT_TEST_RESULT(inventory_get_objects_ids(inv) != NULL);
  inventory_destroy(inv);
}
