#include "../includes/parse_users.h"
#include "../includes/parse_drivers.h"
#include "../includes/parse_rides.h"
#include "../includes/hashtables.h"

#include <stdio.h>
#include <glib.h>

GHashTable *users_table;
GHashTable *drivers_table;
GHashTable *rides_table;

void user_insert(User u){
    g_hash_table_insert(users_table,get_username(u),clone_user(u));
}

void driver_insert(Driver d){
    g_hash_table_insert(drivers_table,GINT_TO_POINTER(get_driverId(d)),clone_driver(d));
}

void ride_insert(Ride r){
    g_hash_table_insert(rides_table,GINT_TO_POINTER(get_rideId(r)),clone_ride(r));
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
