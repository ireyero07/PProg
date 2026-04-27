/**
 * @brief It implements the game rules module
 *
 * @file game_rules.c
 * @author Gonzalez Hijano, Ivan
 * @version 0
 * @date 22-04-2026
 * @copyright GNU Public License
 */

#include "game_rules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*########################################################################################
PRIVATE FUNCTIONS
########################################################################################*/

/*Declarations*/

/**
 * @brief It determinates if an event occurs or not with a percentaje given
 * @author Gonzalez Hijano Ivan
 *
 * @param percentaje the percentaje that has the event to occur
 * @return TIf the event occurs (TRUE) or not (FALSE)
 */
Bool game_rules_event_occurs(int percentage);

/**
 * @brief It generates a random number between a range given
 * @author Gonzalez Hijano Ivan
 *
 * @param min The bottom of the range
 * @param max The top of the range
 * @return The number generated
 */
int game_rules_random_number_in_range_generator(int min, int max);

/**
 * @brief If the player is in tha same space as an enemy, the enemy can ramdomly attack the player
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param probability the probability of the rule to occur
 * @return OK if all goes well or ERROR otherside
 */
Status game_rules_random_enemy_attack(Game *game, int probability);

/**
 * @brief Makes a random following character to die
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param probability the probability of the rule to occur
 * @return OK if all goes well or ERROR otherside
 */
Status game_rules_random_ingredient_following_expires(Game *game, int probability);

/**
 * @brief Opens all the close links in a space where all the enemies located in it dies
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @return OK if all goes well or ERROR otherside
 */
Status game_rules_open_door_when_enemy_dies(Game *game);

/**
 * @brief Decreases the player an amount of health
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param probability the probability of the rule to occur
 * @return OK if all goes well or ERROR otherside
 */
Status game_rules_negative_review(Game *game, int probability);

/**
 * @brief Makes an object to change its space
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param probability the probability of the rule to occur
 * @return OK if all goes well or ERROR otherside
 */
Status game_rules_random_object_teleport(Game *game, int probability);

/**
 * @brief Decreases the player health if in the player backpack the number of object is = player backpack capacity
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param probability the probability of the rule to occur
 * @return OK if all goes well or ERROR otherside
 */
Status game_rules_heavy_backpack_damage(Game *game);

/*Implementations*/

