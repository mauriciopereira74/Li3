#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/interpreter.h"
#include "../includes/hashtables.h"

void precoMedioViagens_cidade(char* city,int N,char* filepointer){
    int i=1; double preco_viagem=0; int n_viagens=0;
    double preco_medio=0;
    char* ptr = malloc(sizeof(float));

    for(;i<=N;i++){
        struct ride *r= g_hash_table_lookup(rides_table,i);
        if(strcmp(get_RideCity(r),city)==0){
            struct driver *d= g_hash_table_lookup(drivers_table,GINT_TO_POINTER(get_rideDriverId(r)));
            if(strcmp(get_Class(d),"basic")==0) preco_viagem= preco_viagem + 3.25 + 0.62*get_RideDistance(r);
            else if(strcmp(get_Class(d),"green")==0) preco_viagem= preco_viagem +4.00+ 0.79*get_RideDistance(r);
            else preco_viagem= preco_viagem + 5.20+ 0.94*get_RideDistance(r);
            n_viagens++;
        }
    }
    preco_medio=preco_viagem/n_viagens;
    sprintf(ptr,"%.3f\n",preco_medio);
    file_writer(filepointer,ptr);
}

int check_dates(int day,int mon, int year,struct tm date){ // return 1 se date_recebido for depois de date ; return -1 se date_recebido for antes de date; return 0 se forem iguais

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

void precoMedioViagens_datas(char *datas,int N,char* filepointer){

    char *date_from,*date_to;
    int n_viagens=0;
    double preco_medio=0,preco_viagem=0;
    char* ptr = malloc(sizeof(float));

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

    for(int i=1;i<=N;i++){
        struct ride *r= g_hash_table_lookup(rides_table,i);
        if((check_dates(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_dates(day_from,mon_from,year_from,get_rideDate(r))== 0 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_dates(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==0)) {
            struct driver *d= g_hash_table_lookup(drivers_table,GINT_TO_POINTER(get_rideDriverId(r)));
            if(strcmp(get_Class(d),"basic")==0) preco_viagem= preco_viagem + 3.25 + 0.62*get_RideDistance(r);
            else if(strcmp(get_Class(d),"green")==0) preco_viagem= preco_viagem +4.00+ 0.79*get_RideDistance(r);
            else preco_viagem= preco_viagem + 5.20+ 0.94*get_RideDistance(r);
            n_viagens++;
        }
    }
    preco_medio=preco_viagem/n_viagens;
    sprintf(ptr,"%.3f\n",preco_medio);
    file_writer(filepointer,ptr);
}