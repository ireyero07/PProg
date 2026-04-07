/** 
 * @brief It declares the tests for the set module
 * 
 * @file set_test.h
 * @author Gonzalez Hijano, Ivan
 * @version 0.0  
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test set creation
 * @pre None
 * @post Non NULL pointer to set
 */
void test1_set_create();

/**
 * @test Test destroying a set
 * @pre Pointer to set
 * @post Output == OK
 */
void test1_set_destroy();

/**
 * @test Test destroying a set
 * @pre pointer to set = NULL 
 * @post Output==ERROR
 */
void test2_set_destroy();

/**
 * @test Test adding an id to a set
 * @pre Pointer to set and an id
 * @post Output==OK
 */
void test1_set_add();

/**
 * @test Test adding an id to a set
 * @pre pointer to set = NULL 
 * @post Output==ERROR
 */
void test2_set_add();

/**
 * @test Test adding an id to a set
 * @pre Pointer to set and a duplicated id
 * @post Output==ERROR
 */
void test3_set_add();

/**
 * @test Test deleting an id from a set
 * @pre Pointer to set and an id
 * @post Output==OK
 */
void test1_set_del();

/**
 * @test Test deleting an id from a set
 * @pre pointer to set = NULL 
 * @post Output==ERROR
 */
void test2_set_del();

/**
 * @test Test deleting an id from a set
 * @pre Pointer to set and a NO_ID
 * @post Output==ERROR
 */
void test3_set_del();

/**
 * @test Test printing a set
 * @pre Pointer to an empty set
 * @post Output==OK
 */
void test1_set_print();

/**
 * @test Test printing a set
 * @pre Pointer to a set with an id
 * @post Output==OK
 */
void test2_set_print();

/**
 * @test Test printing a set
 * @pre pointer to set = NULL 
 * @post Output==ERROR
 */
void test3_set_print();

/**
 * @test Test getting ids from a set
 * @pre Pointer to an empty set
 * @post Output==NULL
 */
void test1_set_get_id_at();

/**
 * @test Test getting ids from a set
 * @pre pointer to set = NULL 
 * @post Output==NULL
 */
void test2_set_get_id_at();

/**
 * @test Test getting ids from a set
 * @pre Pointer to a set with ids
 * @post Output!=NULL
 */
void test3_set_get_id_at();

/**
 * @test Test getting number of ids from a set
 * @pre Pointer to a set with ids
 * @post Output==number of ids
 */
void test1_set_get_n_ids();

/**
 * @test Test getting number of ids from a set
 * @pre pointer to set = NULL 
 * @post Output==-1
 */
void test2_set_get_n_ids();

/**
 * @test Test getting a list of ids
 * @pre pointer to set = NULL 
 * @post Output==-1
 */
void test1_set_get_list_ids();

/**
 * @test Test getting a list of ids
 * @pre pointer to set = NULL 
 * @post Output==-1
 */
void test2_set_get_list_ids();

/**
 * @test Test getting a list of ids
 * @pre pointer to set = NULL 
 * @post Output==-1
 */
void test3_set_get_list_ids();

/**
 * @test Test finding an ID in a set
 * @pre pointer to set = NULL 
 * @post Output==-1
 */
void test1_set_find();

/**
 * @test Test finding an ID in a set
 * @pre pointer to set = NULL 
 * @post Output==-1
 */
void test2_set_find();

/**
 * @test Test finding an ID in a set
 * @pre pointer to set = NULL 
 * @post Output==-1
 */
void test3_set_find();
#endif