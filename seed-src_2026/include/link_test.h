/**
 * @brief It declares the tests for the link module
 *
 * @file link_test.h
 * @author Gonzalez Hijano Ivan
 * @version 0.0
 * @date 02-04-2026
 * @copyright GNU Public License
 */
 

#ifndef LINK_TEST_H
#define LINK_TEST_H
 
/**
 * @test Test inventory creation
 * @pre Max objects = 5
 * @post Non NULL pointer to inventory
 */
void test1_inventory_create();
 
/**
 * @test Test inventory creation
 * @pre Max objects = 3
 * @post inventory_get_max_objs == 3
 */
void test2_inventory_create();
 
/**
 * @test Test inventory_get_max_objs
 * @pre Valid inventory with max_objs = 7
 * @post Returns 7
 */
void test1_inventory_get_max_objs();
 
/**
 * @test Test inventory_get_max_objs
 * @pre NULL inventory pointer
 * @post Returns -1
 */
void test2_inventory_get_max_objs();
 
/**
 * @test Test inventory_set_max_objs
 * @pre Valid inventory and max_objs = 10
 * @post Output==OK
 */
void test1_inventory_set_max_objs();
 
/**
 * @test Test inventory_set_max_objs
 * @pre NULL inventory pointer
 * @post Output==ERROR
 */
void test2_inventory_set_max_objs();
 
/**
 * @test Test inventory_add_object
 * @pre Valid inventory and valid object Id
 * @post Output==OK
 */
void test1_inventory_add_object();
 
/**
 * @test Test inventory_add_object
 * @pre NULL inventory pointer
 * @post Output==ERROR
 */
void test2_inventory_add_object();
 
/**
 * @test Test inventory_add_object when full
 * @pre Valid inventory with max_objs = 1, already containing one object
 * @post Output==ERROR
 */
void test3_inventory_add_object();
 
/**
 * @test Test inventory_del_object
 * @pre Valid inventory containing object
 * @post Output==OK
 */
void test1_inventory_del_object();
 
/**
 * @test Test inventory_del_object
 * @pre NULL inventory pointer
 * @post Output==ERROR
 */
void test2_inventory_del_object();
 
/**
 * @test Test inventory_del_object with non-existing object
 * @pre Valid inventory without the object
 * @post Output==ERROR
 */
void test3_inventory_del_object();
 
/**
 * @test Test inventory_has_object
 * @pre Inventory containing object
 * @post Returns TRUE
 */
void test1_inventory_has_object();
 
/**
 * @test Test inventory_has_object
 * @pre Inventory without the object
 * @post Returns FALSE
 */
void test2_inventory_has_object();
 
/**
 * @test Test inventory_has_object with NULL inventory
 * @pre NULL inventory pointer
 * @post Returns FALSE
 */
void test3_inventory_has_object();
 
/**
 * @test Test inventory_get_objects
 * @pre Valid inventory
 * @post Non NULL pointer to Set
 */
void test1_inventory_get_objects();
 
/**
 * @test Test inventory_get_objects
 * @pre NULL inventory pointer
 * @post Returns NULL
 */
void test2_inventory_get_objects();
 
/**
 * @test Test inventory_get_number_objects
 * @pre Valid inventory with 2 objects added
 * @post Returns 2
 */
void test1_inventory_get_number_objects();
 
/**
 * @test Test inventory_get_number_objects
 * @pre NULL inventory pointer
 * @post Returns -1
 */
void test2_inventory_get_number_objects();
 
/**
 * @test Test inventory_print
 * @pre Valid inventory
 * @post Output==OK
 */
void test1_inventory_print();
 
#endif