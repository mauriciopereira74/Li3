#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/interpreter.h"
#include "../includes/queries.h"
#include "../includes/querie_aux.h"

#include <glib.h>

#define BUFFERSIZE 100

#define REF_DAY 9
#define REF_MON 10
#define REF_YEAR 2022

char buffer[BUFFERSIZE];

/**
 * Controls the flow of the first query.
 */
void querie1(char *id_s,int N,char* filepointer,GHashTable *users_table,GHashTable *drivers_table,GHashTable *rides_table){
    int flag = 1;
    char ptr[BUFSIZ];
    int id= atoi(id_s);
    if(driver_check(drivers_table,id)==1){
        struct driver *d = get_driverStruct(drivers_table,id);
        if(strcmp(get_driverStatus(d),"active")==0){

            sprintf(ptr,"%s;%s;%d;%.3f;%d;%.3f\n",get_driverName(d),get_driverGender(d),age(get_driverBirth(d)),get_driverAvalMedia(d),get_driverNumViagens(d),get_driverTotalAuferido(d));
        }
        else{
            flag = 0;
        }
    }

    else if(user_check(users_table,id_s)==1){
        
        struct user *u = get_userStruct(users_table,id_s);
        if(strcmp(get_userStatus(u),"active")==0){

            sprintf(ptr,"%s;%s;%d;%.3f;%d;%.3f\n",get_user_name(u),get_userGender(u),age(get_userBirth(u)),get_userAvalMedia(u),get_userNumViagens(u),get_userTotalGasto(u));
        }
        else{
            flag = 0;
        }
    }
    else{
        flag = 0;
    }
  
    FILE* output = fopen(filepointer,"w");
    if(flag == 1){
        fprintf(output,"%s",ptr);
    }
   fclose(output);
}

void querie2(char *top_s,int N,char* filepointer,GHashTable *drivers_table) {
    char *ptr=malloc(sizeof(char) * 5);
    int top = atoi(top_s);
    int count = 0;
    GHashTableIter iter;
    gpointer key, value;

    GHashTable *sorted = sort_drivers_table(drivers_table,2);

    g_hash_table_iter_init(&iter, sorted);

    FILE* output = fopen(filepointer,"w");

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        if (count == top) {
            break;
        }
        Driver d = (Driver) value;

        ptr = malloc(sizeof(char) *100);
        sprintf(ptr,"%d;%s;%.3f \n",get_driverId(d),get_driverName(d),get_driverAvalMedia(d));
        fprintf(output,"%s",ptr);

        count++;
    }
    fclose(output);
    free(ptr);
    g_hash_table_destroy(sorted);

}


/**
 * Controls the flow of the third query.
 */

void querie3(char *top_s,int N,char* filepointer,GHashTable *users_table) {
    char *ptr=malloc(sizeof(char) * 5);
    int top = atoi(top_s);

    GHashTable *sorted = sort_users_table(users_table);

    int count = 0;
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, sorted);

    FILE* output = fopen(filepointer,"w");

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        if (count == top) {
            break;
        }
        User u = (User) value;

        ptr = malloc(sizeof(char) *100);
        sprintf(ptr,"%s;%s;%d \n",get_username(u),get_user_name(u),get_userDistanciaTotal(u));
        fprintf(output,"%s",ptr);

        count++;
    }
    fclose(output);
    free(ptr);
    g_hash_table_destroy(sorted);
}

/**
 * Controls the flow of the fourth query.
 */
void querie4(char* city,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table){  // querie 4
    double preco_viagem=0; int n_viagens=0;
    double preco_medio=0;
    char* ptr = malloc(sizeof(double));
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, rides_table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {

        Ride r = (Ride) value;

        if(strcmp(get_RideCity(r),city)==0){
            struct driver *d= get_driverStruct(drivers_table,get_rideDriverId(r));
            if(strcmp(get_Class(d),"basic")==0) preco_viagem= preco_viagem + 3.25 + 0.62*get_RideDistance(r);
            else if(strcmp(get_Class(d),"green")==0) preco_viagem= preco_viagem +4.00+ 0.79*get_RideDistance(r);
            else preco_viagem= preco_viagem + 5.20+ 0.94*get_RideDistance(r);
            n_viagens++;
        }
    }

    preco_medio=preco_viagem/(double)n_viagens;
    if(isnan(preco_medio)) sprintf(ptr,"");
    else{
        sprintf(ptr,"%.3f\n",preco_medio);
    }
    FILE* output = fopen(filepointer,"w");
    fprintf(output,"%s",ptr);
    fclose(output);
    free(ptr);

}
/**
 * Controls the flow of the fifth query.
 */
