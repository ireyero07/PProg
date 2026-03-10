/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG && Ivan
 * @version 0
 * @date 10-02-2026
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "set.h"
#include "types.h"

#define WIDTH_MAP 57
#define WIDTH_DES 59
#define WIDTH_BAN 25
#define HEIGHT_MAP 30
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3


struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID, id_left = NO_ID, id_right = NO_ID;
  Space *space_act = NULL;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_left = space_get_west(space_act);
    id_right = space_get_east(space_act);

    if (game_get_object_location(game) == id_back) 
      obj = '+';
    else
      obj = ' ';

    if (id_back != NO_ID) {
      
      sprintf(str, "  |         %2d|", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    Character *character_act = character_create;
    character_act = space_get_character(space_act);
    char chr [MAX_CHR_GDESC];
    if(game_get_character_location(game,character_get_id(character_act)) == id_act)
      *chr = character_get_gdesc(character_act);
    else
      *chr = ' ';


    Object *object_act[MAX_OBJECTS_SPACE]=NULL;
    *object_act = space_get_objects(space_act);

    char obj[MAX_OBJECTS_SPACE][WORD_SIZE +1];
    for(i = 0; i>MAX_OBJECTS_SPACE; i++){
      if (game_get_object_location(game,object_get_id(object_act[i])) == id_act)
        *obj[i] = object_get_name(object_act[i]);
      else
        *obj[i] = ' ';
    }

    char gdesc_act[GDESC_LINES][GDESC_LENGTH + 1]; 
    for(i=0; i<GDESC_LINES; i++){
      *gdesc_act[i]=space_get_gdesc(space_act,i);
    }

    if (id_act != NO_ID) {
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | ^C>  %s    %2d|", chr, (int) id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc_act[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc_act[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc_act[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc_act[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc_act[4]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s     %s      |", obj[0], obj[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
    }

    if (game_get_object_location(game) == id_next)
      obj = '+';
    else
      obj = ' ';

    if (id_next != NO_ID) {
      sprintf(str, "        v");
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |      %s    %2d|",chr,(int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
    }
  }

  /* Paint in the description area */
  Object *object_info[game_get_n_objects(game)] = NULL;
  Id id_object_info = NO_ID;
  char name_obj[WORD_SIZE + 1];
  game_get_object()
  screen_area_clear(ge->descript);
  sprintf(str, "  Objects location:");
  for(i = 0; i<game_get_n_objects(game); i++){
    id_object_info = object_get_id(object_info[i])
    if ((obj_loc = game_get_object_location(game)) != NO_ID) {
    
    sprintf(str, "  %s : %d",name_obj (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }
  }


  /* Paint in the banner area */
  screen_area_puts(ge->banner, " The haunted castle game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, left or l, right or r, take or t, drop or d, attack or a, chat or c, exit or e");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
