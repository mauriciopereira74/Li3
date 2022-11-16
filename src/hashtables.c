#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/hashtables.h"

#include <stdio.h>
#include <glib.h>

GHashTable *users_table;
GHashTable *drivers_table;
GHashTable *rides_table;

void user_insert(User user){
    g_hash_table_insert(users_table,user->username,clone_user(user));
}

void driver_insert(Driver driver){
    g_hash_table_insert(drivers_table,GINT_TO_POINTER(driver->id),clone_driver(driver));
}

void ride_insert(Ride ride){
    g_hash_table_insert(rides_table,GINT_TO_POINTER(ride->id),clone_ride(ride));
}

int user_check(char *name){
    if (g_hash_table_lookup(users_table,name)) return 1;
    else return 0;
}

int driver_check(char *id){
    if (g_hash_table_lookup(drivers_table,id)) return 1;
    else return 0;
}

int ride_check(char *id){
    if (g_hash_table_lookup(rides_table, id)) return 1;
    else return 0;
}





