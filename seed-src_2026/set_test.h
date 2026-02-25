/** 
 * @brief It declares the tests for the set module
 * @file set_test.h
 * @author Ivan
 * @version 0.0 
 * @date 25-02-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test set creation
 * @pre No parameters
 * @post Non NULL pointer to set
 */
void test1_set_create();

/**
 * @test Test set creation
 * @pre Set created
 * @post Number of ids == 0
 */
void test2_set_create();

/**
 * @test Test set_add
 * @pre Valid set and id
 * @post Output == OK
 */
void test1_set_add();

/**
 * @test Test set_add
 * @pre NULL set
 * @post Output == ERROR
 */
void test2_set_add();

/**
 * @test Test set_add duplicate
 * @pre Id already stored
 * @post Output == ERROR
 */
void test3_set_add();

/**
 * @test Test set_del
 * @pre Existing id in set
 * @post Output == OK
 */
void test1_set_del();

/**
 * @test Test set_del
 * @pre Non existing id
 * @post Output == ERROR
 */
void test2_set_del();

/**
 * @test Test set_del
 * @pre NULL set
 * @post Output == ERROR
 */
void test3_set_del();

/**
 * @test Test set_find
 * @pre Existing id
 * @post Position != -1
 */
void test1_set_find();

/**
 * @test Test set_find
 * @pre Non existing id
 * @post Output == -1
 */
void test2_set_find();

/**
 * @test Test set_get_n_ids
 * @pre Set with elements
 * @post Correct number returned
 */
void test1_set_get_n_ids();

/**
 * @test Test set_get_n_ids
 * @pre NULL set
 * @post Output == -1
 */
void test2_set_get_n_ids();

/**
 * @test Test set_get_id_at
 * @pre Valid position
 * @post Correct id returned
 */
void test1_set_get_id_at();

/**
 * @test Test set_get_id_at
 * @pre Invalid position
 * @post Output == NO_ID
 */
void test2_set_get_id_at();

/**
 * @test Test set_print
 * @pre Valid set
 * @post Output == OK
 */
void test1_set_print();

/**
 * @test Test set_print
 * @pre NULL set
 * @post Output == ERROR
 */
void test2_set_print();

#endif