Bool game_rules_event_occurs(int percentage)
{   
    int r;
    if (percentage < 0 || percentage > 100)
    {
        return FALSE;
    }
    r = rand() % 100;

    if (r < percentage)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int game_rules_random_number_in_range_generator(int min, int max)
{
    if (min > max)
    {
        return -1;
    }
    return min + rand() % (max - min + 1);
}

Status game_rules_random_enemy_attack(Game *game, int probability)
{
    Player *player = NULL;
    Id player_loc = NO_ID;
    int n_enemies = 0;
    int i;
    if (game == NULL || probability < 0)
    {
        return ERROR;
    }
    if (game_rules_event_occurs(probability) == TRUE)
    {
        player = game_get_player(game);
        if (player == NULL)
        {
            return ERROR;
        }
        player_loc = player_get_location(player);
        if (player_loc == NO_ID)
        {
            return ERROR;
        }
        if ((n_enemies = game_space_number_of_enemies(game, player_loc)) == -1)
        {
            return ERROR;
        }

        for (i = 0; i < n_enemies; i++)
        {
            player_set_health(player, player_get_health(player) - game_rules_random_number_in_range_generator(1, 20));
        }
        return OK;
    }

    return OK;
}

Status game_rules_random_ingredient_following_expires(Game *game, int probability)
{
    int n_followers = 0, counter = 0;
    int following_character_number, n_characters_in_space = 0, i = 0;
    Id *characters_in_space = NULL;
    Id player_id = NO_ID;
    Set *set_of_characters = NULL;
    Player *player = NULL;
    if (game == NULL || probability < 0)
    {
        return ERROR;
    }
    player = game_get_player(game);
    n_followers = game_get_number_of_followers(game, player);
    if (n_followers == 0)
    {
        return OK;
    }

    if (n_followers == -1)
    {
        return ERROR;
    }

    if (game_rules_event_occurs(probability) == TRUE)
    {
        following_character_number = game_rules_random_number_in_range_generator(1, n_followers);
        if (following_character_number == -1)
        {
            return ERROR;
        }
        set_of_characters = game_get_characters_by_space(game, game_get_player_location(game));
        if (set_of_characters == NULL)
        {
            return ERROR;
        }
        characters_in_space = set_get_list_ids(set_of_characters);
        n_characters_in_space = set_get_n_ids(set_of_characters);
        player_id = player_get_id(player);

        for (i = 0; i < n_characters_in_space; i++)
        {
            if (character_get_following(game_get_character_by_id(game, characters_in_space[i])) == player_id)
            {
                counter++;
                if (counter == following_character_number)
                {
                    character_set_health(game_get_character_by_id(game, characters_in_space[i]), 0);
                    return OK;
                }
            }
        }
    }

    return OK;
}

Status game_rules_open_door_when_enemy_dies(Game *game)
{
    Set *characters_in_space = NULL;
    int i, j, n_enemies = 0, n_characters = 0;
    Id player_loc = NO_ID;
    Id *list_char_ids = NULL;
    Bool are_enemies_alive = FALSE;
    if (game == NULL)
    {
        return ERROR;
    }
    player_loc = game_get_player_location(game);
    if (player_loc == NO_ID)
    {
        return ERROR;
    }

    if ((n_enemies = (game_space_number_of_enemies(game, game_get_player_location(game)))) > 0)
    {
        if ((characters_in_space = game_get_characters_by_space(game, player_loc)) == NULL)
        {
            return ERROR;
        }
        n_characters = set_get_n_ids(characters_in_space);
        list_char_ids = set_get_list_ids(characters_in_space);
        if (list_char_ids == NULL)
        {
            return ERROR;
        }
        i = 0;
        while (n_enemies != 0 && i < n_characters)
        {
            if (character_get_friendly(game_get_character_by_id(game, list_char_ids[i])) == FALSE)
            {
                n_enemies--;
                if (character_get_health(game_get_character_by_id(game, list_char_ids[i])) > 0)
                {
                    are_enemies_alive = TRUE;
                }
                if (are_enemies_alive == TRUE)
                {
                    return OK;
                }
            }

            i++;
        }
        if (are_enemies_alive == FALSE)
        {
            for (j = 0; j < 6; j++)
            {
                if (game_connection_is_open(game, player_loc, j) == FALSE)
                {
                    link_set_open(game_get_link(game, player_loc, game_get_link_destination(game, player_loc, j)), TRUE);
                }
            }
        }
    }
    return OK;
}

Status game_rules_negative_review(Game *game, int probability)
{
    Player *player = NULL;

    if (game == NULL || probability < 0)
    {
        return ERROR;
    }

    if (game_rules_event_occurs(probability) == TRUE)
    {
        player = game_get_player(game);
        if (player == NULL)
        {
            return ERROR;
        }
        if (player_set_health(player, player_get_health(player) - game_rules_random_number_in_range_generator(10, 40)) == ERROR)
        {
            return ERROR;
        }
        return OK;
    }
    return OK;
}

Status game_rules_random_object_teleport(Game *game, int probability)
{
    Player *player = NULL;
    Space *player_loc = NULL;
    Space *obj_destination = NULL;
    Id player_loc_id = NO_ID;
    Id *obj_ids = NULL;
    Object *object;
    long n_objects = 0;
    int aux = 0, aux_obj_pos = 0, aux_space_pos = 0, i = 0;

    if (game == NULL || probability < 0)
    {
        return ERROR;
    }

    if (game_rules_event_occurs(probability) == TRUE)
    {
        player = game_get_player(game);
        if (player == NULL)
        {
            return ERROR;
        }
        player_loc_id = player_get_location(player);
        player_loc = game_get_space(game, player_loc_id);
        if (player_loc == NULL)
        {
            return ERROR;
        }
        if ((n_objects = space_get_number_objects(player_loc)) > 0)
        {
            obj_ids = space_get_objects_ids(player_loc);
            if (obj_ids == NULL)
            {
                return ERROR;
            }
            while (aux == 0 && i < n_objects)
            {
                object = game_get_object(game, obj_ids[aux_obj_pos = game_rules_random_number_in_range_generator(0, n_objects - 1)]);
                if (object == NULL)
                {
                    return ERROR;
                }
                if ((object_get_movable(object) == TRUE) && object_get_open(object) == NO_ID)
                {
                    aux = 1;
                }
                i++;
            }
            if (aux == 0)
            {
                return OK;
            }
            aux = 0;
            i = 0;
            while (aux == 0 && i < game_get_n_spaces(game))
            {
                obj_destination = game_get_space_at(game, aux_space_pos = game_rules_random_number_in_range_generator(0, game_get_n_spaces(game) - 1));
                if (obj_destination == NULL)
                {
                    return ERROR;
                }
                if ((space_get_number_objects(obj_destination) < MAX_OBJECTS_SPACE) && (player_loc != obj_destination))
                {
                    aux = 1;
                }
                i++;
            }
            if (aux == 0)
            {
                return OK;
            }
            game_set_object_location(game, obj_ids[aux_obj_pos], space_get_id(obj_destination));
            return OK;
        }
    }
    return OK;
}

Status game_rules_heavy_backpack_damage(Game *game)
{
    Player *player = NULL;
    Inventory *backpack = NULL;
    int backpack_capacity, n_objects;

    if (game == NULL)
    {
        return ERROR;
    }

    player = game_get_player(game);

    if (player == NULL)
    {
        return ERROR;
    }

    backpack = player_get_backpack(player);
    if (backpack == NULL)
    {
        return ERROR;
    }

    if ((backpack_capacity = inventory_get_max_objs(backpack)) == -1)
    {
        return ERROR;
    }
    if ((n_objects = inventory_get_number_objects(backpack)) == -1)
    {
        return ERROR;
    }

    if (backpack_capacity == n_objects)
    {
        player_set_health(player, player_get_health(player) - game_rules_random_number_in_range_generator(1, 5));
    }

    return OK;
}

/*########################################################################################
PUBLIC FUNCTIONS
########################################################################################*/

Status game_rules_run_rules(Game *game)
{
    int probability_random_enemy_attack = 30;
    int probability_random_ingredient_following_expires = 10;
    int probability_negative_review = 5;
    int probability_random_object_teleport = 15;

    if (game == NULL)
    {
        return ERROR;
    }

    if (game_rules_random_enemy_attack(game, probability_random_enemy_attack) == ERROR)
    {
        return ERROR;
    }

    if (game_rules_random_ingredient_following_expires(game, probability_random_ingredient_following_expires) == ERROR)
    {
        return ERROR;
    }

    if (game_rules_open_door_when_enemy_dies(game) == ERROR)
    {
        return ERROR;
    }

    if (game_rules_negative_review(game, probability_negative_review) == ERROR)
    {
        return ERROR;
    }

    if (game_rules_random_object_teleport(game, probability_random_object_teleport) == ERROR)
    {
        return ERROR;
    }

    if (game_rules_heavy_backpack_damage(game) == ERROR)
    {
        return ERROR;
    }

    return OK;
}