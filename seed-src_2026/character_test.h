/** 
 * @brief It declares the tests for the character module
 * 
 * @file character_test.h
 * @author Jian Feng Yin Chen
 * @version 0.0 
 * @date 25-02-2026
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test character creation
 * @pre Valid ID
 * @post Non NULL pointer returned
 */
void test1_character_create(void);

/**
 * @test Test character creation  
 * @pre Valid ID
 * @post ID matches input
 */
void test2_character_create(void);

/**
 * @test Test character_get_id
 * @pre Valid character
 * @post Returns correct ID
 */
void test1_character_get_id(void);

/**
 * @test Test character_get_id
 * @pre NULL character
 * @post Returns NO_ID
 */
void test2_character_get_id(void);

/**
 * @test Test character_get_name
 * @pre Character with set name
 * @post Returns correct name
 */
void test1_character_get_name(void);

/**
 * @test Test character_get_name
 * @pre NULL character
 * @post Returns NULL
 */
void test2_character_get_name(void);

/**
 * @test Test character_get_gdesc
 * @pre Character with set gdesc
 * @post Returns correct gdesc
 */
void test1_character_get_gdesc(void);

/**
 * @test Test character_get_gdesc
 * @pre NULL character
 * @post Returns NULL
 */
void test2_character_get_gdesc(void);

/**
 * @test Test character_get_health
 * @pre Character with set health
 * @post Returns correct health
 */
void test1_character_get_health(void);

/**
 * @test Test character_get_health
 * @pre NULL character
 * @post Returns 0
 */
void test2_character_get_health(void);

/**
 * @test Test character_get_friendly
 * @pre Character with TRUE friendly
 * @post Returns TRUE
 */
void test1_character_get_friendly(void);

/**
 * @test Test character_get_friendly
 * @pre NULL character
 * @post Returns FALSE
 */
void test2_character_get_friendly(void);

/**
 * @test Test character_get_message
 * @pre Character with set message
 * @post Returns correct message
 */
void test1_character_get_message(void);

/**
 * @test Test character_get_message
 * @pre NULL character
 * @post Returns NULL
 */
void test2_character_get_message(void);

/**
 * @test Test character_set_name
 * @pre Valid character and name
 * @post Returns OK
 */
void test1_character_set_name(void);

/**
 * @test Test character_set_name
 * @pre NULL character
 * @post Returns ERROR
 */
void test2_character_set_name(void);

/**
 * @test Test character_set_name
 * @pre Valid character, NULL name
 * @post Returns ERROR
 */
void test3_character_set_name(void);

/**
 * @test Test character_set_gdesc
 * @pre Valid character and gdesc
 * @post Returns OK
 */
void test1_character_set_gdesc(void);

/**
 * @test Test character_set_gdesc
 * @pre NULL character
 * @post Returns ERROR
 */
void test2_character_set_gdesc(void);

/**
 * @test Test character_set_health
 * @pre Valid character and health
 * @post Returns OK
 */
void test1_character_set_health(void);

/**
 * @test Test character_set_health
 * @pre NULL character
 * @post Returns ERROR
 */
void test2_character_set_health(void);

/**
 * @test Test character_set_friendly
 * @pre Valid character and friendly
 * @post Returns OK
 */
void test1_character_set_friendly(void);

/**
 * @test Test character_set_friendly
 * @pre NULL character
 * @post Returns ERROR
 */
void test2_character_set_friendly(void);

/**
 * @test Test character_set_message
 * @pre Valid character and message
 * @post Returns OK
 */
void test1_character_set_message(void);

/**
 * @test Test character_set_message
 * @pre NULL character
 * @post Returns ERROR
 */
void test2_character_set_message(void);

#endif