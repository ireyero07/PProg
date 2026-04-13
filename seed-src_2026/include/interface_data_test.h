/**
 * @brief It declares the tests for the interface_data module
 *
 * @file interface_data_test.h
 * @author Gonzalez Hijano Ivan
 * @version 0.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#ifndef INTERFACE_DATA_TEST_H
#define INTERFACE_DATA_TEST_H

/**
 * @test Test interface_data creation
 * @pre Nothing
 * @post Non NULL pointer to interface_data
 */
void test1_interface_data_create();

/**
 * @test Test interface_data creation
 * @pre Nothing
 * @post Default last action status is OK
 */
void test2_interface_data_create();

/**
 * @test Test interface_data_destroy
 * @pre Valid interface_data
 * @post Output==OK
 */
void test1_interface_data_destroy();

/**
 * @test Test interface_data_destroy
 * @pre NULL interface_data
 * @post Output==ERROR
 */
void test2_interface_data_destroy();

/**
 * @test Test function for interface_data_set_last_cmd
 * @pre Valid interface_data and command
 * @post Output==OK
 */
void test1_interface_data_set_last_cmd();

/**
 * @test Test function for interface_data_set_last_cmd
 * @pre NULL interface_data
 * @post Output==ERROR
 */
void test2_interface_data_set_last_cmd();

/**
 * @test Test function for interface_data_set_last_cmd
 * @pre NULL command
 * @post Output==ERROR
 */
void test3_interface_data_set_last_cmd();

/**
 * @test Test function for interface_data_get_last_cmd
 * @pre Valid interface_data with command set
 * @post Returns correct command
 */
void test1_interface_data_get_last_cmd();

/**
 * @test Test function for interface_data_get_last_cmd
 * @pre NULL interface_data
 * @post Returns NULL
 */
void test2_interface_data_get_last_cmd();

/**
 * @test Test function for interface_data_set_last_action_status
 * @pre Valid interface_data and status
 * @post Output==OK
 */
void test1_interface_data_set_last_action_status();

/**
 * @test Test function for interface_data_set_last_action_status
 * @pre NULL interface_data
 * @post Output==ERROR
 */
void test2_interface_data_set_last_action_status();

/**
 * @test Test function for interface_data_get_last_action_status
 * @pre Valid interface_data with status set
 * @post Returns correct status
 */
void test1_interface_data_get_last_action_status();

/**
 * @test Test function for interface_data_get_last_action_status
 * @pre NULL interface_data
 * @post Returns ERROR
 */
void test2_interface_data_get_last_action_status();

/**
 * @test Test function for interface_data_set_last_chat
 * @pre Valid interface_data and message
 * @post Output==OK
 */
void test1_interface_data_set_last_chat();

/**
 * @test Test function for interface_data_set_last_chat
 * @pre NULL interface_data
 * @post Output==ERROR
 */
void test2_interface_data_set_last_chat();

/**
 * @test Test function for interface_data_set_last_chat
 * @pre NULL message
 * @post Output==ERROR
 */
void test3_interface_data_set_last_chat();

/**
 * @test Test function for interface_data_get_last_chat
 * @pre Valid interface_data with message set
 * @post Returns correct message
 */
/**
 * @test Test function for interface_data_get_last_chat
 * @pre NULL interface_data
 * @post Returns NULL
 */
void test2_interface_data_get_last_chat();

/**
 * @test Test function for interface_data_get_last_obj_desc
 * @pre Valid interface_data with description set
 * @post Returns correct description
 */
void test1_interface_data_get_last_obj_desc();

/**
 * @test Test function for interface_data_get_last_obj_desc
 * @pre NULL interface_data
 * @post Returns NULL
 */
void test2_interface_data_get_last_obj_desc();

/**
 * @test Test function for interface_data_set_last_obj_desc
 * @pre Valid interface_data and description
 * @post Output==OK
 */
void test1_interface_data_set_last_obj_desc();

/**
 * @test Test function for interface_data_set_last_obj_desc
 * @pre NULL interface_data
 * @post Output==ERROR
 */
void test2_interface_data_set_last_obj_desc();

/**
 * @test Test function for interface_data_set_last_obj_desc
 * @pre Valid interface_data and NULL description
 * @post Output==ERROR
 */
void test3_interface_data_set_last_obj_desc();
#endif