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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "space.h"
#include "set.h"
#include "types.h"
#include "player.h"
#include "inventory.h"

#define WIDTH_MAP 57
#define WIDTH_DES 59
#define WIDTH_BAN 12
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

void graphic_engine_print_empty_space(Area *map){
  screen_area_puts(map,"                 ");
  screen_area_puts(map,"                 ");
  screen_area_puts(map,"                 ");
  screen_area_puts(map,"                 ");
  screen_area_puts(map,"                 ");
  screen_area_puts(map,"                 ");
  screen_area_puts(map,"                 ");
  screen_area_puts(map,"                 ");
  screen_area_puts(map,"                 ");
}

void graphic_engine_print_not_discovered_space(Area *map){
  screen_area_puts(map,"                   +---------------+");
  screen_area_puts(map,"                   |               |");
  screen_area_puts(map,"                   |               |");
  screen_area_puts(map,"                   |               |");
  screen_area_puts(map,"                   |               |");
  screen_area_puts(map,"                   |               |");
  screen_area_puts(map,"                   |               |");
  screen_area_puts(map,"                   |               |");
  screen_area_puts(map,"                   +---------------+");
}

void graphic_engine_print_SouthOrNorth_space (Graphic_engine *ge, Game *game, Id id_SouthOrNorth) {
  Space *space_SouthOrNorth = NULL;
  Id *space_SouthOrNorth_objects = NULL, obj_id = NO_ID;
  Character *character_SouthOrNorth = NULL;
  Object *obj = NULL;
  char chr[MAX_CHR_GDESC + 1] = "",  space_SouthOrNorth_objects_line[WORD_SIZE] = "", str[255], gdesc[GDESC_LINES][GDESC_LENGTH + 1];
  int i, k;
  long n_objects;
  space_SouthOrNorth = game_get_space(game, id_SouthOrNorth);

  if (id_SouthOrNorth == NO_ID) {
    graphic_engine_print_empty_space(ge->map);
  } else if (!space_get_discovered(game_get_space(game,id_SouthOrNorth))) {
    graphic_engine_print_not_discovered_space(ge->map);
  } else {
    /* character back or next space */
    character_SouthOrNorth = game_get_character_by_space(game, id_SouthOrNorth);

    chr[0] = '\0';
    if (character_SouthOrNorth != NULL) {
      strncpy(chr, character_get_gdesc(character_SouthOrNorth), MAX_CHR_GDESC);
      chr[MAX_CHR_GDESC] = '\0';
    }
    /* object back or next space */
    space_SouthOrNorth_objects = space_get_objects_ids(space_SouthOrNorth);
    n_objects = space_get_number_objects(space_SouthOrNorth);

    if (n_objects >= 3) {
      for (i = 0, k = 0; i < n_objects; i++) {
        while ((obj_id = space_SouthOrNorth_objects[k]) == NO_ID) {
          k++;
        }
        obj = game_get_object(game, obj_id);
        k++;
        if (obj != NULL) {
          if (strlen(space_SouthOrNorth_objects_line) > 0) {
          strcat(space_SouthOrNorth_objects_line, ", ");
          }
          strncat(space_SouthOrNorth_objects_line, object_get_name(obj), 2);
        }
      }
    }
    else
    {
      for (i = 0, k = 0; i < n_objects; i++) {
        while ((obj_id = space_SouthOrNorth_objects[k]) == NO_ID) {
          k++;
        }     
        obj = game_get_object(game, obj_id);
        k++;
        if (obj != NULL) {
          if (strlen(space_SouthOrNorth_objects_line) > 0) {
            strcat(space_SouthOrNorth_objects_line, ", ");
          }
          strcat(space_SouthOrNorth_objects_line, object_get_name(obj));
        }
      }
    }

    /* Gdesc back or next space  */
    for(i=0; i<GDESC_LINES; i++){
      strncpy(gdesc[i], space_get_gdesc(space_SouthOrNorth, i), GDESC_LENGTH);
      gdesc[i][GDESC_LENGTH] = '\0';
    }

    sprintf(str, "                   +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                   |      %3.3s   %3d|", chr, (int) id_SouthOrNorth);
    screen_area_puts(ge->map, str);
    sprintf(str, "                   |%s      |", gdesc[0]);
    screen_area_puts(ge->map, str);
    sprintf(str, "                   |%s      |", gdesc[1]);
    screen_area_puts(ge->map, str);
    sprintf(str, "                   |%s      |", gdesc[2]);
    screen_area_puts(ge->map, str);
    sprintf(str, "                   |%s      |", gdesc[3]);
    screen_area_puts(ge->map, str);
    sprintf(str, "                   |%s      |", gdesc[4]);
    screen_area_puts(ge->map, str);
    sprintf(str, "                   |%-15.15s|", space_SouthOrNorth_objects_line);
    screen_area_puts(ge->map, str);
    sprintf(str, "                   +---------------+");
    screen_area_puts(ge->map, str);
  }
}

