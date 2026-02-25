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
 * @test Test space_set_north
 * @pre Valid space and north Id
 * @post Output==OK
 */
void test1_space_set_north();

/**
 * @test Test space_set_north
 * @pre NULL space
 * @post Output==ERROR
 */
void test2_space_set_north();

/**
 * @test Test space_set_north  
 * @pre NULL north Id
 * @post Output==ERROR
 */
void test3_space_set_north();

/**
 * @test Test space_set_north edge case
 * @pre Valid parameters edge case
 * @post Correct behavior
 */
void test4_space_set_north();

/**
 * @test Test space_set_south
 * @pre Valid space and south Id
 * @post Output==OK
 */
void test1_space_set_south();

/**
 * @test Test space_set_south
 * @pre NULL space
 * @post Output==ERROR
 */
void test2_space_set_south();

/**
 * @test Test space_set_south
 * @pre NULL south Id
 * @post Output==ERROR
 */
void test3_space_set_south();

/**
 * @test Test space_set_south edge case
 * @pre Valid parameters edge case
 * @post Correct behavior
 */
void test4_space_set_south();

/**
 * @test Test space_set_east
 * @pre Valid space and east Id
 * @post Output==OK
 */
void test1_space_set_east();

/**
 * @test Test space_set_east
 * @pre NULL space
 * @post Output==ERROR
 */
void test2_space_set_east();

/**
 * @test Test space_set_east
 * @pre NULL east Id
 * @post Output==ERROR
 */
void test3_space_set_east();

/**
 * @test Test space_set_east edge case
 * @pre Valid parameters edge case
 * @post Correct behavior
 */
void test4_space_set_east();

/**
 * @test Test space_set_west
 * @pre Valid space and west Id
 * @post Output==OK
 */
void test1_space_set_west();

/**
 * @test Test space_set_west
 * @pre NULL space
 * @post Output==ERROR
 */
void test2_space_set_west();

/**
 * @test Test space_set_west
 * @pre NULL west Id
 * @post Output==ERROR
 */
void test3_space_set_west();

/**
 * @test Test space_set_west edge case
 * @pre Valid parameters edge case
 * @post Correct behavior
 */
void test4_space_set_west();

/**
 * @test Test space_set_object
 * @pre Valid space and object Id
 * @post Output==OK
 */
void test1_space_set_object();

/**
 * @test Test space_set_object
 * @pre NULL space
 * @post Output==ERROR
 */
void test2_space_set_object();

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
 * @test Test space_get_north
 * @pre Space with set north
 * @post Returns correct north Id
 */
void test1_space_get_north();

/**
 * @test Test space_get_north
 * @pre NULL space
 * @post Returns NO_ID
 */
void test2_space_get_north();

/**
 * @test Test space_get_south
 * @pre Space with set south
 * @post Returns correct south Id
 */
void test1_space_get_south();

/**
 * @test Test space_get_south
 * @pre NULL space
 * @post Returns NO_ID
 */
void test2_space_get_south();

/**
 * @test Test space_get_east
 * @pre Space with set east
 * @post Returns correct east Id
 */
void test1_space_get_east();

/**
 * @test Test space_get_east
 * @pre NULL space
 * @post Returns NO_ID
 */
void test2_space_get_east();

/**
 * @test Test space_get_west
 * @pre Space with set west
 * @post Returns correct west Id
 */
void test1_space_get_west();

/**
 * @test Test space_get_west
 * @pre NULL space
 * @post Returns NO_ID
 */
void test2_space_get_west();

/**
 * @test Test space_get_object
 * @pre Space with set object
 * @post Returns correct object Id
 */
void test1_space_get_object();

/**
 * @test Test space_get_object
 * @pre NULL space
 * @post Returns NO_ID
 */
void test2_space_get_object();

/**
 * @test Test space_get_object
 * @pre Empty object field
 * @post Returns NO_ID
 */
void test3_space_get_object();
#endif