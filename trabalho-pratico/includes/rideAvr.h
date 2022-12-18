#ifndef RIDEAVR_H
#define RIDEAVR_H

#include <glib.h>
#include "../includes/list.h"

void precoMedioViagens_cidade(char* city,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table);
int check_dates(int day,int mon, int year,struct tm date);
void precoMedioViagens_datas(char *datas,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table);
void distanciaMedia(char *input,int N,char* filepointer,GHashTable *rides_table);
void listRides(char *input,int N,char* filepointer,GHashTable *users_table,GHashTable *drivers_table,GHashTable *rides_table);
void listDrivers(char *input,int N,char* filepointer);
void fill_ht_rides(GHashTable* ht_rides, int id, List l);

#endif