#include "../includes/list.h"
#include "../includes/parse_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glib.h>


struct list
{

    int driver_id, /**< string that represents the id number of a driver. */
        distacia_total;

    struct tm accAge_user,
              accAge_driver;

    char *driver_name,
         *user_username,
         *user_name;
    
    double avaliacao_media;
} ;


int get_ListDriverID(List l){
    return l->driver_id;
}

struct tm get_ListAccAge_user(List l){
    return l->accAge_user;
}

struct tm get_ListAccAge_driver(List l){
    return l->accAge_driver;
}

int get_ListDistancia_total(List l){
    return l->distacia_total;
}

char *get_ListDriverName(List l){
    return l->driver_name;
}

char *get_ListUserUsername(List l){
    return l->user_username;
}

char *get_ListUserName(List l){
    return l->user_name;
}

double get_ListAvaliacaoMedia(List l){
    return l->avaliacao_media;
}

void set_ListDriverID(List l, int driverID){
    l->driver_id=driverID;
}

void set_ListAccAgeUser(List l, struct tm accAge_user){
    l->accAge_user=accAge_user;
}

void set_ListAccAgeDriver(List l,struct tm accAge_driver){
    l->accAge_driver=accAge_driver;
}

void set_ListDistanciaTotal(List l,int distanciaTotal){
    l->distacia_total=distanciaTotal;
}

void set_ListDriverName(List l, char *driverName){
    l->driver_name=driverName;
}

void set_ListUserUsername(List l, char *user_username){
    l->user_username=user_username;
}

void set_ListUserName(List l, char *user_name){
    l->user_name=user_name;
}

void set_ListAvaliacaoMedia(List l, double avaliacaoMedia){
    l->avaliacao_media=avaliacaoMedia;
}

List clone_list(List l){
    List aux = malloc(sizeof(struct list));
    memcpy(aux,l,sizeof(struct list));
    return aux;
}