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

void precoMedioViagens_cidade(char* city){
    int i=1; double preço_viagem=0; int n_viagens=0;
    double preço_medio=0;
    for(;i<=1000000;i++){
        struct ride *r= g_hash_table_lookup(rides_table,i);
        if(strcmp(r->city,city)==0){
            struct driver *d= g_hash_table_lookup(drivers_table,GINT_TO_POINTER(r->driver_id));
            if(strcmp(d->Class,"basic")==0) preço_viagem= preço_viagem + 3.25 + 0.62*r->distance;
            else if(strcmp(d->Class,"green")==0) preço_viagem= preço_viagem +4.00+ 0.79*r->distance;
            else preço_viagem= preço_viagem + 5.20+ 0.94*r->distance;
            n_viagens++;
        }
    }
    preço_medio=preço_viagem/n_viagens;
    printf("%f\n",preço_medio);
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

void precoMedioViagens_datas(char *datas){

    char *date_from,*date_to;
    int avaliacao_total=0; int n_viagens=0;
    double total_custo=0, avaliacao_media=0;

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

    for(int i=1;i<=1000000;i++){
        struct ride *r= g_hash_table_lookup(rides_table,i);
        if((check_dates(day_from,mon_from,year_from,r->date)==-1 && check_dates(day_to,mon_to,year_to,r->date)==1) ||
           (check_dates(day_from,mon_from,year_from,r->date)== 0 && check_dates(day_to,mon_to,year_to,r->date)==1) ||
           (check_dates(day_from,mon_from,year_from,r->date)==-1 && check_dates(day_to,mon_to,year_to,r->date)==0)) {
            avaliacao_total= avaliacao_total + r->score_user;
            n_viagens++;
            struct driver *d= g_hash_table_lookup(drivers_table,GINT_TO_POINTER(r->driver_id));
            if(strcmp(d->Class,"basic")==0) total_custo= total_custo + 3.25 + 0.62* r->distance;
            else if(strcmp(d->Class,"green")==0) total_custo= total_custo +4.00+ 0.79* r->distance;
            else total_custo= total_custo + 5.20+ 0.94*r->distance;
        }
    }
    avaliacao_media = avaliacao_total/n_viagens;
    printf("%f\n",avaliacao_media);

}