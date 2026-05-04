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
 * @return -1 in case of ERROR or the number of damage the player receives
 */
int game_rules_random_enemy_attack(Game *game, int probability);

/**
 * @brief Makes a random following character to die
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param probability the probability of the rule to occur
 * @return NULL in case of ERROR or if the action dont occur or the name of the character that expires
 */
Character *game_rules_random_ingredient_following_expires(Game *game, int probability);

/**
 * @brief Opens all the close links in a space where the boss dies
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @return OK if all goes well or ERROR otherside
 */
Status game_rules_open_doors_when_boss_dies(Game *game);

/**
 * @brief Decreases the player an amount of health
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param probability the probability of the rule to occur
 * @return -1 in case of ERROR or the number of damage the player receives
 */
int game_rules_negative_review(Game *game, int probability);

/**
 * @brief Makes an object to change its space
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @param probability the probability of the rule to occur
 * @return -1 in case of ERROR, 0 in case all OK but no object teleport and 1 if all OK but an object teleport
 */
int game_rules_random_object_teleport(Game *game, int probability);

/**
 * @brief Decreases the player health if in the player backpack the number of object is = player backpack capacity
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @return -1 in case of ERROR or the number of damage the player receives
 */
int game_rules_heavy_backpack_damage(Game *game);

/**
 * @brief Close all the space links when the player enters in a space with a not death boss
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @return OK if all goes well or ERROR otherside
 */
Status game_rules_close_doors_when_boss(Game *game);

/**
 * @brief In the final boss fight the player and the character gets some constant damage each round
 * @author Gonzalez Hijano Ivan
 *
 * @param game a pointer to the game structure
 * @return -1 in case of ERROR, 0 in case all OK and 1 in case all OK and the action occurs
 */
int game_rules_final_boss_fire(Game *game, int damage_players, int damage_followers, Id final_boss_pos);

/**
 * @brief If one player start a fight wtih a boss all the rest players get teleported to that space
 * @author Gonzalez Hijano, Ivan
 *
 * @param game a pointer to the game structure
 * @return -1 in case of ERROR, 0 in case all OK and 1 in case all OK and the action occurs
 */
int game_rules_if_player_fight_boss_tp_all_players(Game *game);

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

int game_rules_random_enemy_attack(Game *game, int probability)
{
    Player *player = NULL;
    Id player_loc = NO_ID;
    int t_damage = 0;
    int n_enemies = 0;
    if (game == NULL || probability < 0)
    {
        return -1;
    }
    if (game_rules_event_occurs(probability) == TRUE)
    {
        player = game_get_player(game);
        if (player == NULL)
        {
            return -1;
        }
        player_loc = player_get_location(player);
        if (player_loc == NO_ID)
        {
            return -1;
        }
        n_enemies = game_space_number_of_enemies(game, player_loc);
        if (n_enemies == -1)
        {
            return -1;
        }

        if (n_enemies == 0)
        {
            return 0;
        }

        player_set_health(player, player_get_health(player) - (t_damage = game_rules_random_number_in_range_generator(1, 15)));

        return t_damage;
    }

    return t_damage;
}

Character *game_rules_random_ingredient_following_expires(Game *game, int probability)
{
    int n_followers = 0, counter = 0;
    int following_character_number, n_characters_in_space = 0, i = 0;
    Id *characters_in_space = NULL;
    Id player_id = NO_ID;
    Set *set_of_characters = NULL;
    Player *player = NULL;
    Character *ch = NULL;
    if (game == NULL || probability < 0)
    {
        return NULL;
    }
    player = game_get_player(game);
    n_followers = game_get_number_of_followers(game, player);
    if (n_followers <= 0)
    {
        return NULL;
    }

    if (game_rules_event_occurs(probability) == TRUE)
    {
        following_character_number = game_rules_random_number_in_range_generator(1, n_followers);
        if (following_character_number == -1)
        {
            return NULL;
        }
        set_of_characters = game_get_characters_by_space(game, game_get_player_location(game));
        if (set_of_characters == NULL)
        {
            return NULL;
        }
        characters_in_space = set_get_list_ids(set_of_characters);
        n_characters_in_space = set_get_n_ids(set_of_characters);
        player_id = player_get_id(player);

        for (i = 0; i < n_characters_in_space; i++)
        {
            ch = game_get_character_by_id(game, characters_in_space[i]);
            if (character_get_following(ch) == player_id)
            {
                counter++;
                if (counter == following_character_number)
                {
                    character_set_health(ch, 0);
                    return ch;
                }
            }
        }
    }

    return NULL;
}

