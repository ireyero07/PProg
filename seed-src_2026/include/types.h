/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000    /*!< Maximum length of a word/string in the project */
#define NO_ID -1          /*!< Represents an invalid or unassigned identifier */
#define NO_DIRECTION -1   /*!< Represents an invalid or unassigned direction */

typedef long Id; /*!< Type used for unique identifiers of game entities */

/**
 * @brief Boolean type for the project
 */
typedef enum { FALSE, TRUE } Bool;

/**
 * @brief Status type to indicate success or failure of operations
 */
typedef enum { ERROR, OK } Status;

/**
 * @brief Cardinal directions used for navigation between spaces
 */
typedef enum { N, S, E, W } Direction;

#endif
