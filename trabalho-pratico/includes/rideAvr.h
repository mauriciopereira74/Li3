#ifndef RIDEAVR_H
#define RIDEAVR_H
void precoMedioViagens_cidade(char* city,int N,char* filepointer);
int check_dates(int day,int mon, int year,struct tm date);
void precoMedioViagens_datas(char *datas,int N,char* filepointer);

#endif