Status game_rules_open_doors_when_boss_dies(Game *game)
{
    Character *ch = NULL;
    Id player_loc = NO_ID, destination = NO_ID;
    Id *char_ids = NULL;
    Link *link = NULL;
    Set *character_set = NULL;
    int i = 0, n_characters = 0;
    Bool boss_dead = FALSE;

    if (game == NULL)
    {
        return ERROR;
    }
    player_loc = game_get_player_location(game);
    if (player_loc == NO_ID)
    {
        return ERROR;
    }

    character_set = space_get_character(game_get_space(game, player_loc));
    char_ids = set_get_list_ids(character_set);
    n_characters = set_get_n_ids(character_set);
    for (i = 0; i < n_characters; i++)
    {
        ch = game_get_character(game, char_ids[i]);
        if (ch != NULL && character_get_boss(ch) == TRUE && character_get_health(ch) <= 0)
        {
            boss_dead = TRUE;
            break;
        }
    }

    if (!boss_dead)
    {
        return OK;
    }

    for (i = 0; i < N_DIRECTIONS; i++)
    {
        destination = game_get_link_destination(game, player_loc, i);
        link = game_get_link(game, player_loc, destination);
        if (link == NULL)
        {
            continue;
        }
        if (link_set_open(link, TRUE) == ERROR)
        {
            return ERROR;
        }
    }

    return OK;
}

int game_rules_negative_review(Game *game, int probability)
{
    Player *player = NULL;
    int t_damage = 0;

    if (game == NULL || probability < 0)
    {
        return -1;
    }

    if (game_rules_event_occurs(probability) == TRUE)
    {
        player = game_get_player(game);
        if (player == NULL)
        {
            return -1;
        }
        if (player_set_health(player, player_get_health(player) - (t_damage = game_rules_random_number_in_range_generator(5, 25))) == ERROR)
        {
            return -1;
        }
    }
    return t_damage;
}

int game_rules_random_object_teleport(Game *game, int probability)
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
        return -1;
    }

    if (game_rules_event_occurs(probability) == TRUE)
    {
        player = game_get_player(game);
        if (player == NULL)
        {
            return -1;
        }
        player_loc_id = player_get_location(player);
        player_loc = game_get_space(game, player_loc_id);
        if (player_loc == NULL)
        {
            return -1;
        }
        if ((n_objects = space_get_number_objects(player_loc)) > 0)
        {
            obj_ids = space_get_objects_ids(player_loc);
            if (obj_ids == NULL)
            {
                return -1;
            }
            while (aux == 0 && i < n_objects)
            {
                object = game_get_object(game, obj_ids[aux_obj_pos = game_rules_random_number_in_range_generator(0, n_objects - 1)]);
                if (object == NULL)
                {
                    return -1;
                }
                if ((object_get_movable(object) == TRUE) && object_get_open(object) == NO_ID)
                {
                    aux = 1;
                }
                i++;
            }
            if (aux == 0)
            {
                return 0;
            }
            aux = 0;
            i = 0;
            while (aux == 0 && i < game_get_n_spaces(game))
            {
                obj_destination = game_get_space_at(game, aux_space_pos = game_rules_random_number_in_range_generator(0, game_get_n_spaces(game) - 1));
                if (obj_destination == NULL)
                {
                    return -1;
                }
                if ((space_get_number_objects(obj_destination) < MAX_OBJECTS_SPACE) && (player_loc != obj_destination))
                {
                    aux = 1;
                }
                i++;
            }
            if (aux == 0)
            {
                return 0;
            }
            game_set_object_location(game, obj_ids[aux_obj_pos], space_get_id(obj_destination));
            return 1;
        }
    }
    return 0;
}

int game_rules_heavy_backpack_damage(Game *game)
{
    Player *player = NULL;
    Inventory *backpack = NULL;
    int backpack_capacity, n_objects, t_damage = 0;

    if (game == NULL)
    {
        return -1;
    }

    player = game_get_player(game);

    if (player == NULL)
    {
        return -1;
    }

    backpack = player_get_backpack(player);
    if (backpack == NULL)
    {
        return -1;
    }

    if ((backpack_capacity = inventory_get_max_objs(backpack)) == -1)
    {
        return -1;
    }
    if ((n_objects = inventory_get_number_objects(backpack)) == -1)
    {
        return -1;
    }

    if (n_objects >= backpack_capacity)
    {
        player_set_health(player, player_get_health(player) - (t_damage = game_rules_random_number_in_range_generator(1, 5)));
    }

    return t_damage;
}

