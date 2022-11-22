#ifndef HASHTABLES_H
#define HASHTABLES_H

#include "../includes/parse_users.h"
#include "../includes/parse_drivers.h"
#include "../includes/parse_rides.h"

#include <glib.h>

void user_insert( User user);
void driver_insert(Driver driver);
void ride_insert(Ride ride);

int user_check(char *name);
int driver_check(char *id);
int ride_check(char *id);


#endif