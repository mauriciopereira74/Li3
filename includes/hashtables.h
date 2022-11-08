#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"

#include <glib.h>

GHashTable *users_table;
GHashTable *drivers_table;
GHashTable *rides_table;

void user_insert(GHashTable *users_table, User user);
void driver_insert(GHashTable *drivers_table,Driver driver);
void ride_insert(GHashTable *rides_table,Ride ride);

bool user_check(GHashTable *users_table,char *name);
bool driver_check(GHashTable *drivers_table,long int id);
bool ride_check(GHashTable *rides_table,long int id);