void querie5(char *datas,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table){   // querie 5

    char *date_from,*date_to;
    int n_viagens=0;
    double preco_medio=0,preco_viagem=0;
    char* ptr = malloc(sizeof(double));

    GHashTableIter iter;
    gpointer key, value;

    date_from= strtok(datas," ");
    date_to=strtok(NULL," ");

    int day_from,mon_from,year_from;
    int day_to,mon_to,year_to;

    day_from= atoi(strtok(date_from,"/"));
    mon_from= atoi(strtok(NULL,"/"));
    year_from=atoi(strtok(NULL,"/"));

    day_to= atoi(strtok(date_to,"/"));
    mon_to= atoi(strtok(NULL,"/"));
    year_to=atoi(strtok(NULL,"/"));

    g_hash_table_iter_init(&iter, rides_table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Ride r = (Ride) value;

        if((check_date(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_date(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_date(day_from,mon_from,year_from,get_rideDate(r))== 0 && check_date(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_date(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_date(day_to,mon_to,year_to,get_rideDate(r))==0)) {
            struct driver *d= get_driverStruct(drivers_table,get_rideDriverId(r));
            if(strcmp(get_Class(d),"basic")==0) preco_viagem= preco_viagem + 3.25 + 0.62*get_RideDistance(r);
            else if(strcmp(get_Class(d),"green")==0) preco_viagem= preco_viagem +4.00+ 0.79*get_RideDistance(r);
            else preco_viagem= preco_viagem + 5.20+ 0.94*get_RideDistance(r);
            n_viagens++;
        }
    }

    preco_medio=preco_viagem/(double)n_viagens;
    if(isnan(preco_medio)) sprintf(ptr,"");
    else{
        sprintf(ptr,"%.3f\n",preco_medio);
    }
    FILE* output = fopen(filepointer,"w");
    fprintf(output,"%s",ptr);
    fclose(output);
    free(ptr);
}

/**
 * Controls the flow of the sixth query.
 */
void querie6(char *input,int N,char* filepointer,GHashTable *rides_table){  // querie 6

    char *city =strtok(input," ");
    char *date_from = strtok(NULL," ");
    char *date_to=strtok(NULL," ");

    GHashTableIter iter;
    gpointer key, value;

    int n_viagens=0;
    double distancia_media=0,distancia_total=0;
    char* ptr = malloc(sizeof(double));

    int day_from,mon_from,year_from;
    int day_to,mon_to,year_to;

    day_from= atoi(strtok(date_from,"/"));
    mon_from= atoi(strtok(NULL,"/"));
    year_from=atoi(strtok(NULL,"/"));

    day_to= atoi(strtok(date_to,"/"));
    mon_to= atoi(strtok(NULL,"/"));
    year_to=atoi(strtok(NULL,"/"));

    g_hash_table_iter_init(&iter, rides_table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Ride r = (Ride) value;
        if((check_date(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_date(day_to,mon_to,year_to,get_rideDate(r))==1 && strcmp(get_RideCity(r),city)==0) ||
           (check_date(day_from,mon_from,year_from,get_rideDate(r))== 0 && check_date(day_to,mon_to,year_to,get_rideDate(r))==1 && strcmp(get_RideCity(r),city)==0) ||
           (check_date(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_date(day_to,mon_to,year_to,get_rideDate(r))==0 && strcmp(get_RideCity(r),city)==0)) {
            distancia_total += get_RideDistance(r);
            n_viagens++;
        }
    }

    distancia_media = distancia_total/(double)n_viagens;
    if(isnan(distancia_media)) sprintf(ptr,"");
    else{
        sprintf(ptr,"%.3f\n",distancia_media);
    }
    FILE* output = fopen(filepointer,"w");
    fprintf(output,"%s",ptr);
    fclose(output);
    free(ptr);
}

/**
 * Controls the flow of the seventh query.
 */

void querie7(char *input,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table) {

    char *ptr=malloc(sizeof(float));
    int top =atoi(strsep(&input," "));
    char *city = strsep(&input,"\0"); 


    int count = 0;
    GHashTableIter iter;
    gpointer key, value;

    GHashTable *aux = g_hash_table_new(g_direct_hash,g_direct_equal);

    g_hash_table_iter_init(&iter, rides_table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {

        Ride r = (Ride) value;

        if(strcmp(get_RideCity(r),city)==0){
            struct driver *d = get_driverStruct(drivers_table,get_rideDriverId(r));
            driver_insert(aux,d);
        }
    }


    GHashTable *sorted = sort_drivers_table(aux,7);
    g_hash_table_destroy(aux);

    g_hash_table_iter_init(&iter, sorted);

    FILE* output = fopen(filepointer,"w");

    while (g_hash_table_iter_next(&iter, &key, &value)) {

        if (count == top) {
            break;
        }
        Driver d = (Driver) value;

        ptr = malloc(sizeof(char) *100);
        sprintf(ptr,"%d;%s;%.3f \n",get_driverId(d),get_driverName(d),get_driverAvalMedia(d));
        fprintf(output,"%s",ptr);

        count++;
    }
    fclose(output);
    free(ptr);
    g_hash_table_destroy(sorted);

}


/**
 * Controls the flow of the eigth query.
 */
void querie8(char *input,int N,char* filepointer,GHashTable *users_table,GHashTable *drivers_table,GHashTable *rides_table){

    char *ptr=malloc(sizeof(char)*140);
    char *gender =strtok(input," ");
    char *idade_ref = strtok(NULL," ");
    GHashTableIter iter;
    gpointer key, value;

    GHashTable *aux = g_hash_table_new(g_direct_hash,g_direct_equal);

    g_hash_table_iter_init(&iter, rides_table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {

        Ride r = (Ride) value;

        struct driver *d = get_driverStruct(drivers_table,get_rideDriverId(r));
        struct user *u = get_userStruct(users_table,get_RideUsername(r));
        if (strcmp(get_driverGender(d),get_userGender(u))==0 && strcmp(get_driverGender(d),gender)==0 && age(get_driverCreateTime(d))>= atoi(idade_ref) && age(get_userCreateTime(u))>= atoi(idade_ref)){
            ride_insert(aux,r);
        }
    }


    g_hash_table_iter_init(&iter, aux);

    FILE* output = fopen(filepointer,"w");

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Ride r = (Ride) value;
        struct driver *d = get_driverStruct(drivers_table,get_rideDriverId(r));
        struct user *u = get_userStruct(users_table,get_RideUsername(r));
        sprintf(ptr,"%d;%s;%s;%s;D-> ;U-> %d/%d/%d \n",get_driverId(d),get_driverName(d),get_user_name(u),get_username(u),get_userCreateTime(u).tm_mday,get_userCreateTime(u).tm_mon,get_userCreateTime(u).tm_year);
        fprintf(output,"%s",ptr);


    }
    fclose(output);
    free(ptr);
    g_hash_table_destroy(aux);
}

/**
 * Controls the flow of the ninth query.
 */
void querie9(char *input,int N,char* filepointer,GHashTable *rides_table) {
    
    char *date_from = strtok(input," ");
    char *date_to = strtok(NULL," ");
    char* ptr = malloc(sizeof(char) * 100);

    int day_from = atoi(strtok(date_from,"/"));
    int mon_from = atoi(strtok(NULL,"/"));
    int year_from = atoi(strtok(NULL,"/"));

    int day_to= atoi(strtok(date_to,"/"));
    int mon_to= atoi(strtok(NULL,"/"));
    int year_to = atoi(strtok(NULL,"/"));

    GHashTableIter iter;
    gpointer key, value;

    GHashTable *aux = g_hash_table_new(g_direct_hash,g_direct_equal);

    g_hash_table_iter_init(&iter, rides_table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Ride r = (Ride) value;
        if((check_date(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_date(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_date(day_from,mon_from,year_from,get_rideDate(r))== 0 && check_date(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_date(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_date(day_to,mon_to,year_to,get_rideDate(r))==0) || 
           (check_date(day_from,mon_from,year_from,get_rideDate(r))== 0 && check_date(day_to,mon_to,year_to,get_rideDate(r))==0)){
            if(get_tip(r)!=0)ride_insert(aux,r);
        }

    }

    g_hash_table_iter_init(&iter, aux);

    FILE* output = fopen(filepointer,"w");

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Ride r = (Ride) value;
        sprintf(ptr,"%d;%d/%d/%d;%d;%s;%.3f\n",get_rideId(r),get_rideDate(r).tm_mday,get_rideDate(r).tm_mon,get_rideDate(r).tm_year,get_RideDistance(r),get_RideCity(r),get_tip(r));
        fprintf(output,"%s",ptr);

    }
    fclose(output);
    free(ptr);
    g_hash_table_destroy(aux);
}








