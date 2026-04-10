/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Jian Feng Yin Chen && Ivanes
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"
#include "libscreen.h"

typedef struct _Graphic_engine Graphic_engine; /*!< Opaque type representing the graphic engine */

/**
 * @brief Creates and initializes the graphic engine.
 * @author Jian Feng Yin Chen && Ivanes
 *
 * Allocates memory for the graphic engine and initializes all screen areas.
 * @return Pointer to the new graphic engine, or NULL if there was an error.
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief Destroys the graphic engine, freeing all allocated memory.
 * @author Jian Feng Yin Chen && Ivanes
 *
 * @param ge Pointer to the graphic engine to be destroyed.
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief Paints the current game state on screen.
 * @author Jian Feng Yin Chen && Ivanes
 *
 * Renders the map, description, banner, help and feedback areas
 * based on the current state of the game.
 * @param ge Pointer to the graphic engine.
 * @param game Pointer to the game whose state will be painted.
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
