#ifndef QUERIEAUX_H
#define _H

#include <glib.h>

int age(struct tm birth_date);
int check_date(int day,int mon, int year,struct tm date);
int compareDistTotal(gconstpointer l1, gconstpointer l2);
GHashTable *sort_drivers_table(GHashTable *drivers_table,int q);
GHashTable *sort_users_table(GHashTable *users_table);

#endif