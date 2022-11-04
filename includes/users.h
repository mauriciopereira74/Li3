#ifndef USERS_H
#define USERS_H

#include <time.h>
#include <stdbool.h>

/**
 * @brief Types of Account Status.
 */

enum Acc_Status { Active,
                  Inactive };

/**
 * @brief Types of User elements.
 */
typedef struct user
{
    char *username, /**< string that represents the login of the user. */
         *name, /**< string that represents the name of the user. */
         *pay_method; /**< string that represents the payment method chosen by the user. */

    char* gender; /**< char that represents the gender of the user. */

    char* Acc_Status; /**< string to check the user account status. */

    struct tm created_time; /**< struct that represents the datetime on which the user account was created. */

    struct tm birth_date ; /**< struct that represents the user's date of birth. */

    
} *User;


#endif