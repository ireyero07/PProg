/**
 * @brief It implements the interface_data
 *
 * @file interface_data.c
 * @author Gonzalez Hijano Ivan
 * @version 0
 * @date 29-03-2026
 * @copyright GNU Public License
 */

#include "interface_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief IntData
 *
 * This struct stores all the information of a character.
 */
struct _Interface_Data
{
    Command *last_cmd;         /*!< The last command */
    Status last_action_status; /*!< Status of the last action */
    char last_chat[WORD_SIZE]; /*!< Stores the last chat message generated in the game */
};

/**
 * @brief It creates a new interface_data
 */
Interface_Data *interface_data_create()
{
    Interface_Data *intdat = NULL;

    intdat = (Interface_Data *)malloc(sizeof(Interface_Data));
    if (intdat == NULL)
    {
        return NULL;
    }

    return intdat;
}
Status interface_data_free(Interface_Data *intdata)
{
}

Status interface_data_set_last_cmd(Interface_Data *intdat, Command *cmd)
{
}
Command *interface_data_get_last_cmd(Interface_Data *intdat)
{
}
Status interface_data_set_last_action_status(Interface_Data *intdat, Status status)
{
}
Status interface_data_get_last_action_status(Interface_Data *intdat)
{
}
Status interface_data_set_last_chat(Interface_Data *intdat, char *message)
{
}
char *interface_data_get_last_chat(Interface_Data *intdat)
{
}
