#ifndef QUERIESITR_H
#define QUERIESITR_H

#include <glib.h>
#include "user_interface.h"

void getLine(char* line, size_t N);

void querie1_itr(char *id_s,int N,GHashTable *users_table,GHashTable *drivers_table,GHashTable *rides_table);
void querie2_itr(char *top_s,int N,GHashTable *drivers_table);
void querie3_itr(char *top_s,int N,GHashTable *users_table);
void querie4_itr(char* city,int N,GHashTable *drivers_table,GHashTable *rides_table);
void querie5_itr(char *datas,int N,GHashTable *drivers_table,GHashTable *rides_table);
void querie6_itr(char *input,int N,GHashTable *rides_table);
void querie7_itr(char *input,int N,GHashTable *drivers_table,GHashTable *rides_table);
void querie8_itr(char *input,int N,GHashTable *users_table,GHashTable *drivers_table,GHashTable *rides_table);
void querie9_itr(char *input,int N,GHashTable *rides_table);


#endif