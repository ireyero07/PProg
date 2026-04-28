/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG && Ivan
 * @version 0
 * @date 10-02-2026
 * @copyright GNU Public License
 */

/** Modelo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ~ +------------------+---------------------+----------+ ~
 * ~ |   Mini Map       | Dining Room         | Floor: 2 | ~
 * ~ +------------------+---------------------+----------+ ~
 * ~ |  [ ]--[ ]--[ ]   |  ./T\.              |    UP    | ~
 * ~ |   |    |    |    |    *                |    ^     | ~
 * ~ |  [ ]--[X]--[ ]   |!   Y   !            |          | ~
 * ~ |   |    |    |    |!_=====_!            |    V     | ~
 * ~ |  [ ]--[ ]--[ ]   |!!_!!!_!!            |  DOWN    | ~
 * ~ +------------------+---------------------+----------+ ~
 * ~                                                       ~
 * ~                          /\                           ~
 * ~        +-------------------------------------+        ~
 * ~        | CHR CHR CHR CHR CHR CHR CHR CHR CHR |        ~
 * ~        |                                     |        ~
 * ~        |                PLY                  |        ~
 * ~        |                                     |        ~
 * ~       <| CHR CHR CHR CHR CHR CHR CHR CHR CHE |>       ~ 
 * ~        | CHR CHR CHR CHR CHR CHR CHR CHR CHE |        ~
 * ~        |                                     |        ~
 * ~        | OBJ                                 |        ~
 * ~        | OBJ                                 |        ~
 * ~        +-------------------------------------+        ~
 * ~                          \/                           ~
 * ~                                                       ~
 * ~-------------------------------------------------------~
 * ~  CHAT/INSPECT/COSA QUE HA PASADO                      ~
 * ~                                                       ~
 * ~       Ha muerto pepito                                ~
 * ~                                                       ~
 * ~                                                       ~
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */


#include "graphic_engine.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "space.h"
#include "set.h"
#include "types.h"
#include "player.h"
#include "inventory.h"

#define WIDTH_MAP 57  /*!< Width of the map area in characters */
#define WIDTH_DES 59  /*!< Width of the description area in characters */
#define WIDTH_BAN 12  /*!< Width of the banner area in characters */
#define HEIGHT_MAP 30 /*!< Height of the map area in lines */
#define HEIGHT_BAN 1  /*!< Height of the banner area in lines */
#define HEIGHT_HLP 2  /*!< Height of the help area in lines */
#define HEIGHT_FDB 3  /*!< Height of the feedback area in lines */

