/**
 * @brief It tests the link module
 *
 * @file link_test.c
 * @author Gonzalez Hijano, Ivan
 * @version 0.0
 * @date 02-04-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 30

int main(int argc, char **argv)
{
  int test = 0;
  int all = 1;

  if (argc < 2)
  {
    printf("Running all test for module Link:\n");
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
    test1_link_create();
  if (all || test == 2)
    test2_link_create();
  if (all || test == 3)
    test1_link_destroy();
  if (all || test == 4)
    test2_link_destroy();
  if (all || test == 5)
    test1_link_get_id();
  if (all || test == 6)
    test2_link_get_id();
  if (all || test == 7)
    test1_link_set_name();
  if (all || test == 8)
    test2_link_set_name();
  if (all || test == 9)
    test3_link_set_name();
  if (all || test == 10)
    test1_link_set_origin();
  if (all || test == 11)
    test2_link_set_origin();
  if (all || test == 12)
    test3_link_set_origin();
  if (all || test == 13)
    test1_link_get_origin();
  if (all || test == 14)
    test2_link_get_origin();
  if (all || test == 15)
    test1_link_set_destination();
  if (all || test == 16)
    test2_link_set_destination();
  if (all || test == 17)
    test3_link_set_destination();
  if (all || test == 18)
    test1_link_get_destination();
  if (all || test == 19)
    test2_link_get_destination();
  if (all || test == 20)
    test1_link_set_direction();
  if (all || test == 21)
    test2_link_set_direction();
  if (all || test == 22)
    test3_link_set_direction();
  if (all || test == 23)
    test1_link_get_direction();
  if (all || test == 24)
    test2_link_get_direction();
  if (all || test == 25)
    test1_link_set_open();
  if (all || test == 26)
    test2_link_set_open();
  if (all || test == 27)
    test1_link_get_open();
  if (all || test == 28)
    test2_link_get_open();
  if (all || test == 29)
    test1_link_get_name();
  if (all || test == 30)
    test2_link_get_name();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_link_create()
{
  Link *l = NULL;
  PRINT_TEST_RESULT((l = link_create(5)) != NULL);
  link_destroy(l);
}

void test2_link_create()
{
  Link *l = NULL;
  PRINT_TEST_RESULT((l = link_create(NO_ID)) == NULL);
}

void test1_link_destroy()
{
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT((link_destroy(l)) == OK);
}

void test2_link_destroy()
{
  Link *l = NULL;
  PRINT_TEST_RESULT((link_destroy(l)) == ERROR);
}

void test1_link_get_id(){
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT((link_get_id(l)) == 5);
  link_destroy(l);
}

void test2_link_get_id(){
  Link *l = NULL;
  PRINT_TEST_RESULT((link_get_id(l)) == NO_ID);
}

void test1_link_set_name(){
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT((link_set_name(l, "link")) == OK);
  link_destroy(l);
}

void test2_link_set_name(){
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT((link_set_name(l, NULL)) == ERROR);
  link_destroy(l);
}

void test3_link_set_name(){
  Link *l = NULL;
  PRINT_TEST_RESULT((link_set_name(l, "link")) == ERROR);
}

void test1_link_set_origin(){
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT((link_set_origin(l, 5)) == OK);
  link_destroy(l);
}

void test2_link_set_origin(){
  Link *l = NULL;
  PRINT_TEST_RESULT((link_set_origin(l, 5)) == ERROR);
}

void test3_link_set_origin(){
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT((link_set_origin(l, NO_ID)) == ERROR);
  link_destroy(l);
}

void test1_link_get_origin(){
  Link *l = NULL;
  Id l_id=10;
  l = link_create(5);
  link_set_origin(l, l_id);
  PRINT_TEST_RESULT(link_get_origin(l) == l_id);
  link_destroy(l);
}

void test2_link_get_origin(){
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_origin(l) == NO_ID);
}

void test1_link_set_destination(){
  Link *l = NULL;
  Id l_id=10;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_destination(l, l_id) == OK);
  link_destroy(l);
}
void test2_link_set_destination(){
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_destination(l, NO_ID) == ERROR);
  link_destroy(l);
}

void test3_link_set_destination(){
  Link *l = NULL;
  Id l_id=10;
  PRINT_TEST_RESULT(link_set_destination(l, l_id) == ERROR);
}

void test1_link_get_destination(){
  Link *l = NULL;
  Id l_id=10;
  l = link_create(5);
  link_set_destination(l, l_id);
  PRINT_TEST_RESULT(link_get_destination(l) == l_id);
  link_destroy(l);
}

void test2_link_get_destination(){
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_destination(l) == NO_ID);
}

void test1_link_set_direction(){
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_direction(l, N) == OK);
  link_destroy(l);
}

void test2_link_set_direction(){
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_direction(l, N) == ERROR);
}

void test3_link_set_direction(){
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_direction(l, -1) == ERROR);
  link_destroy(l);
}

void test1_link_get_direction(){
  Link *l = NULL;
  l = link_create(5);
  link_set_direction(l, N);
  PRINT_TEST_RESULT(link_get_direction(l) == N);
  link_destroy(l);
}

void test2_link_get_direction(){
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_direction(l) == -1);
}

void test1_link_set_open(){
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_open(l, TRUE) == OK);
  link_destroy(l);
}

void test2_link_set_open(){
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_open(l, TRUE) == ERROR);
}

void test1_link_get_open(){
  Link *l = NULL;
  l = link_create(5);
  link_set_open(l, FALSE);
  PRINT_TEST_RESULT(link_get_open(l) == FALSE);
  link_destroy(l);
}

void test2_link_get_open(){
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_open(l) == FALSE);
}

void test1_link_get_name(){
  Link *l = NULL;
  l = link_create(5);
  link_set_name(l, "name");
  PRINT_TEST_RESULT((strcmp(link_get_name(l), "name")) == 0);
  link_destroy(l);
}

void test2_link_get_name(){
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_name(l) == NULL);
}
