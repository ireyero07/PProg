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
 
#define MAX_TESTS 19
 
int main(int argc, char** argv) {
  int test = 0;
  int all = 1;
 
  if (argc < 2) {
    printf("Running all test for module Link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }
 

if(all || test == 1) test1_link_create();
if(all || test == 2) test2_link_create();
if(all || test == 3) test1_link_destroy();
if(all || test == 4) test2_link_destroy();
if(all || test == 5) test1_link_get_id();
if(all || test == 6) test2_link_get_id();
if(all || test == 7) test1_link_set_name();
if(all || test == 8) test2_link_set_name();
if(all || test == 9) test3_link_set_name();
if(all || test == 10) test1_link_set_origin();
if(all || test == 11) test2_link_set_origin();
if(all || test == 12) test3_link_set_origin();
if(all || test == 13) test1_link_get_origin();
if(all || test == 14) test2_link_get_origin();
if(all || test == 15) test1_link_set_destination();
if(all || test == 16) test2_link_set_destination();
if(all || test == 17) test3_link_set_destination();
if(all || test == 18) test1_link_get_destination();
if(all || test == 19) test2_link_get_destination();
if(all || test == 20) test1_link_set_direction();
if(all || test == 21) test2_link_set_direction();
if(all || test == 22) test3_link_set_direction();
if(all || test == 23) test1_link_get_direction();
if(all || test == 24) test2_link_get_direction();
if(all || test == 25) test1_link_set_open();
if(all || test == 26) test2_link_set_open();
if(all || test == 27) test3_link_set_open();
if(all || test == 28) test1_link_get_open();
if(all || test == 29) test2_link_get_open();

 
  PRINT_PASSED_PERCENTAGE;
 
  return 1;
}
