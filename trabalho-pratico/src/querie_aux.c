#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/interpreter.h"
#include <glib.h>

#define REF_DAY 9
#define REF_MON 10
#define REF_YEAR 2022

int age(struct tm birth_date){

    int birth_year= birth_date.tm_year;    
    int final_year = REF_YEAR - birth_year;
    
    if(REF_MON < birth_date.tm_mon){

        final_year--;
   }
   if(REF_MON == birth_date.tm_mon){
        if(REF_DAY < birth_date.tm_mday){
            final_year--;
        }
    }

    return final_year;
}

int check_date(int day,int mon, int year,struct tm date){ // return 1 se date_recebido for depois de date ; return -1 se date_recebido for antes de date; return 0 se forem iguais

    int r=2;
    
    if(year>date.tm_year) r= 1;
    else if(year<date.tm_year) r=-1;
    else{
        if(mon>date.tm_mon) r= 1;
        else if(mon<date.tm_mon) r= -1;
        else{
            if (day>date.tm_mday) r= 1;
            else if(day<date.tm_mday) r= -1;
            else r= 0;
        }
    }
    return r;
}


int compareDistTotal(gconstpointer l1, gconstpointer l2) {
    User ua = (User )l1;
    User ub = (User )l2;

    if(get_userDistanciaTotal(ua) == get_userDistanciaTotal(ub)){
        if(check_date(get_userLastRide(ua).tm_mday,get_userLastRide(ua).tm_mon,get_userLastRide(ua).tm_year,get_userLastRide(ub))==1 ){
            return ((get_userLastRide(ua).tm_mday +get_userLastRide(ua).tm_mon +get_userLastRide(ua).tm_year) - (get_userLastRide(ub).tm_mday + get_userLastRide(ub).tm_mon +get_userLastRide(ub).tm_year));
        }
        else if(check_date(get_userLastRide(ua).tm_mday,get_userLastRide(ua).tm_mon,get_userLastRide(ua).tm_year,get_userLastRide(ub))==-1)
            return ((get_userLastRide(ub).tm_mday +get_userLastRide(ub).tm_mon +get_userLastRide(ub).tm_year) - (get_userLastRide(ua).tm_mday + get_userLastRide(ua).tm_mon +get_userLastRide(ua).tm_year));
        else return strcmp(get_username(ua),get_username(ub));
    }

    return (get_userDistanciaTotal(ua) < get_userDistanciaTotal(ub)) - (get_userDistanciaTotal(ua) > get_userDistanciaTotal(ub));
}

int compareDriversAvalMedia(gconstpointer a, gconstpointer b){
    Driver d1 = (Driver) a;
    Driver d2 = (Driver) b;

    if(get_driverAvalMedia(d1)==get_driverAvalMedia(d2)){
        if(get_driverLastRide(d1).tm_year == get_driverLastRide(d2).tm_year){
            if(get_driverLastRide(d1).tm_mon == get_driverLastRide(d2).tm_mon){
                return (get_driverLastRide(d1).tm_mday - get_driverLastRide(d2).tm_mday);
            }
            else {
                return (get_driverLastRide(d1).tm_mon - get_driverLastRide(d2).tm_mon);
            }
        }
        else {
            return (get_driverLastRide(d1).tm_year - get_driverLastRide(d2).tm_year);
        }
    }
    else {
        return (get_driverAvalMedia(d1)-get_driverAvalMedia(d2));
    }

}

int compareDriversAval(gconstpointer a, gconstpointer b){
    Driver d1 = (Driver) a;
    Driver d2 = (Driver) b;

    if(get_driverAvalMedia(d1)==get_driverAvalMedia(d2)){
       return get_driverId(d1) - get_driverId(d2);
    }
    else {
        return (get_driverAvalMedia(d1)-get_driverAvalMedia(d2));
    }

}

GHashTable *sort_drivers_table(GHashTable *drivers_table,int q){
    GHashTable *sorted_drivers_table = g_hash_table_new(g_direct_hash, g_direct_equal);

    if(q==2){

        GList *drivers_list = g_hash_table_get_values(drivers_table);
        drivers_list = g_list_sort(drivers_list, compareDriversAvalMedia);


    for (GList *l = drivers_list; l != NULL; l = l->next){
        Driver driver = (Driver) l->data;
        g_hash_table_insert(sorted_drivers_table,GINT_TO_POINTER(get_driverId(driver)), driver);
    }

    }
    else if(q==7){

        GList *drivers_list = g_hash_table_get_values(drivers_table);
        drivers_list = g_list_sort(drivers_list, compareDriversAval);

    for (GList *l = drivers_list; l != NULL; l = l->next){
        Driver driver = (Driver) l->data;
        g_hash_table_insert(sorted_drivers_table,GINT_TO_POINTER(get_driverId(driver)), driver);
    }
    
    }
    return sorted_drivers_table;
}

GHashTable *sort_users_table(GHashTable *users_table){

    GList *users_list = g_hash_table_get_values(users_table);
    users_list = g_list_sort(users_list, compareDistTotal);

    GHashTable *sorted_users_table = g_hash_table_new(g_direct_hash, g_direct_equal);

    for (GList *l = users_list; l != NULL; l = l->next){
        User u = (User) l->data;
        g_hash_table_insert(sorted_users_table, get_username(u), u);
    }

    return sorted_users_table;

}

