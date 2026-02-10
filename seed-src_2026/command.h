/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG && Jian Feng Yin Chen
 * @version 0
 * @date 02-02-2026
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 7

typedef enum { CMDS, CMDL } CommandType;

typedef enum { NO_CMD = -1, UNKNOWN, EXIT, NEXT, BACK, TAKE, DROP} CommandCode;

typedef struct _Command Command;

/**
 * @brief It creates a new command, allocating memory and initializing with code NO_CMD.
 * @author Jian Feng Yin Chen
 * 
 * @return A pointer to the new command if everything goes well, or NULL if memory could not be reserved.
 */
Command* command_create();

/**
 * @brief It destroys a command, freeing the allocated memory.
 * @author Jian Feng Yin Chen
 * @param command Pointer to the command that must be destroyed.
 * @return OK if everything goes well, or ERROR if there was some mistake.
 */
Status command_destroy(Command* command);

/**
 * @brief Sets the code of a command.
 * @author Jian Feng Yin Chen
 *
 * @param command Pointer to the command to be modified.
 * @param code New value for the command code.
 * @return OK if everything goes well, or ERROR if the pointer is NULL.
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief Gets the code stored in a command.
 * @author Jian Feng Yin Chen
 *
 * @param command Pointer to the command from wich to obtain the code.
 * @return The command code stored in the structure, or NO_CMD if the pointer is NULL.
 */
CommandCode command_get_code(Command* command);

/**
 * @brief Reads user input and updates the command code accordingly.
 * @author Jian Feng Yin Chen
 * 
 * This function reads a line from stdin, parses the first word and compares it with the known commands to set the corresponding CommandCode.
 * @param command  Pointer to the command that will store the interpreted code.
 * @return OK if everything goes well, or ERROR if the pointer is NULL.
 */
Status command_get_user_input(Command* command);

#endif



