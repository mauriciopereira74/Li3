#ifndef DRIVERS_H
#define DRIVERS_H

#include <time.h>
#include <stdbool.h>

/**
 * @brief Types of Car Classes.
 */

enum Class { Basic,
             Green,
             Premium };

/**
 * @brief Types of Driver elements.
 */
typedef struct
{
    long int id, /**< long int that represents the id number of a driver. */
             license_plate; /**< long int that represents the license plate number of the driver. */


    char* name, /**< string that represents the name of the driver. */
          city, /**< string that represents the city of the driver. */
          account_status; /**< string to check the driver account status. */

    struct tm birth_date ; /**< struct that represents the driver's date of birth. */

    char gender; /**< char that represents the gender of the driver. */

    char* Class; /**< string that represents the car classe. */

    struct tm created_time; /**< struct that represents the datetime on which the driver account was created. */
    
} Driver;


#endif