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
  Status result;
  const char *result_str;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i,k;

  //                Declaration for objects
  Object *obj = NULL;
  char space_act_objects_line[WORD_SIZE] = "", space_next_objects_line[WORD_SIZE] = "", space_back_objects_line[WORD_SIZE] = "", space_left_objects_line[WORD_SIZE] = "", space_right_objects_line[WORD_SIZE] = "";
  Id *space_act_objects = NULL, *space_next_objects = NULL, *space_back_objects = NULL, *space_left_objects = NULL, *space_right_objects = NULL, obj_loc = NO_ID, obj_id= NO_ID;
  int i, k;
  long n_objects, obj_location;

  //               Declaration for characters
  Character *ch = NULL, *character_act = NULL, *character_next = NULL, *character_back = NULL, *character_left = NULL, *character_right = NULL;
  char chr[MAX_CHR_GDESC + 1] = "";
  Id ch_act_id = NO_ID, ch_next_id = NO_ID, ch_back_id = NO_ID, ch_left_id = NO_ID, ch_right_id = NO_ID;


  //               Declaration for space
  Space *space_act = NULL, *space_next = NULL, *space_back = NULL, *space_right = NULL, *space_left = NULL;
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_left = NO_ID, id_right = NO_ID;
  char gdesc[GDESC_LINES][GDESC_LENGTH + 1] = ""; 

  //               Declaration for player
  Player *player = NULL;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_left = space_get_west(space_act);
    id_right = space_get_east(space_act);

    space_back = game_get_space(game, id_back);
    space_next = game_get_space(game, id_next);
    space_left = game_get_space(game, id_left);
    space_right = game_get_space(game, id_right);

    /*---------------------------------------------------------*/
    /*                    ACTUAL SPACE                         */
    /*---------------------------------------------------------*/
    if (id_act != NO_ID) {
      // Character actual space
      Set *chars_act = space_get_character(space_act);

      if (set_get_n_ids(chars_act) > 0){
        ch_act_id = set_get_id_at(chars_act,0);
      }

      if(ch_act_id != NO_ID){
        character_act = game_get_character(game,ch_act_id);
      }

      chr[0] = '\0';

      if(character_act != NULL){
        strncpy(chr, character_get_gdesc(character_act), MAX_CHR_GDESC);
        chr[MAX_CHR_GDESC] = '\0';
      }
      
      // object actual space

      space_act_objects = space_get_objects_ids(space_act);

      n_objects = space_get_number_objects(space_act);

      /* Get the object from the game using its id */
      if (n_objects >= 3)
      {
        for (i = 0, k = 0; i < n_objects; i++)
        {
          /* Only writes if id!=NO_ID (because there may be hollow positions in the array of ids) */
          while ((obj_id = space_act_objects[k]) == NO_ID)
            k++;
          obj = game_get_object(game, obj_id);
          k++;

          if (obj != NULL)
          {
            /* If the string already contains objects, add a separator */
            if (strlen(space_act_objects_line) > 0)
              strcat(space_act_objects_line, ", ");

            /* Add only the first 2 characters of the object name */
            strncat(space_act_objects_line, object_get_name(obj), 2);
          }
        }
      }
      else
      {
        for (i = 0, k = 0; i < n_objects; i++)
        {
          /* Only writes if id!=NO_ID (because there may be hollow positions in the array of ids) */
          while ((obj_id = space_act_objects[k]) == NO_ID)
            k++;
          obj = game_get_object(game, obj_id);
          k++;

          if (obj != NULL)
          {

            if (strlen(space_act_objects_line) > 0)
            {
              strcat(space_act_objects_line, ", ");
            }

            /* Add the full object name to the string */
            strcat(space_act_objects_line, object_get_name(obj));
          }
        }
      }

      // Gdesc actual space 
      for(i=0; i<GDESC_LINES; i++){
        strncpy(gdesc[i], space_get_gdesc(space_act,i), GDESC_LENGTH);
        gdesc[i][GDESC_LENGTH] = '\0';
      }

      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | ^C>  %s    %2d|", chr, (int) id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[4]);
      screen_area_puts(ge->map, str);
      sprintf(str, "%s|%-15.15s|%s", space_act_objects_line);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
    }

    /*-------------------------------------------------------*/
    /*                    NEXT SPACE                         */
    /*-------------------------------------------------------*/
    if (id_next != NO_ID) {
      // Character next space
      Set *chars_next = space_get_character(space_next);

      if (set_get_n_ids(chars_next) > 0){
        ch_next_id = set_get_id_at(chars_next,0);
      }

      if(ch_next_id != NO_ID){
        character_next = game_get_character(game,ch_next_id);
      }

      chr[0] = '\0';

      if(character_next != NULL){
        strncpy(chr, character_get_gdesc(character_next), MAX_CHR_GDESC);
        chr[MAX_CHR_GDESC] = '\0';
      }
      
      // object next space

      space_next_objects = space_get_objects_ids(space_next);

      n_objects = space_get_number_objects(space_next);

      if (n_objects >= 3)
      {
        for (i = 0, k = 0; i < n_objects; i++)
        {
          while ((obj_id = space_next_objects[k]) == NO_ID)
            k++;
          obj = game_get_object(game, obj_id);
          k++;

          if (obj != NULL)
          {
            if (strlen(space_next_objects_line) > 0)
              strcat(space_next_objects_line, ", ");

            strncat(space_next_objects_line, object_get_name(obj), 2);
          }
        }
      }
      else
      {
        for (i = 0, k = 0; i < n_objects; i++)
        {
          while ((obj_id = space_next_objects[k]) == NO_ID)
            k++;
          obj = game_get_object(game, obj_id);
          k++;

          if (obj != NULL)
          {

            if (strlen(space_next_objects_line) > 0)
            {
              strcat(space_next_objects_line, ", ");
            }

            strcat(space_next_objects_line, object_get_name(obj));
          }
        }
      }

      // Gdesc next space 
      for(i=0; i<GDESC_LINES; i++){
        strncpy(gdesc[i], space_get_gdesc(space_next,i), GDESC_LENGTH);
        gdesc[i][GDESC_LENGTH] = '\0';
      }

      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | ^C>  %s    %2d|", chr, (int) id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[4]);
      screen_area_puts(ge->map, str);
      sprintf(str, "%s|%-15.15s|%s", space_next_objects_line);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
    }
    
    /*-------------------------------------------------------*/
    /*                    BACK SPACE                         */
    /*-------------------------------------------------------*/
    if (id_back != NO_ID) {
      Set *chars_back = space_get_character(space_back);

      if (set_get_n_ids(chars_back) > 0){
          ch_back_id = set_get_id_at(chars_back,0);
      }

      if(ch_back_id != NO_ID){
          character_back = game_get_character(game,ch_back_id);
      }

      chr[0] = '\0';

      if(character_back != NULL){
          strncpy(chr, character_get_gdesc(character_back), MAX_CHR_GDESC);
          chr[MAX_CHR_GDESC] = '\0';
      }

      // object back space
      space_back_objects = space_get_objects_ids(space_back);
      n_objects = space_get_number_objects(space_back);

      if (n_objects >= 3)
      {
          for (i = 0, k = 0; i < n_objects; i++)
          {
              while ((obj_id = space_back_objects[k]) == NO_ID)
                  k++;
              obj = game_get_object(game, obj_id);
              k++;

              if (obj != NULL)
              {
                  if (strlen(space_back_objects_line) > 0)
                      strcat(space_back_objects_line, ", ");

                  strncat(space_back_objects_line, object_get_name(obj), 2);
              }
          }
      }
      else
      {
          for (i = 0, k = 0; i < n_objects; i++)
          {
              while ((obj_id = space_back_objects[k]) == NO_ID)
                  k++;
              obj = game_get_object(game, obj_id);
              k++;

              if (obj != NULL)
              {
                  if (strlen(space_back_objects_line) > 0)
                      strcat(space_back_objects_line, ", ");

                  strcat(space_back_objects_line, object_get_name(obj));
              }
          }
      }

      // Gdesc back space 
      for(i=0; i<GDESC_LINES; i++){
          strncpy(gdesc[i], space_get_gdesc(space_back,i), GDESC_LENGTH);
          gdesc[i][GDESC_LENGTH] = '\0';
      }


        sprintf(str, "  +---------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  | ^C>  %s    %2d|", chr, (int) id_back);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |%s             |", gdesc[0]);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |%s             |", gdesc[1]);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |%s             |", gdesc[2]);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |%s             |", gdesc[3]);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |%s             |", gdesc[4]);
        screen_area_puts(ge->map, str);
        sprintf(str, "%s|%-15.15s|%s", space_back_objects_line);
        screen_area_puts(ge->map, str);
        sprintf(str, "  +---------------+");
        screen_area_puts(ge->map, str);
    }

    /*-------------------------------------------------------*/
    /*                    LEFT SPACE (WEST)                 */
    /*-------------------------------------------------------*/
    if (id_left != NO_ID) {
      Set *chars_left = space_get_character(space_left);

      if (set_get_n_ids(chars_left) > 0){
          ch_left_id = set_get_id_at(chars_left,0);
      }

      if(ch_left_id != NO_ID){
          character_left = game_get_character(game,ch_left_id);
      }

      chr[0] = '\0';

      if(character_left != NULL){
          strncpy(chr, character_get_gdesc(character_left), MAX_CHR_GDESC);
          chr[MAX_CHR_GDESC] = '\0';
      }

      // object left space
      space_left_objects = space_get_objects_ids(space_left);
      n_objects = space_get_number_objects(space_left);

      if (n_objects >= 3)
      {
          for (i = 0, k = 0; i < n_objects; i++)
          {
              while ((obj_id = space_left_objects[k]) == NO_ID)
                  k++;
              obj = game_get_object(game, obj_id);
              k++;

              if (obj != NULL)
              {
                  if (strlen(space_left_objects_line) > 0)
                      strcat(space_left_objects_line, ", ");

                  strncat(space_left_objects_line, object_get_name(obj), 2);
              }
          }
      }
      else
      {
          for (i = 0, k = 0; i < n_objects; i++)
          {
              while ((obj_id = space_left_objects[k]) == NO_ID)
                  k++;
              obj = game_get_object(game, obj_id);
              k++;

              if (obj != NULL)
              {
                  if (strlen(space_left_objects_line) > 0)
                      strcat(space_left_objects_line, ", ");

                  strcat(space_left_objects_line, object_get_name(obj));
              }
          }
      }

      // Gdesc left space 
      for(i=0; i<GDESC_LINES; i++){
          strncpy(gdesc[i], space_get_gdesc(space_left,i), GDESC_LENGTH);
          gdesc[i][GDESC_LENGTH] = '\0';
      }

      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | ^C>  %s    %2d|", chr, (int) id_left);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[4]);
      screen_area_puts(ge->map, str);
      sprintf(str, "%s|%-15.15s|%s", space_left_objects_line);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
    }

    /*-------------------------------------------------------*/
    /*                    RIGHT SPACE (EAST)                */
    /*-------------------------------------------------------*/
    if (id_right != NO_ID) {
      Set *chars_right = space_get_character(space_right);

      if (set_get_n_ids(chars_right) > 0){
          ch_right_id = set_get_id_at(chars_right,0);
      }

      if(ch_right_id != NO_ID){
          character_right = game_get_character(game,ch_right_id);
      }

      chr[0] = '\0';

      if(character_right != NULL){
          strncpy(chr, character_get_gdesc(character_right), MAX_CHR_GDESC);
          chr[MAX_CHR_GDESC] = '\0';
      }

      // object right space
      space_right_objects = space_get_objects_ids(space_right);
      n_objects = space_get_number_objects(space_right);

      if (n_objects >= 3)
      {
          for (i = 0, k = 0; i < n_objects; i++)
          {
              while ((obj_id = space_right_objects[k]) == NO_ID)
                  k++;
              obj = game_get_object(game, obj_id);
              k++;

              if (obj != NULL)
              {
                  if (strlen(space_right_objects_line) > 0)
                      strcat(space_right_objects_line, ", ");

                  strncat(space_right_objects_line, object_get_name(obj), 2);
              }
          }
      }
      else
      {
          for (i = 0, k = 0; i < n_objects; i++)
          {
              while ((obj_id = space_right_objects[k]) == NO_ID)
                  k++;
              obj = game_get_object(game, obj_id);
              k++;

              if (obj != NULL)
              {
                  if (strlen(space_right_objects_line) > 0)
                      strcat(space_right_objects_line, ", ");

                  strcat(space_right_objects_line, object_get_name(obj));
              }
          }
      }

      // Gdesc right space 
      for(i=0; i<GDESC_LINES; i++){
          strncpy(gdesc[i], space_get_gdesc(space_right,i), GDESC_LENGTH);
          gdesc[i][GDESC_LENGTH] = '\0';
      }

      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | ^C>  %s    %2d|", chr, (int) id_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s             |", gdesc[4]);
      screen_area_puts(ge->map, str);
      sprintf(str, "%s|%-15.15s|%s", space_right_objects_line);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
    }

    
  
  /* Paint in the description area */
  screen_area_clear(ge->descript);

  /* ---------- OBJECTS ---------- */
  screen_area_puts(ge->descript, "Objects:\n");

  for (i = 0; i<game_get_n_objects(game); i++) {
    obj = game_get_object_by_position(game, i);

    if (obj) {
      sprintf(str, "  %s (loc:%ld)\n", object_get_name(obj), game_get_object_location(game, object_get_id(obj)));
      screen_area_puts(ge->descript, str);
    }
  }

  /* ---------- CHARACTERS ---------- */
  screen_area_puts(ge->descript, "Characters:\n");

  for (i = 0; i<game_get_n_characters(game); i++) {
    ch = game_get_character_by_position(game, i);

    if (ch) {
      sprintf(str, "  %s (loc: %ld, hp:%d)\n", character_get_name(ch), character_get_location(ch), character_get_health(ch));
      screen_area_puts(ge->descript, str);
      }
    }

  /* ---------- PLAYER ---------- */
  screen_area_puts(ge->descript, "Player:");
  player = game_get_player(game);

  if (player) {
    sprintf(str, "  (loc: %ld, hp:%d)\n", player_get_location(player), player_get_health(player));
    screen_area_puts(ge->descript, str);

    if (player_get_object(player) != NO_ID) {
      obj = game_get_object(game, player_get_object(player));
      sprintf(str, "Player has a %s", object_get_name(obj));
      screen_area_puts(ge->descript, str);
    } else {
    screen_area_puts(ge->descript, "Player has no objects");
    }
  }

  /* ---------- CHAT ---------- */
  screen_area_puts(ge->descript, "Chat:\n");



  /* Paint in the banner area */
  screen_area_puts(ge->banner, " The haunted castle game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, left or l, right or r, take or t, drop or d, attack or a, chat or c, exit or e");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  screen_area_clear(ge->feedback);
  last_cmd = command_get_code(game_get_last_command(game));
  result = game_get_last_action_status(game);

  if (result == OK)
    result_str = "OK";
  else
    result_str = "ERROR";

  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], result_str);

  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
}