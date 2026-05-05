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
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "command.h"
#include "game.h"
#include "game_reader.h"
#include "game_actions.h"
#include "graphic_engine.h"
#include "game_rules.h"

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
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 * @brief Cleans up resources used by the game loop.
 * @author Jian Feng Yin Chen
 *
 * It destroys the game structure and the graphic engine.
 * @param game Game structure to be destroyed (passed by value).
 * @param gengine Pointer to the graphic engine to be destroyed.
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

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
int main(int argc, char *argv[])
{
  Game *game = NULL;
  Graphic_engine *gengine = NULL;
  int result = 0;
  Command *last_cmd = NULL;
  FILE *log_file = NULL;
  int log_active = 0, deterministic = 0;

  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  if (argc >= 4 && strcmp(argv[2], "-l") == 0)
  {
    log_file = fopen(argv[3], "w");
    if (!log_file)
    {
      fprintf(stderr, "Error opening log file.\n");
      return 1;
    }
    log_active = 1;
  }

  if (argc >= 5 && strcmp(argv[3], "-l") == 0 && strcmp(argv[2], "-d") == 0)
  {
    deterministic = 1;
    log_file = fopen(argv[4], "w");
    if (!log_file)
    {
      fprintf(stderr, "Error opening log file.\n");
      return 1;
    }
    log_active = 1;
  }

  if (argc >= 3 && strcmp(argv[2], "-d") == 0)
  {
    deterministic = 1;
  }

  result = game_loop_init(&game, &gengine, argv[1]);

  if (result == 1)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }
  else if (result == 2)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    return 1;
  }

  if (deterministic)
  {
    game_set_deterministic(game, deterministic);
  }
  else
  {
    srand(time(NULL));
  }

  last_cmd = command_create();
  if (!last_cmd)
  {
    return 1;
  }

  while ((game_get_finished(game) == FALSE) && (game_is_any_player_death(game) == FALSE))
  {

    graphic_engine_paint_game(gengine, game);

    if ((game_get_finished(game) == TRUE) || (game_is_any_player_death(game) == TRUE))
    {
      break;
    }

    command_get_user_input(last_cmd);

    if (command_get_code(last_cmd) == EXIT)
    {
      if (log_active)
      {
        fclose(log_file);
      }
      command_destroy(last_cmd);
      game_loop_cleanup(game, gengine);
      return 0;
    }

    game_actions_update(game, last_cmd);

    if (log_active)
    {
      char line[128];

      if (command_get_arg(last_cmd)[0] != '\0')
      {
        sprintf(line, "%s %s", command_get_name(last_cmd), command_get_arg(last_cmd));
      }
      else
      {
        sprintf(line, "%s", command_get_name(last_cmd));
      }

      fprintf(log_file, "%s: %s (Player %d)\n", line, (game_get_last_action(game) == OK) ? "OK" : "ERROR", game_get_turn(game) + 1);
    }

    if (game_get_deterministic(game) == FALSE)
    {
      game_rules_run_rules(game);
    }

    graphic_engine_paint_game(gengine, game);

    if (game_get_n_players(game) > 1)
    {
      sleep(2);
    }

    if (game_is_any_player_death(game) == FALSE && game_get_finished(game) == FALSE)
    {
      game_next_turn(game);
    }
  }

  graphic_engine_paint_game(gengine, game);

  if (log_active)
  {
    fclose(log_file);
  }

  command_destroy(last_cmd);
  game_loop_cleanup(game, gengine);

  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name)
{
  if (game_reader_create_from_file(game, file_name) == ERROR)
  {
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    game_destroy(*game);
    return 2;
  }

  return 0;
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
