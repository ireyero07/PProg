/**
 * @brief It declares the tests for the object module
 *
 * @file object_test.h
 * @author Gonzalez HIjano, Ivan
 * @version 0.0
 * @date 11-04-2026
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
 * @test Test object creation
 * @pre Object ID
 * @post Non NULL pointer to object
 */
void test1_object_create();

/**
 * @test Test object creation
 * @pre Object ID
 * @post Object_ID == Supplied Object Id
 */
void test2_object_create();

/**
 * @test Test function for object_name setting
 * @pre String with object name
 * @post Output==OK
 */
void test1_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre pointer to object = NULL
 * @post Output==ERROR
 */
void test2_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre pointer to object_name = NULL (point to object = NON NULL)
 * @post Output==ERROR
 */
void test3_object_set_name();

/**
 * @test Test function for object_description setting
 * @pre String with object description
 * @post Output==OK
 */
void test1_object_set_description();

/**
 * @test Test function for object_description setting
 * @pre pointer to object = NULL
 * @post Output==ERROR
 */
void test2_object_set_description();

/**
 * @test Test function for object_description setting
 * @pre pointer to object_description = NULL (point to object = NON NULL)
 * @post Output==ERROR
 */
void test3_object_set_description();

/**
 * @test Test object_destroy
 * @pre Valid object
 * @post Returns OK
 */
void test1_object_destroy();

/**
 * @test Test object_destroy
 * @pre NULL object
 * @post Returns ERROR
 */
void test2_object_destroy();

/**
 * @test Test object_get_id
 * @pre Valid object
 * @post Returns correct Id
 */
void test1_object_get_id();

/**
 * @test Test object_get_id
 * @pre NULL object
 * @post Returns NO_ID
 */
void test2_object_get_id();

/**
 * @test Test object_get_name
 * @pre Object with set name
 * @post Returns correct name
 */
void test1_object_get_name();

/**
 * @test Test object_get_name
 * @pre NULL object
 * @post Returns NULL
 */
void test2_object_get_name();

/**
 * @test Test object_get_description
 * @pre Object with set description
 * @post Returns correct description
 */
void test1_object_get_description();

/**
 * @test Test object_get_description
 * @pre NULL object
 * @post Returns NULL
 */
void test2_object_get_description();

/**
 * @test Test object_print
 * @pre Valid object
 * @post Returns OK
 */
void test1_object_print();

/**
 * @test Test object_print
 * @pre NULL object
 * @post Returns ERROR
 */
void test2_object_print();

#endif
