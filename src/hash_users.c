#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>

#include "../includes/hash_users.h"

GHashTable *hash_users(char const *filename, int *storage)
{
    printf("> (hash_users)\n");

    FILE *user_file = fopen(filename, "r");
    FILE *user_final = fopen("./entrada/users.csv", "w");

    printf("    > Opening files...");

    if (!user_file || !user_final) 
    {
        fprintf(stderr, "   > Couldn't open file(s).\n'");
        return NULL;
    }

    printf("Done!\n");

    char* buffer = malloc(sizeof(char) * USERS_SIZE);
    char* keep = malloc(sizeof(char) * USERS_SIZE);


    GHashTable *users_table= g_hash_table_new(g_int_hash, g_int_equal);

    int *num_to_add = (int*)malloc(sizeof(int));

    int i=0;

    while(fgets(buffer, USERS_SIZE, user_file)) {
        keep = strcpy(keep, buffer);
        fputs(keep, user_final);

        *num_to_add = get_number(buffer); 

        storage[i] = *num_to_add;
        g_hash_table_add(users_table, &storage[i]);

        i++;
    }

    printf("Done!\n\n");
    
    free(buffer); free(keep); free(num_to_add);
    fclose(user_file);

    return users_table;
}