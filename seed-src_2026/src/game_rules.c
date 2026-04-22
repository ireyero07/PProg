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
Status game_rules_random_enemy_attack(Game *game);


/*Implementations*/

Bool game_rules_event_occurs(int percentage){
    if (percentage<0 || percentage>100){
        return FALSE;
    }
    int r=rand() % 100;

    if (r<percentage){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int game_rules_random_number_in_range_generator(int min, int max){
    int game_rules_random_number_in_range_generator(int min, int max);
}

Status game_rules_random_enemy_attack(Game *game){
    Player *player=NULL;
    Character *character=NULL;
    Id player_loc = NO_ID;
    int probability = 30;
    if(game == NULL){
        return ERROR;
    }

    player=game_get_player(game);

    if((player==NULL) || (player_get_location(player)==NO_ID)){
        return ERROR;
    }

   character = game_get_character_by_space(game, player_loc);
   if(character==NULL){
    return ERROR;
   }

   if(character_get_friendly(character) == FALSE){
    if(game_rules_event_occurs(probability)==TRUE){
        player_set_health(player, player_get_health(player) - game_rules_random_number_in_range_generator(1, 5));
    }/*HAY QUE VER LA VIDA QUE VAN A TENER LOS PLAYER PARA VER DE CUANTO PUEDE SER EL DAMAGE DE ESTE ATACK RANDOM*/
   }

    return OK;
}

/*########################################################################################
PUBLIC FUNCTIONS
########################################################################################*/
