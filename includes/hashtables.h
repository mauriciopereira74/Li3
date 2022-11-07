#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"

#include <glib.h>

GHashTable *users_table;
GHashTable *drivers_table;
GHashTable *rides_table;

void user_insert(User user);
void driver_insert(Driver driver);
void ride_insert(Ride ride);

bool user_check(char *name);
bool driver_check(long int id);
bool ride_check(long int id);
