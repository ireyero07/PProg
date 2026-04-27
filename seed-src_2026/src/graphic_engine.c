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
 * ~        |                                     |        ~
 * ~        |                                     |        ~
 * ~        |                                     |        ~
 * ~        |                                     |        ~
 * ~        +-------------------------------------+        ~
 * ~                          /\                           ~
 * ~-----+  +-------------------------------------+  +-----~ 
 * ~     |  |  [Lettuce]  [Tomato]                |  |     ~
 * ~     |  |                aaa                  |  |     ~
 * ~     |  |                                     |  |     ~
 * ~     | <| Chef                                |> |     ~
 * ~     |  |                                     |  |     ~
 * ~     |  |      efasf             safsaf       |  |     ~
 * ~     |  |  Crowbar    First Aid Kit  dsgdsg   |  |     ~
 * ~-----+  +-------------------------------------+  +-----~
 * ~                          \/                           ~
 * ~        +-------------------------------------+        ~
 * ~        |                                     |        ~
 * ~        |                                     |        ~
 * ~        |                                     |        ~
 * ~        |                                     |        ~
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

/**
 * @brief Prints an empty (blank) space section for north or south neighbouring space in the map area
 * @param map Pointer to the map screen area
 */
void graphic_engine_print_empty_NorthOrSouth_space(Area *map){
  screen_area_puts(map,"                                                       ");
  screen_area_puts(map,"                                                       ");
  screen_area_puts(map,"                                                       ");
  screen_area_puts(map,"                                                       ");
  screen_area_puts(map,"                                                       ");
}