/** @brief Graphic engine structure containing all screen areas */
struct _Graphic_engine {
  Area *map;      /*!< Map display area */
  Area *descript; /*!< Description display area */
  Area *banner;   /*!< Banner display area */
  Area *help;     /*!< Help text display area */
  Area *feedback; /*!< Feedback/command result display area */
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

void get_space_symbol(char *dest, Space *space, int is_player) {
  if (!space || space_get_discovered(space) == FALSE) {
    strcpy(dest, "   ");
  } else if (is_player) {
    strcpy(dest, "[X]");
  } else {
    strcpy(dest, "[ ]");
  }
}

void get_vertical_arrow(char *dest, Game *game, Id from, Id to, Direction dir) {
  if (to != NO_ID) {
    if (game_connection_is_open(game, from, dir) == TRUE) {
      strcpy(dest, "|");
    } else {
      strcpy(dest, "x");
    }
  } else {
    strcpy(dest, " ");
  }
}

void get_horizontal_arrow(char *dest, Game *game, Id from, Id to, Direction dir) {
  if (to != NO_ID) {
    if (game_connection_is_open(game, from, dir) == TRUE) {
      strcpy(dest, "--");
    } else {
      strcpy(dest, "xx");
    }
  } else {
    strcpy(dest, "  ");
  }
}

void get_up_arrow(char *dest, Game *game, Id from, Id to) {
  if (to != NO_ID) {
    if (game_connection_is_open(game, from, UP) == TRUE) {
      strcpy(dest, "^");
    } else {
      strcpy(dest, "x");
    }
  } else {
    strcpy(dest, " ");
  }
}

void get_down_arrow(char *dest, Game *game, Id from, Id to) {
  if (to != NO_ID) {
    if (game_connection_is_open(game, from, DOWN) == TRUE) {
      strcpy(dest, "v");
    } else {
      strcpy(dest, "x");
    }
  } else {
    strcpy(dest, " ");
  }
}

void graphic_engine_info_row(Graphic_engine *ge, Game *game, Id id_act, Id id_north, Id id_south, Id id_west, Id id_east, Id id_up, Id id_down) {
  Space *space_act = NULL, *space_north = NULL, *space_south = NULL, *space_west = NULL, *space_east = NULL;
  char gdesc[GDESC_LINES][GDESC_LENGTH + 1];
  char str[255];
  char act_symbol[4], north_symbol[4], south_symbol[4], west_symbol[4], east_symbol[4];
  char north_arrow[2], south_arrow[2], west_arrow[3], east_arrow[3], up_arrow[2], down_arrow[2];
  int i;

  space_act = game_get_space(game, id_act);
  space_north = game_get_space(game, id_north);
  space_south = game_get_space(game, id_south);
  space_west = game_get_space(game, id_west);
  space_east = game_get_space(game, id_east);

  if (!space_act) return;

  for(i = 0; i< GDESC_LINES; i++){
    strncpy(gdesc[i],space_get_gdesc(space_act,i), GDESC_LENGTH);
    gdesc[i][GDESC_LENGTH] = '\0';
  }

  get_space_symbol(act_symbol,   space_act,   1);
  get_space_symbol(north_symbol, space_north, 0);
  get_space_symbol(south_symbol, space_south, 0);
  get_space_symbol(west_symbol,  space_west,  0);
  get_space_symbol(east_symbol,  space_east,  0);

  get_vertical_arrow(north_arrow, game, id_act, id_north, N);
  get_vertical_arrow(south_arrow, game, id_act, id_south, S);

  get_horizontal_arrow(west_arrow, game, id_act, id_west, W);
  get_horizontal_arrow(east_arrow, game, id_act, id_east, E);

  get_up_arrow(up_arrow, game, id_act, id_up);
  get_down_arrow(down_arrow, game, id_act, id_down);

  sprintf(str, "+------------------+---------------------+----------+");
  screen_area_puts(ge->map, str);
  sprintf(str, "|   Mini Map       | %-20s| Floor:%3d|", space_get_name(space_act), (int)(id_act / 100));
  screen_area_puts(ge->map, str);
  sprintf(str, "+------------------+---------------------+----------+");
  screen_area_puts(ge->map, str);
  sprintf(str, "|       %s        | %-20s|    UP    |", north_symbol, gdesc[0]);
  screen_area_puts(ge->map, str);
  sprintf(str, "|        %s         | %-20s|    %s     |", north_arrow, gdesc[1], up_arrow);
  screen_area_puts(ge->map, str);
  sprintf(str, "|  %s%s%s%s%s  | %-20s|           |", west_symbol, west_arrow, act_symbol, east_arrow, east_symbol, gdesc[2]);
  screen_area_puts(ge->map, str);
  sprintf(str, "|        %s         | %-20s|    %s     |", south_arrow, gdesc[3], down_arrow);
  screen_area_puts(ge->map, str);
  sprintf(str, "|       %s        | %-20s|  DOWN    |", south_symbol, gdesc[4]);
  screen_area_puts(ge->map, str);
  sprintf(str, "+------------------+---------------------+----------+");
  screen_area_puts(ge->map, str);
}


/**
 * @brief Prints the west, current and east spaces side by side in the map area
 * @param ge Pointer to the graphic engine
 * @param game Pointer to the game
 * @param id_act Id of the current (actual) space
 */
void graphic_engine_print_actual_space(Graphic_engine *ge, Game *game, Id id_act) {
  int i, j, n_followers, n_chars, n_objs;
  Space *space_act = NULL;;
  Id ids[3], obj_id = NO_ID, *objects = NULL, player_id = NO_ID, id_west = NO_ID, id_east = NO_ID;
  Character *chrs = NULL, *followers[MAX_CHARACTERS];
  char chr_line1[WORD_SIZE], chr_line2[WORD_SIZE], obj_line1[WORD_SIZE], obj_line2[WORD_SIZE], ply[MAX_CHR_GDESC + 1], str[255], line[64];
  Object *obj = NULL;
  Player *player = NULL;
  long n_objects;
  char left_conn, right_conn;

  if(!ge || !game || id_act == NO_ID) return;

  space_act = game_get_space(game, id_act);
  if(!space_act) return;

  player = game_get_player(game);
  player_id = player_get_id(player);
  id_west   = game_get_connection(game, id_act, W);
  id_east   = game_get_connection(game, id_act, E);

  /* Obteniendo el player gdesc */
  strncpy(ply, player_get_gdesc(player), MAX_CHR_GDESC);
  ply[MAX_CHR_GDESC] = '\0';

  /* Obteniendo followers*/
  n_followers = game_count_followers(game, player_id);
  if (n_followers > 6) {
    n_followers = 6;
  }
  for (i = 0; i < n_followers; i++) {
    followers[i] = game_get_nth_follower(game, player_id, i);
  }
    
  /* Obteniendo personajes en el espacio*/
  chr_line1[0] = '\0';
  chr_line2[0] = '\0';
  n_chars = 0;
  for (i = 0; i < game_get_n_characters(game); i++) {
    chrs = game_get_character_by_position(game, i);
    if (chrs == NULL) continue;
    if (character_get_location(chrs) != id_act) continue;
    if (character_get_health(chrs) <= 0) continue;
    n_chars++;
    if (n_chars <= 4) {
      if (strlen(chr_line1) > 0) {
        strcat(chr_line1, " ");
      }
      strncat(chr_line1, character_get_gdesc(chrs), MAX_CHR_GDESC);
    } else if (n_chars <= 7) {
      if (strlen(chr_line2) > 0) {
        strcat(chr_line2, " ");
      }
      strncat(chr_line2, character_get_gdesc(chrs), MAX_CHR_GDESC);
    }
  }

  /* Obteniendo objetos en el espacio*/
  obj_line1[0] = '\0';
  obj_line2[0] = '\0';
  objects = space_get_objects_ids(space_act);
  n_objects = space_get_number_objects(space_act);
  n_objs = 0;
  for (i = 0, j = 0; i < n_objects; i++) {
    while ((obj_id = objects[j]) == NO_ID) {
      j++;
    }
    obj = game_get_object(game, obj_id);
    j++;
    if (obj == NULL) continue;
    n_objs++;
    if (n_objs <= 3) {
      if (strlen(obj_line1) > 0) {
        strcat(obj_line1, ", ");
      }
      if (n_objects > 3) {
        strncat(obj_line1, object_get_name(obj), 2);
      } else {
        strcat(obj_line1, object_get_name(obj));
      }
    } else {
      if (strlen(obj_line2) > 0) {
        strcat(obj_line2, ", ");
      }
      if (n_objects > 3) {
        strncat(obj_line2, object_get_name(obj), 2);
      } else {
        strcat(obj_line2, object_get_name(obj));
      }
    }
  }

  /* miramos si hay conexiones abiertas a izquierda y derecha */
  if (id_west == NO_ID) {
    left_conn = ' ';
  } else if (game_connection_is_open(game, id_act, W)) {
    left_conn = '<';
  } else {
    left_conn = 'X';
  }

  if (id_east == NO_ID) {
    right_conn = ' ';
  } else if (game_connection_is_open(game, id_act, E)) {
    right_conn = '>';
  } else {
    right_conn = 'X';
  }
  space_set_discovered(game_get_space(game,id_act),TRUE);
  /* Ahora pintamos fila por fila combinando las 3 habitaciones horizontalmente */
  for (i = 0; i < GDESC_LINES + 4; i++) { 
    str[0] = '\0';
    
    if(i == 0 || i == 10) sprintf(line, " +-------------------------------------+ ");
    else if(i == 1){
      if(n_followers == 0) sprintf(line, "        |                                     |        ");
      else if(n_followers == 1) sprintf(line, "        | %-3.3s                                 |        ", character_get_gdesc(followers[0]));
      else if(n_followers == 2) sprintf(line, "        | %-3.3s %-3.3s                             |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]));
      else if(n_followers == 3) sprintf(line, "        | %-3.3s %-3.3s %-3.3s                         |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]), character_get_gdesc(followers[2]));
      else if(n_followers == 4) sprintf(line, "        | %-3.3s %-3.3s %-3.3s %-3.3s                     |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]), character_get_gdesc(followers[2]), character_get_gdesc(followers[3]));
      else if(n_followers == 5) sprintf(line, "        | %-3.3s %-3.3s %-3.3s %-3.3s %-3.3s                 |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]), character_get_gdesc(followers[2]), character_get_gdesc(followers[3]), character_get_gdesc(followers[4]));
      else sprintf(line, "        | %-3.3s %-3.3s %-3.3s %-3.3s %-3.3s %-3.3s             |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]), character_get_gdesc(followers[2]), character_get_gdesc(followers[3]), character_get_gdesc(followers[4]), character_get_gdesc(followers[5]));
    } 
    else if(i == 2) sprintf(line, "        |                                     |        ");
    else if(i == 3) sprintf(line, "        |              [%-3.3s]                 |        ", ply);
    else if(i == 4) sprintf(line, "        |                                     |        ");
      
    else if(i == 5){
      if (left_conn == ' ' && right_conn == ' ') {
        sprintf(line, "        | %-37s|        ", chr_line1);
      } else if (left_conn != ' ' && right_conn == ' ') {
        sprintf(line, "       %c| %-37s|        ", left_conn, chr_line1);
      } else if (left_conn == ' ' && right_conn != ' ') {
        sprintf(line, "        | %-37s|%c       ", chr_line1, right_conn);
      } else {
        sprintf(line, "       %c| %-37s|%c       ", left_conn, chr_line1, right_conn);
      }
      
    } else if(i == 6){
      sprintf(line, "        | %-37s|        ", chr_line2);
    } else if(i == 7){
      sprintf(line, "        |                                     |        ");
    } else if (i == 8) {
      if (strlen(obj_line1) == 0) {
        sprintf(line, "        |                                     |        ");
      } else {
        sprintf(line, "        | %-37s|        ", obj_line1);
      }
    } else if (i == 9) {
      if (strlen(obj_line2) == 0) {
        sprintf(line, "        |                                     |        ");
      } else {
        sprintf(line, "        | %-37s|        ", obj_line2);
      }
    }


    strcat(str, line);
    screen_area_puts(ge->map, str);
  }
}
  
/**
 * @brief Prints the narrator map area
 * @param ge Pointer to the graphic engine
 * @param game Pointer to the game
 */
void graphic_engine_print_narrator(Graphic_engine *ge, Game *game){
  char str[255];
  CommandCode last_cmd;
  char *chat = NULL, *desc = NULL;
  Character *ch = NULL;
  Id chr_id = NO_ID;

  if(!ge || !game) return;

  last_cmd = command_get_code(game_get_last_command(game));
  chat = game_get_last_chat(game);
  desc = game_get_last_obj_desc(game);

  screen_area_puts(ge->map, "-------------------------------------------------------");

  screen_area_puts(ge->map, " ");

  if (last_cmd == CHAT) {
    if (chat != NULL && strlen(chat) > 0) {
      chr_id = game_get_character_id_by_name(game, command_get_arg(game_get_last_command(game)));
      ch = game_get_character_by_id(game, chr_id);
      sprintf(str, " %s said: %s", character_get_name(ch), chat);
      screen_area_puts(ge->descript, str);
    } else {
      screen_area_puts(ge->map, "       No hay nadie con quien hablar");
    }

  } else if (last_cmd == INSPECT) {
    if (desc != NULL && strlen(desc) > 0 && game_get_last_action(game) == OK) {
      sprintf(str, " The description of %s is: %s", command_get_arg(game_get_last_command(game)), desc);
      screen_area_puts(ge->descript, str);
    } else {
      screen_area_puts(ge->map, "       No puedes inspeccionar eso");
    }

  } else if (last_cmd == ATTACK) {
    if (game_get_last_action(game) == OK) {
      screen_area_puts(ge->map, "       Has atacado al enemigo");
    } else {
      screen_area_puts(ge->map, "       No hay enemigos aqui");
    }

  } else if (last_cmd == TAKE) {
    if (game_get_last_action(game) == OK) {
      screen_area_puts(ge->map, "       Has cogido el objeto");
    } else {
      screen_area_puts(ge->map, "       No puedes coger ese objeto");
    }

  } else if (last_cmd == DROP) {
    if (game_get_last_action(game) == OK) {
      screen_area_puts(ge->map, "       Has soltado el objeto");
    } else {
      screen_area_puts(ge->map, "       No puedes soltar ese objeto");
    }

  } else if (last_cmd == USE) {
    if (game_get_last_action(game) == OK) {
      screen_area_puts(ge->map, "       Has usado el objeto");
    } else {
      screen_area_puts(ge->map, "       No puedes usar ese objeto");
    }

  } else if (last_cmd == OPEN) {
    if (game_get_last_action(game) == OK) {
      screen_area_puts(ge->map, "       Has abierto el enlace");
    } else {
      screen_area_puts(ge->map, "       No puedes abrir eso");
    }

  } else if (last_cmd == RECRUIT) {
    if (game_get_last_action(game) == OK) {
      screen_area_puts(ge->map, "       El personaje ahora te sigue");
    } else {
      screen_area_puts(ge->map, "       No puedes reclutar a ese personaje");
    }

  } else if (last_cmd == ABANDON) {
    if (game_get_last_action(game) == OK) {
      screen_area_puts(ge->map, "       El personaje ya no te sigue");
    } else {
      screen_area_puts(ge->map, "       Ese personaje no te estaba siguiendo");
    }

  } else if (last_cmd == MOVE) {
    if (game_get_last_action(game) == ERROR) {
      screen_area_puts(ge->map, "       No puedes moverte en esa direccion");
    } else {
      screen_area_puts(ge->map, " ");
    }

  } else {
    screen_area_puts(ge->map, " ");
  }

  screen_area_puts(ge->map, " ");
  screen_area_puts(ge->map, " ");
}




void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Player *player = NULL;
  Status result;
  const char *result_str;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  Id *objs = NULL, obj_loc = NO_ID;
  Object *obj = NULL;
  long n_objs = 0;
  Space *obj_space = NULL;
  Space *ch_space = NULL;
  Character *ch = NULL;
  Id id_act = NO_ID, id_north = NO_ID, id_south = NO_ID, id_west = NO_ID, id_east = NO_ID, id_up = NO_ID, id_down = NO_ID;

  
  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {

    id_north = game_get_connection(game, id_act, N);
    id_south = game_get_connection(game, id_act, S);
    id_west  = game_get_connection(game, id_act, W);
    id_east  = game_get_connection(game, id_act, E);
    id_up   = game_get_connection(game, id_act, UP);
    id_down = game_get_connection(game, id_act, DOWN);

    /*-------------------------------------------------------*/
    /*                    INFO ROW                           */
    /*-------------------------------------------------------*/
    graphic_engine_info_row(ge, game, id_act ,id_north, id_south, id_west, id_east, id_up, id_down);

    /*-------------------------------------------------------*/
    /*                    ACTUAL SPACES                      */
    /*-------------------------------------------------------*/
    if (id_north != NO_ID) {
      if(game_connection_is_open(game,id_act,N)) sprintf(str, "                          /\\      ");
      else sprintf(str, "                          ><");
      screen_area_puts(ge->map, str);
    }

    graphic_engine_print_actual_space(ge, game, id_act);

    if (id_south != NO_ID) {
      if(game_connection_is_open(game,id_act,S)) sprintf(str, "                          \\/      ");
      else sprintf(str, "                          ><");
      screen_area_puts(ge->map, str);
    }

    /*-------------------------------------------------------*/
    /*                     NARRATOR                          */
    /*-------------------------------------------------------*/
    graphic_engine_print_narrator(ge, game);

  }


  /* Paint in the description area */
  screen_area_clear(ge->descript);

  /* ---------- OBJECTS ---------- */
  screen_area_puts(ge->descript, "Objects:");

  for (i = 0; i<game_get_n_objects(game); i++) {
    obj = game_get_object_by_position(game, i);
    if (!obj) continue;
    obj_loc = game_get_object_location(game,object_get_id(obj));
    obj_space = game_get_space(game, obj_loc);
    if(obj_space && space_get_discovered(obj_space) == TRUE){
      sprintf(str, " %s (loc:%ld)", object_get_name(obj), obj_loc);
      screen_area_puts(ge->descript, str);
    }
  }

  /* ---------- CHARACTERS ---------- */
  screen_area_puts(ge->descript, "Characters:");

  for (i = 0; i<game_get_n_characters(game); i++) {
    ch = game_get_character_by_position(game, i);

    if(!ch) continue;
    ch_space = game_get_space(game, character_get_location(ch));
    if (ch_space && space_get_discovered(ch_space) == TRUE){
      if(character_get_health(ch) <=0 ){
        screen_area_puts(ge->descript, " ");
      } else {
        sprintf(str, " %s (loc: %ld, hp:%d)", character_get_gdesc(ch),character_get_location(ch), character_get_health(ch));
        screen_area_puts(ge->descript, str);
      }
    }
  }

  /* ---------- PLAYER ---------- */
  screen_area_puts(ge->descript, "Player:");
  player = game_get_player(game);

  if (player) {
    sprintf(str, "  (loc: %ld, hp:%d)", player_get_location(player), player_get_health(player));
    screen_area_puts(ge->descript, str);

    if (player_get_backpack(player) != NULL) {
      objs = player_get_objects(player);
      n_objs = inventory_get_number_objects(player_get_backpack(player));
      if(n_objs == 0){
        screen_area_puts(ge->descript, "Player has no objects");
      } else {
        if(n_objs >= inventory_get_max_objs(player_get_backpack(player))){
          sprintf(str, "Player's inventory: (FULL)");
          screen_area_puts(ge->descript, str);
        } else {
          sprintf(str, "Player's inventory:");
          screen_area_puts(ge->descript, str);
        }
        for(i=0; i < n_objs;i++){
          sprintf(str, " %s", object_get_name(game_get_object(game,objs[i])));
          screen_area_puts(ge->descript, str);
        }
      }
    }
  }

  /* Paint in the banner area */
  sprintf(str, " Player %d/%d ",game_get_turn(game)+1, game_get_n_players(game));
  screen_area_puts(ge->banner, str);

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " move or m (n,s,e,w,u,d), take or t, drop or d, attack or a <chr>, chat or c, inspect or i, exit or e, recruit <chr>, abandon <chr>, use <obj> [ over <chr> ], open <lnk> with <obj>");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  result = game_get_last_action(game);

  if (result == OK)
    result_str = "OK";
  else
    result_str = "ERROR";
  if (last_cmd !=NO_CMD){
    sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], result_str);
    screen_area_puts(ge->feedback,str);
  }

  /* Dump to the terminal */
  screen_paint(game_get_turn(game));
  
  if (game_is_any_player_death(game)) {
    fprintf(stdout, "Game Over (╥﹏╥)\n");
    game_set_finished(game, TRUE);
  }
  else{
    fprintf(stdout, "prompt:> ");
  }
}