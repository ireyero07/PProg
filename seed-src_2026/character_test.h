/** 
 * @brief It declares the tests for the character module
 * 
 * @file character_test.h
 * @author Gonzalez Hijano, Ivan
 * @version 0.0  
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef CHARACTER_TEST_H
#define CHARACTER_TEST_H

/**
 * @test Test character creation
 * @pre ID
 * @post Non NULL pointer to character
 */
void test1_character_create();

/**
 * @test Test character creation
 * @pre NO_ID
 * @post NULL pointer to character
 */
void test2_character_create();

/**
 * @test Test destroying a character
 * @pre pointer to character = NULL 
 * @post Output==ERROR
 */
void test1_character_destroy();

/**
 * @test Test destroying a character
 * @pre Pointer to character
 * @post Output == OK
 */
void test2_character_destroy();

/**
 * @test Test getting a character ID
 * @pre Pointer to character
 * @post Output == character ID
 */
void test1_character_get_id();

/**
 * @test Test getting a character ID
 * @pre pointer to character = NULL 
 * @post Output==NO_ID
 */
void test2_character_get_id();

/**
 * @test Test setting a character name
 * @pre Pointer to character and a name
 * @post Output==OK
 */
void test1_character_set_name();

/**
 * @test Test setting a character name
 * @pre Pointer to character and name = NULL
 * @post Output==ERROR
 */
void test2_character_set_name();

/**
 * @test Test getting a character name
 * @pre Pointer to character with a name
 * @post Output!=NULL
 */
void test1_character_get_name();

/**
 * @test Test getting a character name
 * @pre pointer to character = NULL 
 * @post Output==NULL
 */
void test2_character_get_name();

/**
 * @test Test setting a character description
 * @pre Pointer to character and a description bigger than MAX_DESCRIPT_SIZE
 * @post Output==ERROR
 */
void test1_character_set_description();

/**
 * @test Test setting a character description
 * @pre Pointer to character and a description
 * @post Output==OK
 */
void test2_character_set_description();

/**
 * @test Test setting a character description
 * @pre pointer to character = NULL 
 * @post Output==ERROR
 */
void test3_character_set_description();

/**
 * @test Test getting a character description
 * @pre Pointer to character with a description
 * @post Output!=NULL
 */
void test1_character_get_description();

/**
 * @test Test getting a character description
 * @pre Pointer to character with NO description
 * @post Output!=NULL
 */
void test2_character_get_description();

/**
 * @test Test setting a character health
 * @pre Pointer to character and a health
 * @post Output==OK
 */
void test1_character_set_health();

/**
 * @test Test setting a character health
 * @pre pointer to character = NULL 
 * @post Output==ERROR
 */
void test2_character_set_health();

/**
 * @test Test setting a character health
 * @pre Pointer to character and health = -3
 * @post Output==ERROR
 */
void test3_character_set_health();

/**
 * @test Test getting a character health
 * @pre Pointer to character
 * @post Output!=-1
 */
void test1_character_get_health();

/**
 * @test Test getting a character health
 * @pre pointer to character = NULL 
 * @post Output==-1
 */
void test2_character_get_health();

/**
 * @test Test setting a character message
 * @pre Pointer to character and a message
 * @post Output==OK
 */
void test1_character_set_message();

/**
 * @test Test setting a character message
 * @pre Pointer to character and message = NULL
 * @post Output==OK
 */
void test2_character_set_message();

/**
 * @test Test setting a character message
 * @pre pointer to character = NULL 
 * @post Output==OK
 */
void test3_character_set_message();

/**
 * @test Test getting a character message
 * @pre Pointer to character
 * @post Output!=NULL
 */
void test1_character_get_message();

/**
 * @test Test getting a character message
 * @pre pointer to character = NULL 
 * @post Output==NULL
 */
void test2_character_get_message();

/**
 * @test Test setting if a character is friendly
 * @pre Pointer to character and a boolean
 * @post Output==OK
 */
void test1_character_set_friendly();

/**
 * @test Test setting if a character is friendly
 * @pre pointer to character = NULL 
 * @post Output==ERROR
 */
void test2_character_set_friendly();

/**
 * @test Test getting if a character is friendly
 * @pre Pointer to character
 * @post Output!=NULL
 */
void test1_character_get_friendly();

/**
 * @test Test getting if a character is friendly
 * @pre pointer to character = NULL 
 * @post Output==NULL
 */
void test2_character_get_friendly();

/**
 * @test Test printing a character
 * @pre Pointer to character
 * @post Output==OK
 */
void test1_character_print();

/**
 * @test Test printing a character
 * @pre pointer to character = NULL 
 * @post Output==ERROR
 */
void test2_character_print();

void test1_character_get_location();
void test2_character_get_location();
void test1_character_set_location();
void test2_character_set_location();
void test3_character_set_location();

#endif