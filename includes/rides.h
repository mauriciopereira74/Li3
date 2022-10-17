#ifndef RIDES_H
#define RIDES_H

#include <time.h>
#include <stdbool.h>
#include "drivers.h"
#include "users.h"


/**
 * @brief Types of User elements.
 */
typedef struct
{
    long int id; /**< long int that represents the id number of a ride. */

    struct tm birth_date ; /**< struct that represents the ride's date. */

    Driver driver; /**< Driver of the ride. */

    User user ; /**< User of the ride. */

    char* city, /**< string that represents the city of the ride. */
          comment; /**< string that represents the comment that was given to the driver/ride. */

    float distance, /**< float that represents the distance of the ride. */
          tip; /**< float that represents the tip that was given to the driver. */

    int score_user, /**< int that represents the score of the user. */
        score_driver; /**< int that represents the score of the driver. */
 
} Ride;


#endif