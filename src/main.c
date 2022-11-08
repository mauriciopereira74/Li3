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
 

int main(){
    users_table = g_hash_table_new(g_str_hash, g_str_equal);
    drivers_table= g_hash_table_new(g_str_hash, g_str_equal);
    rides_table= g_hash_table_new(g_str_hash, g_str_equal); 

    char* line = malloc(sizeof(char) * LINE_SIZE);
    parser(line);
    return 0;
}