void graphic_engine_info_row(Graphic_engine *ge, Game *game, Id id_act){
  Space *space_act = NULL, *space = NULL;
  Player *player = NULL;
  Id id = NULL;
  char gdesc[GDESC_LINES][GDESC_LENGTH + 1];
  char str[255];
  char *minimap;
  int i;
  space_act = game_get_space(game,id_act);
  player = game_get_player(game);

  for(i = 0; i< GDESC_LINES; i++){
    strncpy(gdesc[i],space_get_gdesc(space_act,i), GDESC_LENGTH);
    gdesc[i][GDESC_LENGTH] = '\0';
  }

  sprintf(str, "+------------------+---------------------+----------+");
  screen_area_puts(ge->map, str);
  sprintf(str, "|   Mini Map       | %-20s| Floor:%3d|", space_get_name(space_act), (int)(id_act / 100));
  screen_area_puts(ge->map, str);

  if (space_get_discovered(space) == FALSE) {
    minimap = "   ";
  } else {
    if (id_act = id) {
      
    }
  }

  if (id_act >= 51 && id_act <= 55) {
    sprintf(str, "+------------------+---------------------+----------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "|       [%c]  [%c]   | %-20s| UP:       |", (id_act == 54) ? "X" : " ", (id_act == 53) ? "X" : " ", gdesc[0]);
    screen_area_puts(ge->map, str);
    sprintf(str, "|        |    |    | %-20s|           |", gdesc[1]);
    screen_area_puts(ge->map, str);
    sprintf(str, "|       [%c]--[%c]   | %-20s|           |", gdesc[2]);
    screen_area_puts(ge->map, str);
    sprintf(str, "|        |         | %-20s|           |", gdesc[3]);
    screen_area_puts(ge->map, str);
    sprintf(str, "|       [%c]        | %-20s| DOWN:     |", gdesc[4]);
    screen_area_puts(ge->map, str);
    sprintf(str, "+------------------+---------------------+----------+");
    screen_area_puts(ge->map, str);
  } 


  sprintf(str, "+------------------+---------------------+----------+");
  screen_area_puts(ge->map, str);
  sprintf(str, "|                  | %-20s| UP:       |", gdesc[0]);
  screen_area_puts(ge->map, str);
  sprintf(str, "|                  | %-20s|           |", gdesc[1]);
  screen_area_puts(ge->map, str);
  sprintf(str, "|                  | %-20s|           |", gdesc[2]);
  screen_area_puts(ge->map, str);
  sprintf(str, "|                  | %-20s|           |", gdesc[3]);
  screen_area_puts(ge->map, str);
  sprintf(str, "|                  | %-20s| DOWN:     |", gdesc[4]);
  screen_area_puts(ge->map, str);
  sprintf(str, "+------------------+---------------------+----------+");
  screen_area_puts(ge->map, str);
}


/**
 * @brief Prints the north neighbouring space in the map area
 * @param ge Pointer to the graphic engine
 * @param game Pointer to the game
 * @param id_North Id of the north space to print
 */
void graphic_engine_print_North_space (Graphic_engine *ge, Game *game, Id id_North) {
  Space *space_North = NULL;
  char str[255];

  space_North = game_get_space(game, id_North);

  if (id_North == NO_ID) {
    graphic_engine_print_empty_NorthorSouth_space(ge->map);
  } else {
    sprintf(str, "        |                                     |        ");
    screen_area_puts(ge->map, str);
    sprintf(str, "        |                                     |        ");
    screen_area_puts(ge->map, str);
    sprintf(str, "        |                                     |        ");
    screen_area_puts(ge->map, str);
    sprintf(str, "        |                                     |        ");
    screen_area_puts(ge->map, str);
    sprintf(str, "        +-------------------------------------+        ");
    screen_area_puts(ge->map, str);
  }
}

/**
 * @brief Prints the south neighbouring space in the map area
 * @param ge Pointer to the graphic engine
 * @param game Pointer to the game
 * @param id_South Id of the south space to print
 */
void graphic_engine_print_South_space (Graphic_engine *ge, Game *game, Id id_South) {
  Space *space_South = NULL;
  char str[255];

  space_South = game_get_space(game, id_South);

  if (id_South == NO_ID) {
    graphic_engine_print_empty_NorthOrSouth_space(ge->map);
  } else {
    sprintf(str, "        +-------------------------------------+        ");
    screen_area_puts(ge->map, str);
    sprintf(str, "        |                                     |        ");
    screen_area_puts(ge->map, str);
    sprintf(str, "        |                                     |        ");
    screen_area_puts(ge->map, str);
    sprintf(str, "        |                                     |        ");
    screen_area_puts(ge->map, str);
    sprintf(str, "        |                                     |        ");
    screen_area_puts(ge->map, str);
  }
}

/**
 * @brief Prints the west, current and east spaces side by side in the map area
 * @param ge Pointer to the graphic engine
 * @param game Pointer to the game
 * @param id_west Id of the west space
 * @param id_act Id of the current (actual) space
 * @param id_east Id of the east space
 */
void graphic_engine_print_west_actual_east_space(Graphic_engine *ge, Game *game, Id id_west, Id id_act, Id id_east) {
  int i, j, col;
  Space *spaces[3];
  Id ids[3], obj_id = NO_ID, *objects = NULL;
  Character *chars[3];
  char chr[3][MAX_CHR_GDESC + 1], ply[3][MAX_CHR_GDESC + 1], obj_line[3][WORD_SIZE], str[255];
  Object *obj = NULL;
  Player *player;
  long n_objects;


  /* Inicializar arrays de spaces, ids y player */
  if (id_west != NO_ID) {
    spaces[0] = game_get_space(game, id_west);
  } else {
    spaces[0] = NULL;
  }

  if (id_act != NO_ID) {
    spaces[1] = game_get_space(game, id_act);
  } else {
    spaces[1] = NULL;
  }

  if (id_east != NO_ID) {
    spaces[2] = game_get_space(game, id_east);
  } else {
    spaces[2] = NULL;
  }

  ids[0] = id_west; ids[1] = id_act; ids[2] = id_east;
  chars[0] = chars[1] = chars[2] = NULL;

  player = game_get_player(game);

  strncpy(ply[1], player_get_gdesc(player), MAX_CHR_GDESC);
  ply[1][MAX_CHR_GDESC] = '\0';
  ply[0][0] = '\0';
  ply[2][0] = '\0';

  

  /* Inicializar arrays de gdesc, objects y characters */
  for (col = 0; col < 3; col++) {
    for (j = 0; j < MAX_CHR_GDESC; j++) {
      chr[col][j] = ' ';
    }
    chr[col][MAX_CHR_GDESC] = '\0';
    obj_line[col][0] = '\0';

    if (spaces[col] != NULL) {
      /* Character */
      chars[col] = game_get_character_by_space(game, ids[col]);
      if (chars[col] != NULL) {
        strncpy(chr[col], character_get_gdesc(chars[col]), MAX_CHR_GDESC);
        chr[col][MAX_CHR_GDESC] = '\0';
      } else {
        chr[col][0] = '\0'; 
      }
      /* Objects */
      objects = space_get_objects_ids(spaces[col]);
      n_objects = space_get_number_objects(spaces[col]);
      if (n_objects >= 3) {
        for (i = 0, j = 0; i < n_objects; i++) {
          while ((obj_id = objects[j]) == NO_ID) {
            j++;
          }
          obj = game_get_object(game, obj_id);
          j++;
          if (obj != NULL) {
            if (strlen(obj_line[col]) > 0) {
              strcat(obj_line[col], ", ");
            }
            strncat(obj_line[col], object_get_name(obj), 2);
          }
        }
      } else {
        for (i = 0, j = 0; i < n_objects; i++) {
          while ((obj_id = objects[j]) == NO_ID) {
            j++;
          }
          obj = game_get_object(game, obj_id);
          j++;
          if (obj != NULL) {
            if (strlen(obj_line[col]) > 0) {
              strcat(obj_line[col], ", ");
            }
            strcat(obj_line[col], object_get_name(obj));
          }
        }
      }
    }
  }
  space_set_discovered(game_get_space(game,id_act),TRUE);
  /* Ahora pintamos fila por fila combinando las 3 habitaciones horizontalmente */
  for (i = 0; i < GDESC_LINES + 4; i++) { 
    str[0] = '\0';
    for (col = 0; col < 3; col++) {
      char line[64];
      if(col == 0){
        if(id_west == NO_ID){
          strcat(str,"       ");
        } else{
          if (i == 0) { 
            sprintf(line, "-----+ ");
          } else if (i == 1){
            sprintf(line, "     | ");
          } else if (i == 2){
            sprintf(line, "     | ");
          } else if (i == 3){
            sprintf(line, "     | ");
          } else if (i == 4){
            sprintf(line, "     | ");
          } else if (i == 5){
            sprintf(line, "     | ");
          } else if (i == 6){
            sprintf(line, "     | ");
          } else if (i == 7){
            sprintf(line, "     | ");
          } else if (i == 8){
            sprintf(line, "-----+ ");
          }
        }

      } else if(col == 1){
        if (i == 0) { 
          sprintf(line, " +-------------------------------------+ ");
        } else if (i == 1){
            
        } else if (i == 2){
          sprintf(line, " |                %3.3s                  | ", ply[1]);
        } else if (i == 3){
          sprintf(line, " |                                     | ");
        } else if (i == 4){
            
        } else if (i == 5){
            
        } else if (i == 6){
            
        } else if (i == 7){
            
        } else if (i == 8){
          sprintf(line, " +-------------------------------------+ ");  
        }



        



        if (col == 0 && spaces[0] != NULL && spaces[1] != NULL && i == (GDESC_LENGTH / 2)) {
        if(game_connection_is_open(game,ids[1], W)) strcat(str, "<");
        else strcat(str,"X");
        } 
        else if (col == 1 && spaces[1] != NULL && spaces[2] != NULL && i == (GDESC_LENGTH / 2)) {
          if(game_connection_is_open(game,ids[1], E)) strcat(str, ">");
          else strcat(str,"X");
        } 
        else {
          strcat(str, " ");
        }
        screen_area_puts(ge->map, str);

      } else if(col == 2){
        if(id_west == NO_ID){
          strcat(str,"       ");
        } else{
          if (i == 0) { 
            sprintf(line, " +-----");
          } else if (i == 1){
            sprintf(line, " |     ");
          } else if (i == 2){
            sprintf(line, " |     ");
          } else if (i == 3){
            sprintf(line, " |     ");
          } else if (i == 4){
            sprintf(line, " |     ");
          } else if (i == 5){
            sprintf(line, " |     ");
          } else if (i == 6){
            sprintf(line, " |     ");
          } else if (i == 7){
            sprintf(line, " |     ");
          } else if (i == 8){
            sprintf(line, " +-----");
          }
        }

      }
    }
  }
}








void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Player *player = NULL;
  Status result;
  const char *result_str;
  char str[255], *chat;
  char str_desc[255], *desc;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  Id *objs = NULL, obj_loc = NO_ID;
  Object *obj = NULL;
  long n_objs = 0;
  Space *obj_space = NULL;
  Space *ch_space = NULL;
  Character *ch = NULL;
  Space *space_act = NULL;
  Id id_act = NO_ID, id_north = NO_ID, id_south = NO_ID, id_west = NO_ID, id_east = NO_ID, id_up = NO_ID, id_down = NO_ID;;

  
  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_north = game_get_connection(game, id_act, N);
    id_south = game_get_connection(game, id_act, S);
    id_west  = game_get_connection(game, id_act, W);
    id_east  = game_get_connection(game, id_act, E);
    id_up   = game_get_connection(game, id_act, UP);
    id_down = game_get_connection(game, id_act, DOWN);

    /*-------------------------------------------------------*/
    /*                    INFO ROW                           */
    /*-------------------------------------------------------*/
    graphic_engine_info_row(ge, game, id_act);

    /*-------------------------------------------------------*/
    /*                    NORTH SPACE                        */
    /*-------------------------------------------------------*/
    graphic_engine_print_SouthOrNorth_space(ge, game, id_north);
    if (id_north != NO_ID) {
      if(game_connection_is_open(game,id_act,N)) sprintf(str, "                          /\\      ");
      else sprintf(str, "                          ><");
      screen_area_puts(ge->map, str);
    }
    

    /*-------------------------------------------------------*/
    /*               WEST/ACTUAL/EAST SPACES                 */
    /*-------------------------------------------------------*/

    graphic_engine_print_west_actual_east_space(ge, game, id_west, id_act, id_east);

    /*-------------------------------------------------------*/
    /*                    SOUTH SPACE                        */
    /*-------------------------------------------------------*/
    if (id_south != NO_ID) {
      if(game_connection_is_open(game,id_act,S)) sprintf(str, "                          \\/      ");
      else sprintf(str, "                          ><");
      screen_area_puts(ge->map, str);
    }
    graphic_engine_print_SouthOrNorth_space(ge, game, id_south);
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

  /* ---------- CHAT ---------- */
  screen_area_puts(ge->descript, "Chat:");
  chat = game_get_last_chat(game);

  if (chat && strlen(chat) > 0) {
    if (command_get_code(game_get_last_command(game)) == CHAT) {
      ch = game_get_character_by_space(game, space_get_id(space_act));
      if (ch && character_get_friendly(ch)) {
        sprintf(str, " Character %s said: %s", character_get_gdesc(ch), chat);
        screen_area_puts(ge->descript, str);
      }
    } else {
      game_set_last_chat(game, "");
    }
  }

  /* ---------- OBJECT DESCRIPTION (INSPECT) ---------- */
  screen_area_puts(ge->descript, "Object description:");
  desc = game_get_last_obj_desc(game);

  if (desc && strlen(desc) > 0) {
    if (command_get_code(game_get_last_command(game)) == INSPECT && game_get_last_action(game) == OK) {      
      sprintf(str_desc, " The description of %s is: %s", command_get_arg(game_get_last_command(game)), desc);
      screen_area_puts(ge->descript, str_desc);
      } else {
      game_set_last_chat(game, "");
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