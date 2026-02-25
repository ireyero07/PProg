/** 
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author Ivan
 * @version 0.0 
 * @date 17-02-2025
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



  // por ejemplo: if (all || test == 1) test1_set_create();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}