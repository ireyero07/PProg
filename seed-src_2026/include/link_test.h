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
 * @test Test link creation
 * @pre 5 as an ID
 * @post Non NULL pointer to link
 */
void test1_link_create();

/**
 * @test Test link creation
 * @pre NO_ID
 * @post NULL pointer
 */
void test2_link_create();

/**
 * @test Test link destroy
 * @pre A valid link pointer
 * @post OK
 */
void test1_link_destroy();

/**
 * @test Test link destroy
 * @pre NULL pointer
 * @post ERROR
 */
void test2_link_destroy();

/**
 * @test Test link get id
 * @pre Link created with id 5
 * @post Returns 5
 */
void test1_link_get_id();

/**
 * @test Test link get id
 * @pre NULL pointer
 * @post Returns NO_ID
 */
void test2_link_get_id();

/**
 * @test Test link set name
 * @pre Valid link and name "link"
 * @post OK
 */
void test1_link_set_name();

/**
 * @test Test link set name
 * @pre Valid link and NULL name
 * @post ERROR
 */
void test2_link_set_name();

/**
 * @test Test link set name
 * @pre NULL link pointer
 * @post ERROR
 */
void test3_link_set_name();

/**
 * @test Test link set origin
 * @pre Valid link and origin id 5
 * @post OK
 */
void test1_link_set_origin();

/**
 * @test Test link set origin
 * @pre NULL link pointer
 * @post ERROR
 */
void test2_link_set_origin();

/**
 * @test Test link set origin
 * @pre Valid link and NO_ID
 * @post ERROR
 */
void test3_link_set_origin();

/**
 * @test Test link get origin
 * @pre Valid link with origin set to 10
 * @post Returns 10
 */
void test1_link_get_origin();

/**
 * @test Test link get origin
 * @pre NULL link pointer
 * @post Returns NO_ID
 */
void test2_link_get_origin();

/**
 * @test Test link set destination
 * @pre Valid link and destination id 10
 * @post OK
 */
void test1_link_set_destination();

/**
 * @test Test link set destination
 * @pre Valid link and NO_ID
 * @post ERROR
 */
void test2_link_set_destination();

/**
 * @test Test link set destination
 * @pre NULL link pointer
 * @post ERROR
 */
void test3_link_set_destination();

/**
 * @test Test link get destination
 * @pre Valid link with destination set to 10
 * @post Returns 10
 */
void test1_link_get_destination();

/**
 * @test Test link get destination
 * @pre NULL link pointer
 * @post Returns NO_ID
 */
void test2_link_get_destination();

/**
 * @test Test link set direction
 * @pre Valid link and direction N
 * @post OK
 */
void test1_link_set_direction();

/**
 * @test Test link set direction
 * @pre NULL link pointer
 * @post ERROR
 */
void test2_link_set_direction();

/**
 * @test Test link set direction
 * @pre Valid link and invalid direction
 * @post ERROR
 */
void test3_link_set_direction();

/**
 * @test Test link get direction
 * @pre Valid link with direction N
 * @post Returns N
 */
void test1_link_get_direction();

/**
 * @test Test link get direction
 * @pre NULL link pointer
 * @post Returns NO_DIRECTION
 */
void test2_link_get_direction();

/**
 * @test Test link set open
 * @pre Valid link and TRUE
 * @post OK
 */
void test1_link_set_open();

/**
 * @test Test link set open
 * @pre NULL link pointer
 * @post ERROR
 */
void test2_link_set_open();

/**
 * @test Test link get open
 * @pre Valid link with open FALSE
 * @post Returns FALSE
 */
void test1_link_get_open();

/**
 * @test Test link get open
 * @pre NULL link pointer
 * @post Returns FALSE
 */
void test2_link_get_open();

/**
 * @test Test link get name
 * @pre Valid link with name "name"
 * @post Returns "name"
 */
void test1_link_get_name();

/**
 * @test Test link get name
 * @pre NULL link pointer
 * @post Returns NULL
 */
void test2_link_get_name();

#endif