Status game_rules_close_doors_when_boss(Game *game)
{

    Character *boss = NULL;
    Id player_loc = NO_ID, destination = NO_ID;
    Link *link = NULL;
    int i = 0;

    if (game == NULL)
    {
        return ERROR;
    }
    player_loc = game_get_player_location(game);
    if (player_loc == NO_ID)
    {
        return ERROR;
    }
    boss = game_space_with_boss(game, game_get_space(game, player_loc));
    if (boss == NULL)
    {
        return OK;
    }
    if (character_get_health(boss) > 0)
    {
        for (i = 0; i < N_DIRECTIONS; i++)
        {
            destination = game_get_link_destination(game, player_loc, i);
            link = game_get_link(game, player_loc, destination);
            if (link == NULL)
            {
                continue;
            }
            if (link_get_open(link) == FALSE)
            {
                continue;
            }
            else
            {
                if (link_set_open(link, FALSE) == ERROR)
                {
                    return ERROR;
                }
            }
        }
    }

    return OK;
}

int game_rules_final_boss_fire(Game *game, int damage_players, int damage_followers, Id final_boss_pos)
{
    Player *player = NULL;
    Id player_id = NO_ID, player_loc = NO_ID;
    int i, n_followers = 0;
    Character *follower = NULL;
    if (game == NULL || damage_followers < 0 || damage_players < 0 || final_boss_pos == NO_ID)
    {
        return -1;
    }

    player = game_get_player(game);
    if (player == NULL)
    {
        return -1;
    }

    player_loc = player_get_location(player);
    if (player_loc == NO_ID)
    {
        return -1;
    }

    player_id = player_get_id(player);
    if (player_id == NO_ID)
    {
        return -1;
    }

    if (final_boss_pos == player_loc)
    {
        n_followers = game_count_followers(game, player_id);
        for (i = 0; i < n_followers; i++)
        {
            follower = game_get_nth_follower(game, player_id, i);
            if (character_set_health(follower, character_get_health(follower) - damage_followers) == ERROR)
            {
                return -1;
            }
        }

        if (player_set_health(player, player_get_health(player) - damage_players) == ERROR)
        {
            return -1;
        }
        return 1;
    }
    return 0;
}

int game_rules_if_player_fight_boss_tp_all_players(Game *game)
{
    Player *act_player = NULL;
    Player *aux_player = NULL;
    Id player_pos = NO_ID;
    Id list_p_ids[MAX_PLAYERS];
    int i, n_players = 0, teleported = 0;
    if (game == NULL)
    {
        return -1;
    }
    act_player = game_get_player(game);
    if (act_player == NULL)
    {
        return -1;
    }
    player_pos = player_get_location(act_player);
    if (game_space_with_boss(game, game_get_space(game, player_pos)) != NULL)
    {
        n_players = game_get_n_players(game);
        if (n_players != game_get_list_of_player_ids(game, list_p_ids, MAX_PLAYERS))
        {
            return -1;
        }
        for (i = 0; i < n_players; i++)
        {
            aux_player = game_get_player_from_id(game, list_p_ids[i]);
            if (aux_player == NULL)
            {
                return -1;
            }
            if (player_get_location(aux_player) != player_pos)
            {
                if (player_set_location(aux_player, player_pos) == ERROR)
                {
                    return -1;
                }
                teleported++;
            }
        }

        return teleported > 0 ? 1 : 0;
    }
    return 0;
}

/*########################################################################################
PUBLIC FUNCTIONS
########################################################################################*/

