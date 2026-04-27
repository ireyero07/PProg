/**
 * @brief It defines the game rules interface
 *
 * @file game_rules.h
 * @author Gonzalez Hijano Ivan
 * @version 0
 * @date 22-04-2026
 * @copyright GNU Public License
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game.h"
#include "types.h"

/**
 * @brief It runs all the game rules functions
 * @author Gonzalez Hijano Ivan
 *
 *
 * @param game a pointer to the game structure
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_rules_run_rules(Game *game);

#endif