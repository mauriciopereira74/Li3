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
 

int main(){
    users_table = g_hash_table_new(g_int_hash, g_int_equal);
    drivers_table= g_hash_table_new(g_int_hash, g_int_equal);
    rides_table= g_hash_table_new(g_int_hash, g_int_equal); 

    char* line = malloc(sizeof(char) * LINE_SIZE);
    parser(line);
    struct user *u = g_hash_table_lookup(users_table,"MiTeixeira");
    printf("%s\n",u->pay_method);
    struct driver *d = g_hash_table_lookup(drivers_table,"000000000001");
    printf("%s\n",d->name);
    return 0;
}