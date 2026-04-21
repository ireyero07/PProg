/**
 * @brief It defines the object module interface
 *
 * @file object.h
 * @author Profesores PPROG && Ivan
 * @version 1
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#define MAX_DESC 200 /*!< Maximum length of an object description */

#include "types.h"

typedef struct _Object Object; /*!< Opaque type representing an object in the game */

/**
 * @brief It creates a new object, allocating memory and initializing its members
 * @author Ivan
 *
 * @param id the identification number for the new object
 * @return a new object, initialized
 */
Object* object_create(Id id);

/**
 * @brief It destroys an object, freeing the allocated memory
 * @author Ivan
 *
 * @param object a pointer to the object that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_destroy(Object* object);

/**
 * @brief It gets the id of an object
 * @author Ivan
 *
 * @param object a pointer to the object
 * @return the id of object
 */
Id object_get_id(Object* object);

/**
 * @brief It sets the name of an object
 * @author Ivan
 *
 * @param object a pointer to the object
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief It gets the name of an object
 * @author Ivan
 *
 * @param object a pointer to the object
 * @return  a string with the name of the object
 */
const char* object_get_name(Object* object);

/**
 * @brief It sets the description of an object
 * @author Ivan Mijangos
 *
 * @param object a pointer to the object
 * @param description a string with the description to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_description(Object* object, char* description);

/**
 * @brief It gets the description of an object
 * @author Ivan Mijangos
 *
 * @param object a pointer to the object
 * @return  a string with the description of the object
 */
const char* object_get_description(Object* object);
/**
* @brief It sets the health of an object
* @author Ivan Mijangos
*
* @param object a pointer to the object
* @param health an integer that says how much health it cures
* @return OK, if everything goes well or ERROR if there was some mistake
*/
Status object_set_health(Object* object, int health);

/**
* @brief It gets the health of an object
* @author Ivan Mijangos
*
* @param object a pointer to the object
* @return an integer that says how much health it cures
*/
int object_get_health(Object* object);

/**
* @brief It sets if an object is movable
* @author Ivan Mijangos
*
* @param object a pointer to the object
* @param movable bool that says if the object is movable or not
* @return OK, if everything goes well or ERROR if there was some mistake
*/
Status object_set_movable(Object* object, Bool movable);

/**
* @brief It gets if an object is movable
* @author Ivan Mijangos
*
* @param object a pointer to the object
* @return bool that says if the object is movable or not
*/
Bool object_get_movable(Object* object);

/**
* @brief It sets the dependency of an object
* @author Ivan Mijangos
*
* @param object a pointer to the object
* @param dependency the Id of the object that is needed to take this object
* @return OK, if everything goes well or ERROR if there was some mistake
*/
Status object_set_dependency(Object* object, Id dependency);

/**
* @brief It gets the dependency of an object
* @author Ivan Mijangos
*
* @param object a pointer to the object
* @return the Id of the object that is needed to take this object
*/
Id object_get_dependency(Object* object);

/**
* @brief It sets the Id that an object can open
* @author Ivan Mijangos
*
* @param object a pointer to the object
* @param open the Id of the object that this object can open
* @return OK, if everything goes well or ERROR if there was some mistake
*/
Status object_set_open(Object* object, Id open);

/**
* @brief It gets the Id that an object can open
* @author Ivan Mijangos
*
* @param object a pointer to the object
* @return the Id of the object that this object can open
*/
Id object_get_open(Object* object);

/**
 * @brief It prints the object information
 * @author Ivan
 *
 * This fucntion shows the id and name of the object.
 * @param object a pointer to the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_print(Object* object);


#endif