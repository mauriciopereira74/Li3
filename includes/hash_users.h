#ifndef HUSERS_H
#define HUSERS_H

/** Max line size on the file drivers.csv. */
#define USERS_SIZE 200000

#include <stdbool.h>
#include <glib.h>


GHashTable *hash_users(char const *filename, int *storage);

#endif