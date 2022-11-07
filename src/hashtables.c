#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/hashtables.h"

#include <glib.h>


GHashTable *users_table= g_hash_table_new(g_int_hash, g_int_equal);

GHashTable *drivers_table= g_hash_table_new(g_int_hash, g_int_equal);

GHashTable *rides_table= g_hash_table_new(g_int_hash, g_int_equal);

void user_insert(User user){
    g_hash_table_insert(users_table,user->name,user);
}

void driver_insert(Driver driver){
    g_hash_table_insert(drivers_table,driver->id,driver);
}

void ride_insert(Ride ride){
    g_hash_table_insert(rides_table,ride->id,ride);
}

bool user_check(char *name){
    return (g_hash_table_contains(users_table,name));
}

bool driver_check(long int id){
    return (g_hash_table_contains(drivers_table,id));
}

bool ride_check(long int id){
    return (g_hash_table_contains(rides_table,id));
}





