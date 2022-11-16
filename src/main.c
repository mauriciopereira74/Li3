#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/interpreter.h"
#include "../includes/hashtables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>
 
 extern GHashTable* users_table;
 extern GHashTable* drivers_table;
 extern GHashTable* rides_table;

int main(){
    users_table = g_hash_table_new(g_str_hash, g_str_equal);
    drivers_table= g_hash_table_new(g_str_hash, g_str_equal);
    rides_table= g_hash_table_new(g_str_hash, g_str_equal); 

    char* line = malloc(sizeof(char) * LINE_SIZE);
    parser(line);
    //line = malloc(sizeof(char) * LINE_SIZE);
    int u,d,r;

    u = g_hash_table_size(users_table);
    d = g_hash_table_size(drivers_table);
    r = g_hash_table_size(rides_table);

    printf("Users -> %d\nDrivers -> %d\nRides -> %d\n",u,d,r);
    command_interpreter(line);
    return 0;
}