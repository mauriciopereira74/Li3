#ifndef HRIDES_H
#define HRIDES_H

/** Max line size on the file drivers.csv. */
#define USERS_SIZE 2000000

#include <stdbool.h>
#include <glib.h>


GHashTable *hash_rides(char const *filename, int *storage);

#endif