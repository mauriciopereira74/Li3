#ifndef PROFILE_H
#define PROFILE_H

#include <glib.h>

void profile(char *id,int N,char* filepointer,GHashTable *users_table,GHashTable *drivers_table,GHashTable *rides_table);
int age(struct tm birth_date);

#endif