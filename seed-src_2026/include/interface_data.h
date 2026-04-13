/**
 * @brief interface_data management module
 *
 * @file interface_data.h
 * @author Gonzalez Hijano, Ivan
 * @version 0
 * @date 29-03-2026
 * @copyright GNU Public License
 */

#ifndef INTERFACE_DATA_H
#define INTERFACE_DATA_H
#include "command.h"
#include "types.h"

typedef struct _Interface_Data Interface_Data; /*!< Opaque type representing the interface data for a player */

/**
 * @brief Creates a new Interface_Data structure.
 * @author Gonzalez Hijano, Ivan
 *
 * Allocates memory for a new Interface_Data structure and initializes it.
 * @return Pointer to the newly created Interface_Data structure, or NULL if memory allocation fails.
 */
Interface_Data *interface_data_create();

/**
 * @brief Frees the memory allocated for an Interface_Data structure.
 * @author Gonzalez Hijano, Ivan
 *
 * Deallocates all memory associated with the given Interface_Data structure.
 * @param intdat Pointer to the Interface_Data structure to free.
 * @return OK if the operation was successful, or ERROR if the pointer is NULL.
 */
Status interface_data_destroy(Interface_Data *intdat);

/**
 * @brief Sets the last command executed.
 * @author Gonzalez Hijano, Ivan
 *
 * Stores a pointer to the last Command executed in the Interface_Data structure.
 * @param intdat Pointer to the Interface_Data structure.
 * @param code The code of the command
 * @return OK if the operation was successful, or ERROR if any pointer is NULL.
 */
Status interface_data_set_last_cmd(Interface_Data *intdat, Command *code);

/**
 * @brief Gets the last command executed.
 * @author Gonzalez Hijano, Ivan
 *
 * Retrieves a pointer to the last Command stored in the Interface_Data structure.
 * @param intdat Pointer to the Interface_Data structure.
 * @return Pointer to the last Command structure, or NULL if intdat is NULL or no command has been set.
 */
Command *interface_data_get_last_cmd(Interface_Data *intdat);

/**
 * @brief Sets the status of the last action performed.
 * @author Gonzalez Hijano, Ivan
 *
 * Stores the status of the last game action in the Interface_Data structure.
 * @param intdat Pointer to the Interface_Data structure.
 * @param status The Status value to store.
 * @return Pointer to the Interface_Data structure if successful, or NULL if intdat is NULL.
 */
Status interface_data_set_last_action_status(Interface_Data *intdat, Status status);

/**
 * @brief Gets the status of the last action performed.
 * @author Gonzalez Hijano, Ivan
 *
 * Retrieves the status of the last game action stored in the Interface_Data structure.
 * @param intdat Pointer to the Interface_Data structure.
 * @return The Status value of the last action, or ERROR if intdat is NULL.
 */
Status interface_data_get_last_action_status(Interface_Data *intdat);

/**
 * @brief Sets the last chat message received.
 * @author Gonzalez Hijano, Ivan
 *
 * Stores a chat message string in the Interface_Data structure.
 * @param intdat Pointer to the Interface_Data structure.
 * @param message Pointer to the message string to store.
 * @return OK if the operation was successful, or ERROR if any pointer is NULL.
 */
Status interface_data_set_last_chat(Interface_Data *intdat, const char *message);

/**
 * @brief Gets the last chat message received.
 * @author Gonzalez Hijano, Ivan
 *
 * Retrieves the last chat message string stored in the Interface_Data structure.
 * @param intdat Pointer to the Interface_Data structure.
 * @return Pointer to the message string if available, or NULL if intdat is NULL or no message has been set.
 */
char *interface_data_get_last_chat(Interface_Data *intdat);

/**
 * @brief Sets the last object description.
 * @author Gonzalez Hijano, Ivan
 *
 * Stores an object description string in the Interface_Data structure.
 * @param intdat Pointer to the Interface_Data structure.
 * @param desc Pointer to the description string to store.
 * @return OK if the operation was successful, or ERROR if any pointer is NULL.
 */
Status interface_data_set_last_desc(Interface_Data *intdat, const char *desc);

/**
 * @brief Gets the last object description.
 * @author Gonzalez Hijano, Ivan
 *
 * Retrieves the last object description string stored in the Interface_Data structure.
 * @param intdat Pointer to the Interface_Data structure.
 * @return Pointer to the message string if available, or NULL if intdat is NULL or no message has been set.
 */
char *interface_data_get_last_desc(Interface_Data *intdat);

#endif