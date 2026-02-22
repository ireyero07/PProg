/**
 * @brief It defines the game reader module interface
 *
 * @file game_reader.h
 * @author Ivan
 * @version 0
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "types.h"
#include "game.h"

/**
 * @brief It creates a game from a file
 * @author Ivan
 *
 * This function initializes the game and loads the spaces from a file.
 *
 * @param game a pointer to the game structure
 * @param filename the name of the file with the spaces information
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_create_from_file(Game **game, char *filename);

#endif