void graphic_engine_print_west_actual_east_space(Graphic_engine *ge, Game *game, Id id_west, Id id_act, Id id_east) {
  int i, j, col;
  Space *spaces[3];
  Id ids[3], obj_id = NO_ID, *objects = NULL;
  Character *chars[3];
  char gdesc[3][GDESC_LINES][GDESC_LENGTH + 1], chr[3][MAX_CHR_GDESC + 1], ply[3][MAX_CHR_GDESC + 1], obj_line[3][WORD_SIZE], str[255];
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
    for (i = 0; i < GDESC_LINES; i++) {
      for (j = 0; j < GDESC_LENGTH; j++) {
        gdesc[col][i][j] = ' ';
      } 
    }   
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

      /* Gdesc */
      for (i = 0; i < GDESC_LINES; i++) {
        const char *line = space_get_gdesc(spaces[col], i);
        for (j = 0; j < GDESC_LENGTH && line[j] != '\0'; j++) {
          gdesc[col][i][j] = line[j];
        }         
        gdesc[col][i][GDESC_LENGTH] = '\0';
      }
    }
  }
  space_set_discovered(game_get_space(game,id_act),TRUE);
  /* Ahora pintamos fila por fila combinando las 3 habitaciones horizontalmente */
  for (i = 0; i < GDESC_LINES + 4; i++) { 
    str[0] = '\0';
    for (col = 0; col < 3; col++) {
      char line[64];
      if (spaces[col] == NULL) {
        /* Nada si no hay habitación */
        strcat(str, "                 ");
        strcat(str, " ");
      } 
      else {
        if(space_get_discovered(spaces[col])==TRUE){
          if (i == 0) { /* borde superior */
            sprintf(line, "+---------------+ ");
          }
          else if (i == 1) { /* linea de player, character e id */
            if (col == 1) {
              sprintf(line, "| %3.3s  %3.3s   %3d| ", ply[1], chr[col], (int) ids[col]);
            } 
            else if (col == 0) {
              sprintf(line, "|      %3.3s   %3d| ", chr[col], (int) ids[col]);
            } 
            else {
              sprintf(line, "|      %3.3s   %3d| ", chr[col], (int) ids[col]);
            } 
          } 
          else if (i >= 2 && i < 7) { /* líneas gdesc */
            sprintf(line, "|%s      | ", gdesc[col][i - 2]);
          } else if (i == 7) { /* línea de objects */
            sprintf(line, "|%-15.15s| ", obj_line[col]);
          } else if (i == 8) {
            sprintf(line, "+---------------+ ");
          }
        }else{
          if (i == 0) { /* borde superior */
            sprintf(line, "+---------------+ ");
          }
          else if (i >= 1 && i <= 7) {
            sprintf(line, "|               | ");
          } else { /* borde inferior */
            sprintf(line, "+---------------+ ");
          }
        }
        strcat(str, line);
      }
      /* Flechas entre habitaciones */
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
    }
    screen_area_puts(ge->map, str);
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
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_left = NO_ID, id_right = NO_ID;

  
  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back  = game_get_connection(game, id_act, N);
    id_next  = game_get_connection(game, id_act, S);
    id_left  = game_get_connection(game, id_act, W);
    id_right = game_get_connection(game, id_act, E);

    /*-------------------------------------------------------*/
    /*                    BACK SPACE                         */
    /*-------------------------------------------------------*/
    graphic_engine_print_backOrNext_space (ge, game, id_back);
    if (id_back != NO_ID) {
      if(game_connection_is_open(game,id_act,N)) sprintf(str, "                           ^         ");
      else sprintf(str, "                           X         ");
      screen_area_puts(ge->map, str);
    }
    
    
    /*-------------------------------------------------------*/
    /*               LEFT/ACTUAL/RIGHT SPACES                */
    /*-------------------------------------------------------*/
    
    graphic_engine_print_left_actual_right_space (ge, game, id_left, id_act, id_right);

    /*-------------------------------------------------------*/
    /*                    NEXT SPACE                         */
    /*-------------------------------------------------------*/
    if (id_next != NO_ID) { 
      if(game_connection_is_open(game,id_act,S)) sprintf(str, "                           V         ");
      else sprintf(str, "                           X         ");
      screen_area_puts(ge->map, str);
    }
    graphic_engine_print_backOrNext_space (ge, game, id_next);
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
        sprintf(str, "Player's inventory:");
        screen_area_puts(ge->descript, str);
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
    if (command_get_code(game_get_last_command(game)) == INSPECT) {      
      sprintf(str_desc, " The description of %s is: %s", command_get_arg(game_get_last_command(game)), desc);
      screen_area_puts(ge->descript, str_desc);
      
    } else {
      game_set_last_obj_desc(game, "");
    }
  }


  /* Paint in the banner area */
  sprintf(str, " Player %d/%d ",game_get_turn(game)+1, game_get_n_players(game));
  screen_area_puts(ge->banner, str);

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " move or m (n,s,e,w), take or t, drop or d, attack or a, chat or c, inspect or i, exit or e");
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