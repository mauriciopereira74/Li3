#ifndef RIDES_H
#define RIDES_H

#include <time.h>
#include <stdbool.h>
#include "drivers.h" // not needed i think
#include "users.h" // not needed i think


/**
 * @brief Types of User elements.
 */
typedef struct ride
{
    
    char *id,        /**< string that represents the id number of a ride. */
         *driver_id; /**< Driver of the ride. */

    struct tm date;     /**< struct that represents the ride's date. */

    char *city,          /**< string that represents the city of the ride. */
      *comment,          /**< string that represents the comment that was given to the driver/ride. */
      *user_username;        /**< User of the ride. */
    double tip;           /**< float that represents the tip that was given to the driver. */

    int score_user,      /**< int that represents the score of the user. */
        distance,      /**< float that represents the distance of the ride. */
        score_driver;    /**< int that represents the score of the driver. */
 
} *Ride;


#endif