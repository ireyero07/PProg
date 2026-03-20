/**
 * @brief It declares the tests for the player module
 *
 * @file player_test.h
 * @author Jian Feng Yin Chen
 * @version 0.0
 * @date 17-03-2026
 * @copyright GNU Public License
 */
 
#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H
 
/**
 * @test Test player creation
 * @pre Valid player ID and max_objs = 5
 * @post Non NULL pointer to player
 */
void test1_player_create();
 
/**
 * @test Test player creation
 * @pre NO_ID as player ID
 * @post Returns NULL
 */
void test2_player_create();
 
/**
 * @test Test player_get_id
 * @pre Valid player with id = 5
 * @post Returns 5
 */
void test1_player_get_id();
 
/**
 * @test Test player_get_id
 * @pre NULL player pointer
 * @post Returns NO_ID
 */
void test2_player_get_id();
 
/**
 * @test Test player_set_name
 * @pre Valid player and valid name string
 * @post Output==OK
 */
void test1_player_set_name();
 
/**
 * @test Test player_set_name
 * @pre NULL player pointer
 * @post Output==ERROR
 */
void test2_player_set_name();
 
/**
 * @test Test player_set_name with NULL name
 * @pre Valid player, NULL name string
 * @post Output==ERROR
 */
void test3_player_set_name();
 
/**
 * @test Test player_get_name
 * @pre Player with name set to "knight"
 * @post Returns correct name string
 */
void test1_player_get_name();
 
/**
 * @test Test player_get_name
 * @pre NULL player pointer
 * @post Returns NULL
 */
void test2_player_get_name();
 
/**
 * @test Test player_set_location
 * @pre Valid player and valid location Id
 * @post Output==OK
 */
void test1_player_set_location();
 
/**
 * @test Test player_set_location
 * @pre NULL player pointer
 * @post Output==ERROR
 */
void test2_player_set_location();
 
/**
 * @test Test player_get_location
 * @pre Player with location set to 10
 * @post Returns 10
 */
void test1_player_get_location();
 
/**
 * @test Test player_get_location
 * @pre NULL player pointer
 * @post Returns NO_ID
 */
void test2_player_get_location();
 
/**
 * @test Test player_add_object
 * @pre Valid player and valid object Id
 * @post Output==OK
 */
void test1_player_add_object();
 
/**
 * @test Test player_add_object
 * @pre NULL player pointer
 * @post Output==ERROR
 */
void test2_player_add_object();
 
/**
 * @test Test player_add_object when backpack is full
 * @pre Player with max_objs = 1, already carrying one object
 * @post Output==ERROR
 */
void test3_player_add_object();
 
/**
 * @test Test player_del_object
 * @pre Valid player carrying object
 * @post Output==OK
 */
void test1_player_del_object();
 
/**
 * @test Test player_del_object
 * @pre NULL player pointer
 * @post Output==ERROR
 */
void test2_player_del_object();
 
/**
 * @test Test player_del_object with non-existing object
 * @pre Valid player not carrying the object
 * @post Output==ERROR
 */
void test3_player_del_object();
 
/**
 * @test Test player_has_object
 * @pre Player carrying object with Id = 10
 * @post Returns TRUE
 */
void test1_player_has_object();
 
/**
 * @test Test player_has_object
 * @pre Player not carrying any object
 * @post Returns FALSE
 */
void test2_player_has_object();
 
/**
 * @test Test player_has_object with NULL player
 * @pre NULL player pointer
 * @post Returns FALSE
 */
void test3_player_has_object();
 
/**
 * @test Test player_get_objects
 * @pre Valid player
 * @post Non NULL pointer to Id array
 */
void test1_player_get_objects();
 
/**
 * @test Test player_get_objects
 * @pre NULL player pointer
 * @post Returns NULL
 */
void test2_player_get_objects();
 
/**
 * @test Test player_get_backpack
 * @pre Valid player
 * @post Non NULL pointer to Inventory
 */
void test1_player_get_backpack();
 
/**
 * @test Test player_get_backpack
 * @pre NULL player pointer
 * @post Returns NULL
 */
void test2_player_get_backpack();
 
/**
 * @test Test player_get_health
 * @pre Valid player with default health
 * @post Returns 5
 */
void test1_player_get_health();
 
/**
 * @test Test player_get_health
 * @pre NULL player pointer
 * @post Returns 0
 */
void test2_player_get_health();
 
/**
 * @test Test player_set_health
 * @pre Valid player and health = 10
 * @post Output==OK
 */
void test1_player_set_health();
 
/**
 * @test Test player_set_health
 * @pre NULL player pointer
 * @post Output==ERROR
 */
void test2_player_set_health();
 
/**
 * @test Test player_get_gdesc
 * @pre Player with gdesc set to "^C>"
 * @post Returns correct gdesc string
 */
void test1_player_get_gdesc();
 
/**
 * @test Test player_get_gdesc
 * @pre NULL player pointer
 * @post Returns NULL
 */
void test2_player_get_gdesc();
 
/**
 * @test Test player_set_gdesc
 * @pre Valid player and valid gdesc string
 * @post Output==OK
 */
void test1_player_set_gdesc();
 
/**
 * @test Test player_set_gdesc
 * @pre NULL player pointer
 * @post Output==ERROR
 */
void test2_player_set_gdesc();
 
#endif