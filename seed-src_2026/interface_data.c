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
    Command *last_cmd;             /*!< The last command */
    Status last_action_status;     /*!< Status of the last action */        
    char last_chat[WORD_SIZE + 1]; /*!< Stores the last chat message generated in the game */
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
    intdat->last_action_status = OK;
    intdat->last_cmd = NULL;
    intdat->last_chat[0] = '\0';
    return intdat;
}
Status interface_data_destroy(Interface_Data *intdat)
{
    if (intdat == NULL)
    {
        return ERROR;
    }
    if(intdat->last_cmd!=NULL){
        command_destroy(intdat->last_cmd);
    }
    free(intdat);
    return OK;
}

Status interface_data_set_last_cmd(Interface_Data *intdat, Command *code)
{
    if (intdat == NULL || code==NULL)
    {
        return ERROR;
    }

    if (intdat->last_cmd != NULL)
    {
        command_destroy(intdat->last_cmd);
    }

    intdat->last_cmd = command_create();
    if (intdat->last_cmd == NULL)
    {
        return ERROR;
    }

    command_set_code(intdat->last_cmd, command_get_code(code));
    command_set_arg(intdat->last_cmd, command_get_arg(code));

    return OK;
}

Command *interface_data_get_last_cmd(Interface_Data *intdat)
{
    if (intdat == NULL)
    {
        return NULL;
    }
    return intdat->last_cmd;
}

Status interface_data_set_last_action_status(Interface_Data *intdat, Status status)
{
    if (intdat == NULL || ((status != OK) && (status != ERROR)))
    {
        return ERROR;
    }
    intdat->last_action_status = status;
    return OK;
}

Status interface_data_get_last_action_status(Interface_Data *intdat)
{
    if (intdat == NULL)
    {
        return ERROR;
    }
    return intdat->last_action_status;
}

Status interface_data_set_last_chat(Interface_Data *intdat, const char *message)
{
    if (intdat == NULL || message == NULL)
    {
        return ERROR;
    }
    strncpy(intdat->last_chat, message, WORD_SIZE);
    intdat->last_chat[WORD_SIZE] = '\0';
    return OK;
}

char *interface_data_get_last_chat(Interface_Data *intdat)
{
    if (intdat == NULL)
    {
        return NULL;
    }
    return intdat->last_chat;
}
