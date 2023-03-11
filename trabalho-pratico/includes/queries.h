#ifndef QUERIES_H
#define QUERIES_H

#include "user_interface.h"

void querie1(char *id_s,int N,char* filepointer,GHashTable *users_table,GHashTable *drivers_table,GHashTable *rides_table);
void querie2(char *top_s,int N,char* filepointer,GHashTable *drivers_table);
void querie3(char *top_s,int N,char* filepointer,GHashTable *users_table);
void querie4(char* city,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table);
void querie5(char *datas,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table);
void querie6(char *input,int N,char* filepointer,GHashTable *rides_table);
void querie7(char *input,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table);
void querie8(char *input,int N,char* filepointer,GHashTable *users_table,GHashTable *drivers_table,GHashTable *rides_table);
void querie9(char *input,int N,char* filepointer,GHashTable *rides_table);

#endif