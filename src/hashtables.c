#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/hashtables.h"

#include <glib.h>

void user_insert(User user){
    
    g_hash_table_add(users_table,user->name);
    
}

void driver_insert(Driver driver){
    g_hash_table_add(drivers_table,driver->id);
}

void ride_insert(Ride ride){
    g_hash_table_add(rides_table,ride->id);
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





