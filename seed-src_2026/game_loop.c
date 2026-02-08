/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG && Jian Feng Yin Chen
 * @version 0
 * @date 02-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"

/**
 * @brief Initializes the game and the graphic engine.
 * @author Jian Feng Yin Chen
 * 
 * It creates the game from the data file and creates the graphic engine.
 * @param game Pointer to the game structure to be initialized.
 * @param gengine Address of the pointer to the graphic engine to be created.
 * @param file_name Name of the data file with the game description.
 * @return 0 if everything goes well, 1 if there is any error.
 */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

/**
 * @brief Cleans up resources used by the game loop.
 * @author Jian Feng Yin Chen
 * 
 * It destroys the game structure and the graphic engine.
 * @param game Game structure to be destroyed (passed by value).
 * @param gengine Pointer to the graphic engine to be destroyed.
 */
void game_loop_cleanup(Game game, Graphic_engine *gengine);

/**
 * @brief Runs the game loop.
 * @author Jian Feng Yin Chen
 *
 * The game loop: paints the game, reads a command fron the user, updates the game to that command.
 * Until the user enters EXIT or the game finishes.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments. argv[1] must be the data file.
 * @return 0 if the program ends normally, 1 if there was any initialization error.
 */
int main(int argc, char *argv[]) {
  Game game;
  Graphic_engine *gengine;
  int result;
  Command *last_cmd;

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  result = game_loop_init(&game, &gengine, argv[1]);

  if (result == 1) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  } else if (result == 2){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    return 1;
  }

  last_cmd = game_get_last_command(&game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(&game) == FALSE)) {
    graphic_engine_paint_game(gengine, &game);
    command_get_user_input(last_cmd);
    game_actions_update(&game, last_cmd);
  }

  game_loop_cleanup(game, gengine);

  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name) {
  if (game_reader_create_from_file(game, file_name) == ERROR) {
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    game_destroy(game);
    return 1;
  }

  return 0;
}

void game_loop_cleanup(Game game, Graphic_engine *gengine) {
  game_destroy(&game);
  graphic_engine_destroy(gengine);
}
