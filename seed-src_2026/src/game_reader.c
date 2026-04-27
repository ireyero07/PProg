/**
 * @brief It implements the game reader module
 *
 * @file game_reader.c
 * @author Ivan
 * @version 0
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "space.h"

/**
 * Private functions
 */

/**
 * @brief It loads the game spaces from a file
 * @author Ivan
 *
 * This function reads a file containing the description of the spaces
 * and adds them to the game structure.
 *
 * @param game a pointer to the game structure
 * @param filename the name of the file with the spaces information
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load(Game *game, const char *filename);

/**
 * Game_reader code
 */

/**
 * @brief It creates a game from a file
 */
Status game_reader_create_from_file(Game **game, char *filename)
{
  Space *space = NULL;

  if (!game || !filename)
    return ERROR;

  *game = game_create();
  if (!*game)
  {
    return ERROR;
  }

  if (game_reader_load(*game, filename) == ERROR)
  {
    game_destroy(*game);
    *game = NULL;
    return ERROR;
  }

  if (game_get_n_players(*game) <= 0)
  {
    game_destroy(*game);
    *game = NULL;
    return ERROR;
  }

  space = game_get_space(*game, game_get_player_location(*game));
  if (!space)
  {
    game_destroy(*game);
    *game = NULL;
    return ERROR;
  }

  space_set_discovered(space, TRUE);

  return OK;
}

/**
 * @brief It loads the spaces from a file
 */
