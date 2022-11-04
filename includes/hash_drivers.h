#ifndef HDRIVES_H
#define HDRIVES_H

/** Max line size on the file drivers.csv. */
#define DRIVERS_SIZE 20000

#include <stdbool.h>
#include <glib.h>


int get_third_number(char* string);


GHashTable *hash_drivers(char const *filename, GHashTable *users_table, int *storage);

#endif