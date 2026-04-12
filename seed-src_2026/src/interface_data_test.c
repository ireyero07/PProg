/**
 * @brief It tests interface_data module
 *
 * @file interface_data_test.c
 * @author Gonzalez Hijano Ivan
 * @version 0.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface_data.h"
#include "interface_data_test.h"
#include "command.h"
#include "test.h"

#define MAX_TESTS 18

/**
 * @brief Main function for INTERFACE DATA unit tests.
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
        printf("Running all test for module Interface data:\n");
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
        test1_interface_data_create();
    if (all || test == 2)
        test2_interface_data_create();
    if (all || test == 3)
        test1_interface_data_destroy();
    if (all || test == 4)
        test2_interface_data_destroy();
    if (all || test == 5)
        test1_interface_data_set_last_cmd();
    if (all || test == 6)
        test2_interface_data_set_last_cmd();
    if (all || test == 7)
        test3_interface_data_set_last_cmd();
    if (all || test == 8)
        test1_interface_data_get_last_cmd();
    if (all || test == 9)
        test2_interface_data_get_last_cmd();
    if (all || test == 10)
        test1_interface_data_set_last_action_status();
    if (all || test == 11)
        test2_interface_data_set_last_action_status();
    if (all || test == 12)
        test1_interface_data_get_last_action_status();
    if (all || test == 13)
        test2_interface_data_get_last_action_status();
    if (all || test == 14)
        test1_interface_data_set_last_chat();
    if (all || test == 15)
        test2_interface_data_set_last_chat();
    if (all || test == 16)
        test3_interface_data_set_last_chat();
    if (all || test == 17)
        test1_interface_data_get_last_chat();
    if (all || test == 18)
        test2_interface_data_get_last_chat();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_interface_data_create()
{
    int result;
    Interface_Data *id;
    id = interface_data_create();
    result = id != NULL;
    PRINT_TEST_RESULT(result);
    interface_data_destroy(id);
}

void test2_interface_data_create()
{
    Interface_Data *id = interface_data_create();
    PRINT_TEST_RESULT(interface_data_get_last_action_status(id) == OK); 
    interface_data_destroy(id);
}

void test1_interface_data_destroy()
{
    Interface_Data *id;
    id = interface_data_create();
    PRINT_TEST_RESULT(interface_data_destroy(id) == OK);
}

void test2_interface_data_destroy()
{
    Interface_Data *id = NULL;
    PRINT_TEST_RESULT(interface_data_destroy(id) == ERROR);
}

void test1_interface_data_set_last_cmd()
{
    Interface_Data *id;
    Command *cmd;
    id = interface_data_create();
    cmd = command_create();
    command_set_code(cmd, EXIT);
    PRINT_TEST_RESULT(interface_data_set_last_cmd(id, cmd) == OK);
    interface_data_destroy(id);
    command_destroy(cmd);
}

void test2_interface_data_set_last_cmd()
{
    Interface_Data *id = NULL;
    Command *cmd = command_create();
    command_set_code(cmd, EXIT);
    PRINT_TEST_RESULT(interface_data_set_last_cmd(id, cmd) == ERROR);
    command_destroy(cmd);
}

void test3_interface_data_set_last_cmd()
{
    Interface_Data *id;
    Command *cmd = NULL;
    id = interface_data_create();
    PRINT_TEST_RESULT(interface_data_set_last_cmd(id, cmd) == ERROR);
    interface_data_destroy(id);
}

void test1_interface_data_get_last_cmd()
{
    Interface_Data *id;
    Command *cmd, *cmd2;
    id = interface_data_create();
    cmd = command_create();
    command_set_code(cmd, EXIT);
    interface_data_set_last_cmd(id, cmd);
    cmd2 = interface_data_get_last_cmd(id);
    PRINT_TEST_RESULT(command_get_code(cmd) == command_get_code(cmd2));
    interface_data_destroy(id);
    command_destroy(cmd);
}

void test2_interface_data_get_last_cmd()
{
    Interface_Data *id = NULL;
    PRINT_TEST_RESULT(interface_data_get_last_cmd(id) == NULL);
}

void test1_interface_data_set_last_action_status()
{
    Interface_Data *id;
    id = interface_data_create();
    PRINT_TEST_RESULT(interface_data_set_last_action_status(id, OK) == OK);
    interface_data_destroy(id);
}

void test2_interface_data_set_last_action_status()
{
    Interface_Data *id = NULL;
    PRINT_TEST_RESULT(interface_data_set_last_action_status(id, OK) == ERROR);
}

void test1_interface_data_get_last_action_status()
{
    Interface_Data *id;
    id = interface_data_create();
    interface_data_set_last_action_status(id, OK);
    PRINT_TEST_RESULT(interface_data_get_last_action_status(id) == OK);
    interface_data_destroy(id);
}

void test2_interface_data_get_last_action_status()
{
    Interface_Data *id = NULL;
    PRINT_TEST_RESULT(interface_data_get_last_action_status(id) == ERROR);
}

void test1_interface_data_set_last_chat()
{
    Interface_Data *id;
    id = interface_data_create();
    PRINT_TEST_RESULT(interface_data_set_last_chat(id, "hello") == OK);
    interface_data_destroy(id);
}

void test2_interface_data_set_last_chat()
{
    Interface_Data *id = NULL;
    PRINT_TEST_RESULT(interface_data_set_last_chat(id, "hello") == ERROR);
}

void test3_interface_data_set_last_chat()
{
    Interface_Data *id;
    id = interface_data_create();
    PRINT_TEST_RESULT(interface_data_set_last_chat(id, NULL) == ERROR);
    interface_data_destroy(id);
}

void test1_interface_data_get_last_chat()
{
    Interface_Data *id;
    id = interface_data_create();
    interface_data_set_last_chat(id, "hello");
    PRINT_TEST_RESULT(strcmp(interface_data_get_last_chat(id), "hello") == 0);
    interface_data_destroy(id);
}

void test2_interface_data_get_last_chat()
{
    Interface_Data *id = NULL;
    PRINT_TEST_RESULT(interface_data_get_last_chat(id) == NULL);
}