#ifndef LIST_H
#define LIST_H


typedef struct list *List;

int get_ListDriverID(List l);

struct tm get_ListAccAge_user(List l);

struct tm get_ListAccAge_driver(List l);

int get_ListDistancia_total(List l);

char *get_ListDriverName(List l);

char *get_ListUserUsername(List l);

char *get_ListUserName(List l);

double get_ListAvaliacaoMedia(List l);

void set_ListDriverID(List l, int driverID);

void set_ListAccAgeUser(List l, struct tm accAge_user);

void set_ListAccAgeDriver(List l,struct tm accAge_driver);

void set_ListDistanciaTotal(List l,int distanciaTotal);

void set_ListDriverName(List l, char *driverName);

void set_ListUserUsername(List l, char *user_username);

void set_ListUserName(List l, char *user_name);

void set_ListAvaliacaoMedia(List l, double avaliacaoMedia);

List clone_list(List l);

#endif