Status game_rules_run_rules(Game *game)
{
    int r1, probability_random_enemy_attack = 10;
    Character *char_r2 = NULL;
    int probability_random_ingredient_following_expires = 5;
    int r3, probability_negative_review = 5;
    int r4, probability_random_object_teleport = 10;
    int r5;
    int r6;
    int fire_damage_to_player = 7;
    int fire_damage_to_followers = 4;
    Id final_boss_pos = 515;
    int r7;
    char narrator[WORD_SIZE];
    char tmp[256];

    if (game == NULL)
    {
        return ERROR;
    }

    narrator[0] = '\0';

    r1 = game_rules_random_enemy_attack(game, probability_random_enemy_attack);
    if (r1 == -1)
    {
        return ERROR;
    }
    if (r1 > 0)
    {
        Set *enemies_set = NULL;
        Id *enemies_ids = NULL;
        int n_chars_r1 = 0, j = 0;
        Character *ch_r1 = NULL;

        enemies_set = game_get_characters_by_space(game, game_get_player_location(game));
        if (enemies_set != NULL)
        {
            enemies_ids = set_get_list_ids(enemies_set);
            n_chars_r1 = set_get_n_ids(enemies_set);
            for (j = 0; j < n_chars_r1; j++)
            {
                ch_r1 = game_get_character_by_id(game, enemies_ids[j]);
                if (ch_r1 && character_get_friendly(ch_r1) == FALSE && character_get_health(ch_r1) > 0)
                {
                    sprintf(tmp, "[!] %s attacks %s: -%d HP. ",
                            character_get_name(ch_r1),
                            player_get_name(game_get_player(game)),
                            r1);
                    strncat(narrator, tmp, WORD_SIZE - strlen(narrator) - 1);
                }
            }
        }
    }

    char_r2 = game_rules_random_ingredient_following_expires(game, probability_random_ingredient_following_expires);
    if (char_r2 != NULL)
    {
        sprintf(tmp, "[!] %s is dead and he/she's not following you anymore. ", character_get_name(char_r2));
        strncat(narrator, tmp, WORD_SIZE - strlen(narrator) - 1);
    }

    if (game_rules_open_doors_when_boss_dies(game) == ERROR)
    {
        return ERROR;
    }

    r3 = game_rules_negative_review(game, probability_negative_review);
    if (r3 == -1)
    {
        return ERROR;
    }
    if (r3 > 0)
    {
        sprintf(tmp, "[!] Bad review: you lose %d HP. ", r3);
        strncat(narrator, tmp, WORD_SIZE - strlen(narrator) - 1);
    }

    r4 = game_rules_random_object_teleport(game, probability_random_object_teleport);
    if (r4 == -1)
    {
        return ERROR;
    }
    if (r4 == 1)
    {
        strncat(narrator, "[!] An object has mysteriously disappeared from the room. ", WORD_SIZE - strlen(narrator) - 1);
    }

    r5 = game_rules_heavy_backpack_damage(game);
    if (r5 == -1)
    {
        return ERROR;
    }
    if (r5 > 0)
    {
        sprintf(tmp, "[!] Full backpack: cervical damage %d HP. ", r5);
        strncat(narrator, tmp, WORD_SIZE - strlen(narrator) - 1);
    }

    if (game_rules_close_doors_when_boss(game) == ERROR)
    {
        return ERROR;
    }

    r6 = game_rules_final_boss_fire(game, fire_damage_to_player, fire_damage_to_followers, final_boss_pos);
    if (r6 == -1)
    {
        return ERROR;
    }
    if (r6 == 1)
    {
        Player *player_r6 = NULL;
        Id player_id_r6 = NO_ID;
        int n_fol_r6 = 0, j = 0;
        Character *fol_r6 = NULL;

        strncat(narrator, "[!] Final boss fire: damage to you", WORD_SIZE - strlen(narrator) - 1);

        player_r6 = game_get_player(game);
        if (player_r6 != NULL)
        {
            player_id_r6 = player_get_id(player_r6);
            n_fol_r6 = game_count_followers(game, player_id_r6);
            for (j = 0; j < n_fol_r6; j++)
            {
                fol_r6 = game_get_nth_follower(game, player_id_r6, j);
                if (fol_r6 != NULL)
                {
                    sprintf(tmp, " y %s", character_get_name(fol_r6));
                    strncat(narrator, tmp, WORD_SIZE - strlen(narrator) - 1);
                }
            }
        }
        strncat(narrator, ". ", WORD_SIZE - strlen(narrator) - 1);
    }

    r7 = game_rules_if_player_fight_boss_tp_all_players(game);
    if (r7 == -1)
    {
        return ERROR;
    }
    if (r7 == 1)
    {
        strncat(narrator, "[!] All players are teleported to your position.", WORD_SIZE - strlen(narrator) - 1);
    }

    if (command_get_code(game_get_last_command(game)) != ATTACK)
    {
        game_set_narrator_msg(game, narrator);
    }

    return OK;
}
