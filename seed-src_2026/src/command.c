/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG
 * @version 0
 * @date 24-01-2026
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGHT 30 /*!< Maximum length of a command string read from input */

/** @brief Table mapping command codes to their short and long string representations */
char *cmd_to_str[N_CMD][N_CMDT] = {
  {"", "No command"}, 
  {"", "Unknown"}, 
  {"e", "Exit"}, 
  {"t", "Take"},
  {"d", "Drop"},
  {"a", "Attack"},
  {"c", "Chat"},
  {"m", "Move"},
  {"i", "Inspect"},
  {"r", "Recruit"},
  {"ab", "Abandon"},
  {"u", "Use"},
  {"o", "Open"}

  }; 

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
struct _Command {
  CommandCode code; /*!< Name of the command */
  char arg[WORD_SIZE + 1]; /*!< Name of the object in case of take */
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Command* command_create() {
  Command* newCommand = NULL;

  newCommand = (Command*)calloc(1,sizeof(Command));
  if (newCommand == NULL) {
    return NULL;
  }

  /* Initialization of an empty command*/
  newCommand->code = NO_CMD;
  newCommand->arg[0] ='\0';

  return newCommand;
}

Status command_destroy(Command* command) {
  if (!command) {
    return ERROR;
  }

  free(command);
  command = NULL;
  return OK;
}

Status command_set_code(Command* command, CommandCode code) {
  if (!command) {
    return ERROR;
  }

  command->code=code;

  return OK;
}

CommandCode command_get_code(Command* command) {
  if (!command) {
    return NO_CMD;
  }
  return command->code;
}

Status command_get_user_input(Command* command) {
  char input[CMD_LENGHT] = "", *token = NULL;
  int i = UNKNOWN - NO_CMD + 1,len;
  CommandCode cmd;

  if (!command) {
    return ERROR;
  }

  command->arg[0] = '\0';

  if (fgets(input, CMD_LENGHT, stdin)) {
    token = strtok(input, " \n");
    if (!token) {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD) {
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
        cmd = i + NO_CMD;
        if (cmd == TAKE||cmd == DROP||cmd == INSPECT||cmd == MOVE||cmd == RECRUIT||cmd == ABANDON||cmd == CHAT||cmd == ATTACK) {
          token = strtok(NULL, "\n"); 
          if (token != NULL) {
            while (*token == ' ') token++;
            strncpy(command->arg, token, WORD_SIZE);
            command->arg[WORD_SIZE] = '\0';
            len = strlen(command->arg);
            while (len > 0 && (command->arg[len-1] == ' ' || command->arg[len-1] == '\n')) {
              command->arg[--len] = '\0';
            }
          }
        }
        if (cmd == USE||cmd == OPEN) {
          token = strtok(NULL, "\n"); 
          if (token != NULL) {
            while (*token == ' ') token++;
            strncpy(command->arg, token, WORD_SIZE);
            command->arg[WORD_SIZE] = '\0';
            len = strlen(command->arg);
            while (len > 0 && (command->arg[len-1] == ' ' || command->arg[len-1] == '\n')) {
              command->arg[--len] = '\0';
            }
          }
        }

      } else {
        i++;
      }
    }
    return command_set_code(command, cmd);
  }
  else
    return command_set_code(command, EXIT);
  
}

const char* command_get_arg(Command *command){
  if (!command) return NULL;
  return command->arg;
}

Status command_set_arg(Command *command,const char *arg){
  if(!command||!arg) return ERROR;
  strncpy(command->arg,arg,WORD_SIZE);
  command->arg[WORD_SIZE] = '\0';
  return OK;
}

const char* command_get_name(Command *command) {
  if (!command) return NULL;

  return cmd_to_str[command->code - NO_CMD][CMDL];
}