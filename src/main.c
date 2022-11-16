#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/interpreter.h"
#include "../includes/hashtables.h"
#include "../includes/profile.h"

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
    drivers_table= g_hash_table_new(g_direct_hash, g_direct_equal);
    rides_table= g_hash_table_new(g_direct_hash, g_direct_equal);

    char* line = malloc(sizeof(char) * LINE_SIZE);
    parser(line);
    //line = malloc(sizeof(char) * LINE_SIZE);

    //else if (g_hash_table_contains(drivers_table,identifier) && querie==1) profileD(identifier);
    command_interpreter(line);
    return 0;
}