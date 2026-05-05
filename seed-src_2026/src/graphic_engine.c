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

#define WIDTH_MAP 70  /*!< Width of the map area in characters */
#define WIDTH_DES 74  /*!< Width of the description area in characters */
#define WIDTH_BAN 12  /*!< Width of the banner area in characters */
#define HEIGHT_MAP 38 /*!< Height of the map area in lines */
#define HEIGHT_BAN 1  /*!< Height of the banner area in lines */
#define HEIGHT_HLP 3  /*!< Height of the help area in lines */
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

void graphic_engine_get_direction_name(char *dest, Direction dir) {
  if (dir == NO_DIRECTION){
    strcpy(dest, "   ");
  } else if (dir == N) {
    strcpy(dest, "North");
  } else if (dir == S) {
    strcpy(dest, "South");
  } else if (dir == E) {
    strcpy(dest, "East");
  } else if (dir == W) {
    strcpy(dest, "West");
  }
}

void graphic_engine_get_space_symbol(char *dest, Space *space, int is_player) {
  if (!space || space_get_discovered(space) == FALSE) {
    strcpy(dest, "   ");
  } else if (is_player) {
    strcpy(dest, "[X]");
  } else {
    strcpy(dest, "[ ]");
  }
}

void graphic_engine_get_vertical_arrow(char *dest, Game *game, Id from, Id to, Direction dir) {
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

void graphic_engine_get_horizontal_arrow(char *dest, Game *game, Id from, Id to, Direction dir) {
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

void graphic_engine_get_up_arrow(char *dest, Game *game, Id from, Id to) {
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

void graphic_engine_get_down_arrow(char *dest, Game *game, Id from, Id to) {
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

  graphic_engine_get_space_symbol(act_symbol,   space_act,   1);
  graphic_engine_get_space_symbol(north_symbol, space_north, 0);
  graphic_engine_get_space_symbol(south_symbol, space_south, 0);
  graphic_engine_get_space_symbol(west_symbol,  space_west,  0);
  graphic_engine_get_space_symbol(east_symbol,  space_east,  0);

  graphic_engine_get_vertical_arrow(north_arrow, game, id_act, id_north, N);
  graphic_engine_get_vertical_arrow(south_arrow, game, id_act, id_south, S);

  graphic_engine_get_horizontal_arrow(west_arrow, game, id_act, id_west, W);
  graphic_engine_get_horizontal_arrow(east_arrow, game, id_act, id_east, E);

  graphic_engine_get_up_arrow(up_arrow, game, id_act, id_up);
  graphic_engine_get_down_arrow(down_arrow, game, id_act, id_down);

  sprintf(str, "      +------------------+---------------------+----------+");
  screen_area_puts(ge->map, str);
  sprintf(str, "      |     Mini Map     | %-19.19s | Floor: %d |", space_get_name(space_act), player_get_floor(game_get_player(game)));
  screen_area_puts(ge->map, str);
  sprintf(str, "      +------------------+---------------------+----------+");
  screen_area_puts(ge->map, str);
  sprintf(str, "      |       %s        | %-20s|    UP    |", north_symbol, gdesc[0]);
  screen_area_puts(ge->map, str);
  sprintf(str, "      |        %s         | %-20s|    %s     |", north_arrow, gdesc[1], up_arrow);
  screen_area_puts(ge->map, str);
  sprintf(str, "      |  %s%s%s%s%s   | %-20s|          |", west_symbol, west_arrow, act_symbol, east_arrow, east_symbol, gdesc[2]);
  screen_area_puts(ge->map, str);
  sprintf(str, "      |        %s         | %-20s|    %s     |", south_arrow, gdesc[3], down_arrow);
  screen_area_puts(ge->map, str);
  sprintf(str, "      |       %s        | %-20s|  DOWN    |", south_symbol, gdesc[4]);
  screen_area_puts(ge->map, str);
  sprintf(str, "      +------------------+---------------------+----------+");
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
  Space *space_act = NULL;
  Id obj_id = NO_ID, *objects = NULL, player_id = NO_ID, id_west = NO_ID, id_east = NO_ID;
  Character *chrs = NULL, *followers[MAX_CHARACTERS];
  char chr_line1[WORD_SIZE], chr_line2[WORD_SIZE], obj_line1[WORD_SIZE], obj_line2[WORD_SIZE], ply[MAX_CHR_GDESC + 1], str[255], line[128];
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

  strncpy(ply, player_get_gdesc(player), MAX_CHR_GDESC);
  ply[MAX_CHR_GDESC] = '\0';

  n_followers = game_count_followers(game, player_id);
  if (n_followers > 6) {
    n_followers = 6;
  }
  for (i = 0; i < n_followers; i++) {
    followers[i] = game_get_nth_follower(game, player_id, i);
  }
    
  chr_line1[0] = '\0';
  chr_line2[0] = '\0';
  n_chars = 0;
  for (i = 0; i < game_get_n_characters(game); i++) {
    chrs = game_get_character_by_position(game, i);
    if (chrs == NULL) continue;
    if (character_get_location(chrs) != id_act) continue;
    if (character_get_health(chrs) <= 0) continue;
    if (character_get_following(chrs) == player_id) continue;
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
  for (i = 0; i < GDESC_LINES + 6; i++) { 
    str[0] = '\0';

    if(i == 0 || i == 10) sprintf(line, "              +-------------------------------------+");
    else if(i == 1){
      if(n_followers == 0) sprintf(line, "              |                                     |        ");
      else if(n_followers == 1) sprintf(line, "              | %-3.3s                                 |        ", character_get_gdesc(followers[0]));
      else if(n_followers == 2) sprintf(line, "              | %-3.3s %-3.3s                             |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]));
      else if(n_followers == 3) sprintf(line, "              | %-3.3s %-3.3s %-3.3s                         |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]), character_get_gdesc(followers[2]));
      else if(n_followers == 4) sprintf(line, "              | %-3.3s %-3.3s %-3.3s %-3.3s                     |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]), character_get_gdesc(followers[2]), character_get_gdesc(followers[3]));
      else if(n_followers == 5) sprintf(line, "              | %-3.3s %-3.3s %-3.3s %-3.3s %-3.3s                 |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]), character_get_gdesc(followers[2]), character_get_gdesc(followers[3]), character_get_gdesc(followers[4]));
      else sprintf(line, "              | %-3.3s %-3.3s %-3.3s %-3.3s %-3.3s %-3.3s             |        ", character_get_gdesc(followers[0]), character_get_gdesc(followers[1]), character_get_gdesc(followers[2]), character_get_gdesc(followers[3]), character_get_gdesc(followers[4]), character_get_gdesc(followers[5]));
    } 
    else if(i == 2) sprintf(line, "              |                                     |        ");
    else if(i == 3) sprintf(line, "              |                %-3.3s                  |        ", ply);
    else if(i == 4) sprintf(line, "              |                                     |        ");
      
    else if(i == 5){
      if (left_conn == ' ' && right_conn == ' ') {
        sprintf(line, "              |%-37.37s|        ", chr_line1);
      } else if (left_conn != ' ' && right_conn == ' ') {
        sprintf(line, "             %c|%-37.37s|        ", left_conn, chr_line1);
      } else if (left_conn == ' ' && right_conn != ' ') {
        sprintf(line, "              |%-37.37s|%c       ", chr_line1, right_conn);
      } else {
        sprintf(line, "             %c|%-37.37s|%c       ", left_conn, chr_line1, right_conn);
      }
      
    } else if(i == 6){
      sprintf(line, "              |%-37.37s|        ", chr_line2);
    } else if(i == 7){
      sprintf(line, "              |                                     |        ");
    } else if (i == 8) {
      if (strlen(obj_line1) == 0) {
        sprintf(line, "              |                                     |        ");
      } else {
        sprintf(line, "              |%-37.37s|        ", obj_line1);
      }
    } else if (i == 9) {
      if (strlen(obj_line2) == 0) {
        sprintf(line, "              |                                     |        ");
      } else {
        sprintf(line, "              |%-37.37s|        ", obj_line2);
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
  char str[WORD_SIZE + 100];
  CommandCode last_cmd;
  char *chat = NULL, *desc = NULL;
  Character *ch = NULL;
  Id chr_id = NO_ID;
  Player *player = NULL;
  Id player_loc = NO_ID;
  int n_enemies = 0, n_followers = 0, player_hp = 0;
  const char *arg = NULL;

  if(!ge || !game) return;

  last_cmd = command_get_code(game_get_last_command(game));
  chat = game_get_last_chat(game);
  desc = game_get_last_obj_desc(game);
  arg = command_get_arg(game_get_last_command(game));
  player = game_get_player(game);
  if (player) {
    player_loc = player_get_location(player);
    player_hp = player_get_health(player);
    n_followers = game_count_followers(game, player_get_id(player));
  }
  n_enemies = game_space_number_of_enemies(game, player_loc);

  screen_area_puts(ge->map, "----------------------------------------------------------------------");
  screen_area_puts(ge->map, " Action:");

  if (last_cmd == CHAT) {
    if (game_get_last_action(game) == OK && chat != NULL && strlen(chat) > 0) {
      chr_id = game_get_character_id_by_name(game, arg);
      ch = game_get_character_by_id(game, chr_id);
      if (ch != NULL) {
        sprintf(str, "  %s dice: \"%s\"", character_get_name(ch), chat);
        screen_area_puts(ge->map, str);
      }
    } else if (game_get_last_action(game) == ERROR) {
      sprintf(str, "  You cannot talk to '%s': he/she is not here or he/she is not an ally.", arg);
      screen_area_puts(ge->map, str);
    }

  } else if (last_cmd == INSPECT) {
    if (game_get_last_action(game) == OK && desc != NULL && strlen(desc) > 0) {
      sprintf(str, "  [%s]: %s", arg, desc);
      screen_area_puts(ge->map, str);
    } else {
      sprintf(str, "  You cannot inspect '%s': you don't have it and it's not here.", arg);
      screen_area_puts(ge->map, str);
    }

  } else if (last_cmd == ATTACK) {
    if (game_get_last_action(game) == OK) {
      char *attack_msg = game_get_narrator_msg(game);
      if (attack_msg != NULL && strlen(attack_msg) > 0) {
        sprintf(str, "  %s", attack_msg);
        screen_area_puts(ge->map, str);
      }
    } else {
      sprintf(str, "  You cannot attack '%s': he/she is not here, he/she is already dead, or he/she is an ally.", arg);
      screen_area_puts(ge->map, str);
    }

  } else if (last_cmd == TAKE) {
    if (game_get_last_action(game) == OK) {
      sprintf(str, "  You've taken '%s' and you have it in your inventory. If you used a key, it disapeared as well as the chest.", arg);
      screen_area_puts(ge->map, str);
    } else {
      sprintf(str, "  You cannot pick up '%s': it's not here, your inventory is full, or the item is inside a chest.", arg);
      screen_area_puts(ge->map, str);
    }

  } else if (last_cmd == DROP) {
    if (game_get_last_action(game) == OK) {
      sprintf(str, "  You dropped '%s' on the ground.", arg);
      screen_area_puts(ge->map, str);
    } else {      sprintf(str, "  You can't drop '%s': you don't have it in your inventory.", arg);
      screen_area_puts(ge->map, str);
    }

  } else if (last_cmd == USE) {
    if (game_get_last_action(game) == OK) {
      sprintf(str, "  You have used '%s'. Effect applied.", arg);
      screen_area_puts(ge->map, str);
    } else {
      sprintf(str, "  You cannot use '%s': you don't have it, the target is not here, or the syntax is incorrect.", arg);
      screen_area_puts(ge->map, str);
    }

  } else if (last_cmd == OPEN) {
    if (game_get_last_action(game) == OK) {
      screen_area_puts(ge->map, "  You've cleared the way. You can go through now.");
    } else {
      sprintf(str, "  You cannot open that link: incorrect object, it is already open, or you do not have it.");
      screen_area_puts(ge->map, str);
    }

  } else if (last_cmd == RECRUIT) {
    if (game_get_last_action(game) == OK) {
      sprintf(str, "  %s now follows you. (%d allied with you)", arg, n_followers);
      screen_area_puts(ge->map, str);
    } else {
      sprintf(str, "  You cannot recruit '%s': he is not here, he already follows you, or he is not an ally.", arg);
      screen_area_puts(ge->map, str);
    }

  } else if (last_cmd == ABANDON) {
    if (game_get_last_action(game) == OK) {
      sprintf(str, "  %s no longer follows you. You've left him behind.", arg);
      screen_area_puts(ge->map, str);
    } else {
      sprintf(str, "  '%s' wasn't following you.", arg);
      screen_area_puts(ge->map, str);
    }

  } else if (last_cmd == MOVE) {
    if (game_get_last_action(game) == ERROR) {
      sprintf(str, "  You cannot move towards '%s': path blocked or does not exist.", arg);
      screen_area_puts(ge->map, str);
    } else {
      screen_area_puts(ge->map, "  You moved correctly.");
    }

  } else {
    screen_area_puts(ge->map, " ");
  }

  screen_area_puts(ge->map, " ");
  screen_area_puts(ge->map, " Environment:");

  if (n_enemies > 0) {
    sprintf(str, "  [!] %d enemy(s) in the room. They can attack you every turn.", n_enemies);
    screen_area_puts(ge->map, str);
  } else {
    screen_area_puts(ge->map, "  No enemies in this room.");
  }

  if (player_hp > 0 && player_hp <= 30) {
    sprintf(str, "  [!!] Critical state of health: %d HP. Use a healing item or flee.", player_hp);
    screen_area_puts(ge->map, str);
  }

  if (n_followers > 0) {
    sprintf(str, "  %d allies with you. They attack alongside you and can be injured.", n_followers);
    screen_area_puts(ge->map, str);
  }

  {
    char *events = game_get_events_msg(game);

    if (events != NULL && strlen(events) > 0) {
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " Events:");
      sprintf(str, "  %s", events);
      screen_area_puts(ge->map, str);
    }
  }
}




void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Player *player = NULL;
  Status result;
  const char *result_str;
  char str[WORD_SIZE + 100], direction[WORD_SIZE];
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
  int n_followers_dsc, player_id_dsc;
  Character *fol = NULL;
  Link *link_n = NULL, *link_w = NULL, *link_e = NULL, *link_s = NULL;

  
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
      if(game_connection_is_open(game,id_act,N)) sprintf(str, "                                /\\");
      else sprintf(str, "                                ><");
      screen_area_puts(ge->map, str);
    } else {
      sprintf(str, " ");
      screen_area_puts(ge->map, str);
    }

    graphic_engine_print_actual_space(ge, game, id_act);

    if (id_south != NO_ID) {
      if(game_connection_is_open(game,id_act,S)) sprintf(str, "                                \\/      ");
      else sprintf(str, "                                ><");
      screen_area_puts(ge->map, str);
    } else {
      sprintf(str, " ");
      screen_area_puts(ge->map, str);
    }

    /*-------------------------------------------------------*/
    /*                     NARRATOR                          */
    /*-------------------------------------------------------*/
    graphic_engine_print_narrator(ge, game);

  }


  /* Paint in the description area */
  screen_area_clear(ge->descript);
  player = game_get_player(game);
  player_id_dsc = player ? (int)player_get_id(player) : (int)NO_ID;

  /* ---------- OBJECTS ---------- */
  screen_area_puts(ge->descript, " Objects:");

  for (i = 0; i < game_get_n_objects(game); i++) {
    obj = game_get_object_by_position(game, i);
    if (!obj) continue;
    if (player && player_has_object(player, object_get_id(obj)) == TRUE) continue;
    obj_loc = game_get_object_location(game, object_get_id(obj));
    obj_space = game_get_space(game, obj_loc);
    if (obj_space && space_get_discovered(obj_space) == TRUE) {
      sprintf(str, "  Location: %s | %s", space_get_name(obj_space), object_get_name(obj));
      screen_area_puts(ge->descript, str);
    }
  }

  /* ---------- CHARACTERS ---------- */
  screen_area_puts(ge->descript, " ");
  screen_area_puts(ge->descript, " Characters:");

  for (i = 0; i < game_get_n_characters(game); i++) {
    ch = game_get_character_by_position(game, i);
    if (!ch) continue;
    if (character_get_health(ch) <= 0) continue;
    if (character_get_following(ch) == (Id)player_id_dsc) continue;
    ch_space = game_get_space(game, character_get_location(ch));
    if (ch_space && space_get_discovered(ch_space) == TRUE) {
      const char *type = character_get_friendly(ch) == TRUE ? "Ally" : "Enemy";
      sprintf(str, "  Location: %s | [%s] [%dhp] %s %s",space_get_name(game_get_space(game,game_get_character_location(game,character_get_id(ch)))) , type, character_get_health(ch),character_get_name(ch),character_get_gdesc(ch));
      screen_area_puts(ge->descript, str);
    }
  }

  /* ---------- SIGUIENDO ---------- */
  n_followers_dsc = player ? game_count_followers(game, (Id)player_id_dsc) : 0;
  if (n_followers_dsc > 0) {
    screen_area_puts(ge->descript, " ");
    screen_area_puts(ge->descript, " Following:");
    for (i = 0; i < n_followers_dsc; i++) {
      fol = game_get_nth_follower(game, (Id)player_id_dsc, i);
      if (!fol) continue;
      sprintf(str, "  [%dhp] %s %s", character_get_health(fol), character_get_name(fol), character_get_gdesc(fol));
      screen_area_puts(ge->descript, str);
    }
  }

  /* ---------- PLAYER ---------- */
  screen_area_puts(ge->descript, " ");
  screen_area_puts(ge->descript, " Player:");

  if (player) {
    sprintf(str, "  Location: %s | [%dhp]", space_get_name(game_get_space(game, game_get_player_location(game))), player_get_health(player));
    screen_area_puts(ge->descript, str);

    if (player_get_backpack(player) != NULL) {
      objs = player_get_objects(player);
      n_objs = inventory_get_number_objects(player_get_backpack(player));
      if (n_objs == 0) {
        screen_area_puts(ge->descript, " ");
        screen_area_puts(ge->descript, " You do not carry any object");
      } else {
        if (n_objs >= inventory_get_max_objs(player_get_backpack(player))) {
          screen_area_puts(ge->descript, " ");
          screen_area_puts(ge->descript, " Inventory: (FULL)");
        } else {
          screen_area_puts(ge->descript, " ");
          screen_area_puts(ge->descript, " Inventory:");
        }
        for (i = 0; i < n_objs; i++) {
          sprintf(str, "  %s", object_get_name(game_get_object(game, objs[i])));
          screen_area_puts(ge->descript, str);
        }
      }
    }
  }

  /* ---------- CLOSED LINKS ---------- */
  link_n = game_get_link(game, id_act ,id_north);
  link_e = game_get_link(game, id_act ,id_east);
  link_s = game_get_link(game, id_act ,id_south);
  link_w = game_get_link(game, id_act ,id_west);

  if((link_get_open(link_n) == FALSE && link_n) || (link_get_open(link_s) == FALSE && link_s) || (link_get_open(link_e) == FALSE && link_e) || (link_get_open(link_w) == FALSE && link_w)){
    screen_area_puts(ge->descript, " ");
    screen_area_puts(ge->descript, " Closed links:");
    if(link_get_open(link_n) == FALSE && link_n){
      graphic_engine_get_direction_name(direction, link_get_direction(link_n));
      sprintf(str, "  [%s] %s", direction, link_get_name(link_n));
      screen_area_puts(ge->descript, str);
    }
    if(link_get_open(link_s) == FALSE && link_s){
      graphic_engine_get_direction_name(direction, link_get_direction(link_s));
      sprintf(str, "  [%s] %s", direction, link_get_name(link_s));
      screen_area_puts(ge->descript, str);
    }
    if(link_get_open(link_e) == FALSE && link_e){
      graphic_engine_get_direction_name(direction, link_get_direction(link_e));
      sprintf(str, "  [%s] %s", direction, link_get_name(link_e));
      screen_area_puts(ge->descript, str);
    }
    if(link_get_open(link_w) == FALSE && link_w){
      graphic_engine_get_direction_name(direction, link_get_direction(link_w));
      sprintf(str, "  [%s] %s", direction, link_get_name(link_w));
      screen_area_puts(ge->descript, str);
    }
  } else {
    screen_area_puts(ge->descript, " ");
    screen_area_puts(ge->descript, " All Links open");
  }




  /* Paint in the banner area */
  sprintf(str, " Player %d/%d ", game_get_turn(game) + 1, game_get_n_players(game));
  screen_area_puts(ge->banner, str);

  /* Paint in the help area */
  screen_area_clear(ge->help);
  screen_area_puts(ge->help, "                                                             |Comandos disponibles|                                                 ");
  screen_area_puts(ge->help, "      |   Move/m      | Take/t | Drop/d | Attack/a | Chat/c | Inspect/i | Recruit/r | Abandon/ab | exit/e | Use/u   over | open/o   with |       ");
  screen_area_puts(ge->help, "      | <n|s|e|w|u|d> | <obj>  | <obj>  |  <chr>   | <chr>  |   <obj>   |   <chr>   |   <chr>    |        | <obj>  <chr> | <lnk>   <obj> |       ");

  /* Paint in the feedback area */
  screen_area_clear(ge->feedback);
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