Status game_reader_load(Game *game, const char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[GDESC_LINES][GDESC_LENGTH + 1] = {""};
  char player_gdesc[MAX_PLAYER_GDESC + 1];
  char character_gdesc[MAX_CHR_GDESC + 1];
  char char_msg[WORD_SIZE];
  char obj_desc[MAX_DESC];
  char *toks = NULL;
  Id idLink = NO_ID, idCharacter = NO_ID, idSpace = NO_ID, idFinal = NO_ID, idObject = NO_ID, obj_dependency = NO_ID, obj_open = NO_ID;
  Id idPlayer = NO_ID;
  Space *space = NULL;
  Object *object = NULL;
  Player *player = NULL;
  Character *character = NULL;
  Link *link = NULL;
  Status status = OK;
  int i, health, backpack_capacity, friendly, direction, open, numobjects = 0, numchr = 0, numlinks = 0, numplayers = 0, numspaces = 0, obj_health;
  Bool boss, obj_movable;

  /* Error control */
  if (!game || !filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  /* Read the file line by line */
  while (fgets(line, WORD_SIZE, file))
  {
    /* Check if the line defines a space */
    if (strncmp("#s:", line, 3) == 0)
    {

      /* Parse the space data */
      toks = strtok(line + 3, "|");
      idSpace = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
      {
        status = ERROR;
        break;
      }
      strncpy(name, toks, WORD_SIZE - 1);
      name[WORD_SIZE - 1] = '\0';

      for (i = 0; i < GDESC_LINES; i++)
      {
        toks = strtok(NULL, "|");
        if (toks)
        {
          strncpy(gdesc[i], toks, GDESC_LENGTH);
          gdesc[i][GDESC_LENGTH] = '\0';
        }
        else
        {
          gdesc[i][0] = '\0';
        }
      }
      numspaces++;

#ifdef DEBUG
      printf("Read: s:%ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s|%s|%s|\n",
             idSpace, name, north, east, south, west, gdesc[0], gdesc[1], gdesc[2], gdesc[3], gdesc[4]);
#endif

      if (numspaces > MAX_SPACES)
      {
        printf("Error: demasiados espacios\n");
        game_set_finished(game, TRUE);
        fclose(file);
        return ERROR;
      }
      else
      {
        /* Create the space and add it to the game */
        space = space_create(idSpace);
        if (space != NULL)
        {
          space_set_name(space, name);

          for (i = 0; i < GDESC_LINES; i++)
          {
            if (gdesc[i][0] != '\0')
            {
              space_set_gdesc(space, gdesc[i], i);
            }
          }
          game_add_space(game, space);
        }
      }
    }

    /* Check if the line defines an object */
    else if (strncmp("#o:", line, 3) == 0)
    {

      /* Parse the space data */
      toks = strtok(line + 3, "|");
      idObject = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
      {
        status = ERROR;
        break;
      }
      strncpy(name, toks, WORD_SIZE - 1);
      name[WORD_SIZE - 1] = '\0';

      toks = strtok(NULL, "|");
      idSpace = atol(toks);

      toks = strtok(NULL, "|");
      strncpy(obj_desc, toks, MAX_DESC - 1);
      obj_desc[MAX_DESC - 1] = '\0';
      numobjects++;

      toks = strtok(NULL, "|");
      obj_health = atol(toks);

      toks = strtok(NULL, "|");
      if(atol(toks) == 0){
        obj_movable = FALSE;
      } else {
        obj_movable = TRUE;
      }

      toks = strtok(NULL, "|");
      obj_dependency = atol(toks);

      toks = strtok(NULL, "|");
      obj_open = atol(toks);

#ifdef DEBUG
      printf("Read: o:%ld|%s|%ld\n",
             idObject, name, idSpace);
#endif

      if (numobjects > MAX_OBJECTS)
      {
        printf("Error: demasiados objetos\n");
        game_set_finished(game, TRUE);
        fclose(file);
        return ERROR;
      }
      else
      /* Create the object and add it to the space */
      {
        object = object_create(idObject);
        if (object != NULL)
        {
          object_set_name(object, name);
          object_set_description(object, obj_desc);
          object_set_health(object, obj_health);
          object_set_movable(object, obj_movable);
          object_set_dependency(object, obj_dependency);
          object_set_open(object, obj_open);
          game_add_object(game, object);
          space = game_get_space(game, idSpace);

          if (space)
          {
            space_add_object(space, idObject);
          }
        }
      }
    }

    /*LOAD PLAYERS*/
    else if (strncmp("#p:", line, 3) == 0)
    {

      /* Divide the player data */
      toks = strtok(line + 3, "|");
      idPlayer = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
      {
        status = ERROR;
        break;
      }
      strncpy(name, toks, WORD_SIZE - 1);
      name[WORD_SIZE - 1] = '\0';

      toks = strtok(NULL, "|");
      strncpy(player_gdesc, toks, MAX_PLAYER_GDESC);
      player_gdesc[MAX_PLAYER_GDESC] = '\0';
      toks = strtok(NULL, "|");
      idSpace = atol(toks);

      toks = strtok(NULL, "|");
      health = atoi(toks);

      toks = strtok(NULL, "|");
      backpack_capacity = atoi(toks);
      numplayers++;

#ifdef DEBUG
      printf("Read: p:%ld|%s|%s|%ld|%d|%d|\n",
             idPlayer, name, player_gdesc, idSpace, health, backpack_capacity);
#endif

      if (numplayers > MAX_PLAYERS)
      {
        printf("Error: demasiados jugadores\n");
        game_set_finished(game, TRUE);
        fclose(file);
        return ERROR;
      }
      else
      /* Create the player and add it to the game */
      {
        player = player_create(idPlayer, backpack_capacity);
        if (player != NULL)
        {
          player_set_name(player, name);
          player_set_gdesc(player, player_gdesc);
          player_set_location(player, idSpace);
          player_set_health(player, health);
          if (game_add_player(game, player) == ERROR)
          {
            player_destroy(player);
          }
        }
      }
    }

    /*LOAD CHARACTERS*/
    else if (strncmp("#c:", line, 3) == 0)
    {

      /* Divide the character data */
      toks = strtok(line + 3, "|");
      idCharacter = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
      {
        status = ERROR;
        break;
      }
      strncpy(name, toks, WORD_SIZE - 1);
      name[WORD_SIZE - 1] = '\0';

      toks = strtok(NULL, "|");
      strncpy(character_gdesc, toks, MAX_CHR_GDESC);
      character_gdesc[MAX_CHR_GDESC] = '\0';
      toks = strtok(NULL, "|");
      idSpace = atol(toks);

      toks = strtok(NULL, "|");
      health = atoi(toks);

      toks = strtok(NULL, "|");
      friendly = atoi(toks);

      toks = strtok(NULL, "|");
      strncpy(char_msg, toks, WORD_SIZE);
      char_msg[WORD_SIZE - 1] = '\0';

      boss = FALSE;
      toks = strtok(NULL, "|");
      if (strncmp(toks, "F", 1) == 0)
      {
        boss = FALSE;
      }
      else if (strncmp(toks, "T", 1) == 0)
      {
        boss = TRUE;
      }

      numchr++;

#ifdef DEBUG
      printf("Read: c:%ld|%s|%s|%ld|%d|%d|%s|%s|\n",
             idCharacter, name, character_gdesc, idSpace, health, friendly, char_msg, boss);
#endif

      if (numchr > MAX_CHARACTERS)
      {
        printf("Error: demasiados characters\n");
        game_set_finished(game, TRUE);
        fclose(file);
        return ERROR;
      }
      else
      {
        /* Create the character and add it to the game */
        character = character_create(idCharacter);
        if (character != NULL)
        {
          character_set_name(character, name);
          character_set_gdesc(character, character_gdesc);
          character_set_location(character, idSpace);
          character_set_health(character, health);
          character_set_friendly(character, friendly);
          character_set_message(character, char_msg);

          space = game_get_space(game, idSpace);
          if (space != NULL)
          {

            if (game_get_number_of_boss_in_space(game, space) < MAX_BOSS_SPACE)
            {
              character_set_boss(character, boss);
            }
            
            space_add_character(space, idCharacter);
          }

          if (game_add_character(game, character) == ERROR)
          {
            character_destroy(character);
          }
        }
      }
    }

    /*LOAD LINKS*/
    else if (strncmp("#l:", line, 3) == 0)
    {

      /* Divide the link data */
      toks = strtok(line + 3, "|");
      idLink = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
      {
        status = ERROR;
        break;
      }
      strncpy(name, toks, WORD_SIZE - 1);
      name[WORD_SIZE - 1] = '\0';

      toks = strtok(NULL, "|");
      idSpace = atol(toks);

      toks = strtok(NULL, "|");
      idFinal = atol(toks);

      toks = strtok(NULL, "|");
      direction = atoi(toks);

      toks = strtok(NULL, "|");
      open = atoi(toks);
      numlinks++;

#ifdef DEBUG
      printf("Read: l:%ld|%s|%ld|%ld|%d|%d|\n",
             idLink, name, idSpace, idFinal, direction, open);
#endif

      if (numlinks > MAX_LINKS)
      {
        printf("Error: demasiados links\n");
        game_set_finished(game, TRUE);
        fclose(file);
        return ERROR;
      }
      else
      {
        /* Create the link and add it to the game */
        link = link_create(idLink);
        if (link != NULL)
        {
          link_set_name(link, name);
          link_set_origin(link, idSpace);
          link_set_destination(link, idFinal);
          link_set_direction(link, direction);
          link_set_open(link, open);
          if (game_add_link(game, link) == ERROR)
          {
            link_destroy(link);
          }
        }
      }
    }
  }

  /* Check read errors */
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);
  return status;
}

Status game_reader_set_player()
{
}

Status game_reader_set_character()
{
}

Status game_reader_set_link()
{
}

Status game_reader_set_space()
{
}

Status game_reader_set_object()
{
}
