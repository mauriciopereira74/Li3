#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"

#include <glib.h>

void user_insert( User user);
void driver_insert(Driver driver);
void ride_insert(Ride ride);

int user_check(char *name);
int driver_check(char *id);
int ride_check(char *id);
