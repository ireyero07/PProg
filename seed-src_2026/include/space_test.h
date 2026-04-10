/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Profesores Pprog
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL)
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test space_add_object
 * @pre Valid space and object Id
 * @post Output == OK
 */
void test1_space_add_object();

/**
 * @test Test space_add_object
 * @pre NULL space
 * @post Output == ERROR
 */
void test2_space_add_object();

/**
 * @test Test space_add_object duplicate
 * @pre Valid space and existing object Id
 * @post Output == ERROR
 */
void test3_space_add_object();

/**
 * @test Test space_del_object
 * @pre Valid space with object
 * @post Output == OK
 */
void test1_space_del_object();

/**
 * @test Test space_del_object
 * @pre NULL space
 * @post Output == ERROR
 */
void test2_space_del_object();

/**
 * @test Test deleting non-existing object
 * @pre Valid space without object
 * @post Output == ERROR
 */
void test3_space_del_object();

/**
 * @test Test space_get_objects
 * @pre Valid space with object
 * @post Output == OK
 */
void test1_space_get_objects();

/**
 * @test Test space_get_objects
 * @pre NULL space
 * @post Output == ERROR
 */
void test2_space_get_objects();

/**
 * @test Test space_has_object
 * @pre Space containing object
 * @post Returns TRUE
 */
void test1_space_has_object();

/**
 * @test Test space_has_object
 * @pre Space without object
 * @post Returns FALSE
 */
void test2_space_has_object();

/**
 * @test Test space_has_object with NULL space
 * @pre NULL space pointer
 * @post Returns FALSE
 */
void test3_space_has_object();

/**
 * @test Test space_get_id
 * @pre Valid space
 * @post Returns correct Id
 */
void test1_space_get_id();

/**
 * @test Test space_get_id
 * @pre NULL space
 * @post Returns NO_ID
 */
void test2_space_get_id();

/**
 * @test Test space_get_name
 * @pre Space with set name
 * @post Returns correct name
 */
void test1_space_get_name();

/**
 * @test Test space_get_name
 * @pre NULL space
 * @post Returns NULL
 */
void test2_space_get_name();

/**
 * @test Test space_set_gdesc
 * @pre Valid space, valid string and valid line index
 * @post Returns OK
 */
void test1_space_set_gdesc();

/**
 * @test Test space_set_gdesc
 * @pre NULL space
 * @post Returns ERROR
 */
void test2_space_set_gdesc();

/**
 * @test Test space_get_gdesc
 * @pre Space with graphic description
 * @post Returns correct string
 */
void test1_space_get_gdesc();

/**
 * @test Test space_get_gdesc
 * @pre NULL space
 * @post Returns NULL
 */
void test2_space_get_gdesc();


void test1_space_destroy();
void test2_space_destroy();
void test1_space_get_objects_ids();
void test2_space_get_objects_ids();
void test1_space_get_number_objects();
void test2_space_get_number_objects();
void test1_space_add_character();
void test2_space_add_character();
void test1_space_del_character();
void test2_space_del_character();
void test1_space_get_character();
void test2_space_get_character();
void test1_space_has_character();
void test2_space_has_character();
void test1_space_set_discovered();
void test2_space_set_discovered();
void test3_space_set_discovered();
void test1_space_get_discovered();
void test2_space_get_discovered();

#endif