#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/hashtables.h"

#include <glib.h>



void user_insert(GHashTable *users_table, User user){
    g_hash_table_insert(users_table,user->username,user);
}

void driver_insert(GHashTable *drivers_table,Driver driver){
    g_hash_table_insert(drivers_table,driver->id,driver);
}

void ride_insert(GHashTable *rides_table,Ride ride){
    g_hash_table_insert(rides_table,ride->id,ride);
}

bool user_check(GHashTable *users_table,char *name){
    return (g_hash_table_contains(users_table,name));
}

bool driver_check(GHashTable *drivers_table,long int id){
    return (g_hash_table_contains(drivers_table,id));
}

bool ride_check(GHashTable *rides_table,long int id){
    return (g_hash_table_contains(rides_table,id));
}





