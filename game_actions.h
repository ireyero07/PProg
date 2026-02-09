/**
 * @brief It defines the game update interface
 *
 * @file game.h
 * @author Profesores PPROG && Jian Feng Yin Chen
 * @version 0
 * @date 02-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "player.h"
#include "object.h"
#include "types.h"
/**
 * @brief Updates the game state according to the last user command.
 * @author Jian Feng Yin Chen
 * 
 * It stores the las command in the game structure, ontains its code and calls the corresponding action function.
 * @param game Pointer to the game to be updated.
 * @param cmd Pointer to the command that has been entered by the user.
 * @return OK if everything goes well, if not ERROR.
 */
Status game_actions_update(Game *game, Command *cmd);

#endif