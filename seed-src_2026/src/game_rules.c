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
Bool game_rules_event_occurs(int percentage);
int game_rules_random_number_in_range_generator(int min, int max);
Status game_rules_random_enemy_attack(Game *game, int probability);
Status game_rules_random_ingredient_following_expires(Game *game, int probability);

/*Implementations*/

Bool game_rules_event_occurs(int percentage)
{
    if (percentage < 0 || percentage > 100)
    {
        return FALSE;
    }
    int r = rand() % 100;

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
    int game_rules_random_number_in_range_generator(int min, int max);
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

        if ((player == NULL) || (player_loc = player_get_location(player)) == NO_ID)
        {
            return ERROR;
        }
        if ((n_enemies = game_space_number_of_enemies(game, player_loc) == -1))
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
    int n_followers = 0, counter=0;
    int following_character_number, n_characters_in_space=0, i = 0;
    Id *characters_in_space=NULL;
    Id player_id=NO_ID;
    Set *set_of_characters=NULL;
    Player *player=NULL;
    if (game == NULL || probability < 0)
    {
        return ERROR;
    }
    player=game_get_player(game);
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
        set_of_characters=game_get_characters_by_space(game, game_get_player_location(game));
        if(set_of_characters==NULL){
            return ERROR;
        }
        characters_in_space=set_get_list_ids(set_of_characters);
        n_characters_in_space=set_get_n_ids(set_of_characters);
        player_id=player_get_id(player);
        
        for (i = 0; i < n_characters_in_space; i++)
        {
            if (character_get_following(game_get_character_by_id(game, characters_in_space[i])) == player_id)
            {
                counter++;
                if(counter==following_character_number){
                    character_set_health(game_get_character_by_id(game, characters_in_space[i]), 0);
                    return OK;
                }
            }
        }
    }

    return OK;
}

/*########################################################################################
PUBLIC FUNCTIONS
########################################################################################*/
