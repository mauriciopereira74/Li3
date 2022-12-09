#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/profile.h"
#include "../includes/interpreter.h"
#include "../includes/list.h"

#include <glib.h>

void precoMedioViagens_cidade(char* city,int N,char* filepointer){  // querie 4
    int i=1; double preco_viagem=0; int n_viagens=0;
    double preco_medio=0;
    char* ptr = malloc(sizeof(float));

    for(;i<=N;i++){
        struct ride *r= get_rideStruct(i);
        if(strcmp(get_RideCity(r),city)==0){
            struct driver *d= get_driverStruct(get_rideDriverId(r));
            if(strcmp(get_Class(d),"basic")==0) preco_viagem= preco_viagem + 3.25 + 0.62*get_RideDistance(r);
            else if(strcmp(get_Class(d),"green")==0) preco_viagem= preco_viagem +4.00+ 0.79*get_RideDistance(r);
            else preco_viagem= preco_viagem + 5.20+ 0.94*get_RideDistance(r);
            n_viagens++;
        }
    }
    preco_medio=preco_viagem/(double)n_viagens;
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

void precoMedioViagens_datas(char *datas,int N,char* filepointer){   // querie 5

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
        struct ride *r= get_rideStruct(i);
        if((check_dates(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_dates(day_from,mon_from,year_from,get_rideDate(r))== 0 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_dates(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==0)) {
            struct driver *d= get_driverStruct(get_rideDriverId(r));
            if(strcmp(get_Class(d),"basic")==0) preco_viagem= preco_viagem + 3.25 + 0.62*get_RideDistance(r);
            else if(strcmp(get_Class(d),"green")==0) preco_viagem= preco_viagem +4.00+ 0.79*get_RideDistance(r);
            else preco_viagem= preco_viagem + 5.20+ 0.94*get_RideDistance(r);
            n_viagens++;
        }
    }
    preco_medio=preco_viagem/(double)n_viagens;
    sprintf(ptr,"%.3f\n",preco_medio);
    file_writer(filepointer,ptr);
}

void distanciaMedia(char *input,int N,char* filepointer){  // querie 6

    char *city =strtok(input," ");
    char *date_from = strtok(NULL," ");
    char *date_to=strtok(NULL," ");

    int n_viagens=0;
    double distancia_media=0,distancia_total=0;
    char* ptr = malloc(sizeof(float));

    int day_from,mon_from,year_from;
    int day_to,mon_to,year_to;

    day_from= atoi(strtok(date_from,"/"));
    mon_from= atoi(strtok(NULL,"/"));
    year_from=atoi(strtok(NULL,"/"));

    day_to= atoi(strtok(date_to,"/"));
    mon_to= atoi(strtok(NULL,"/"));
    year_to=atoi(strtok(NULL,"/"));

    for(int i=1;i<=N;i++){
        struct ride *r= get_rideStruct(i);
        if((check_dates(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==1 && strcmp(get_RideCity(r),city)==0) ||
           (check_dates(day_from,mon_from,year_from,get_rideDate(r))== 0 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==1 && strcmp(get_RideCity(r),city)==0) ||
           (check_dates(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==0 && strcmp(get_RideCity(r),city)==0)) {
            distancia_total += get_RideDistance(r);
            n_viagens++;
        }
    }
    distancia_media = distancia_total/(double)n_viagens;
    sprintf(ptr,"%.3f\n",distancia_media);
    file_writer(filepointer,ptr);
}

void swap(struct list *l1, struct list *l2)
{
    struct list *temp = l1;
    l1 = l2;
    l2 = temp;
}

void bubbleListRides(struct list *array[],int N){

    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N - i; j++)
            if ( age(get_ListAccAge_driver(array[j])) > age (get_ListAccAge_driver(array[j+1])))
                swap(array[j], array[j + 1]);

}

void bubbleListDrivers(struct list *array[],int N){

    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N - i; j++)
            if ( get_ListAvaliacaoMedia(array[j]) > get_ListAvaliacaoMedia(array[j+1]))
                swap(array[j], array[j + 1]);
}

void listRides(char *input,int N,char* filepointer){

    char *gender =strtok(input," ");
    char *idade_ref = strtok(NULL," ");
    int j=0;
    struct list *array[1500];

    for(int i=1;i<=N;i++){
        struct ride *r= get_rideStruct(i);
        struct driver *d = get_driverStruct(get_rideDriverId(r));
        struct user *u = get_userStruct(get_RideUsername(r));

        //printf("D-> %s ",get_driverGender(d));
        //printf("U-> %s\n",get_userGender(u));
        if (strcmp(get_driverGender(d),get_userGender(u))==0 && strcmp(get_driverGender(d),gender)==0 && age(get_driverCreateTime(d))>= atoi(idade_ref) && age(get_userCreateTime(u))>= atoi(idade_ref) ){
            struct list *l = malloc(sizeof(List));
            set_ListDriverID(l,get_driverId(d));
            set_ListDriverName(l,get_driverName(d));
            set_ListUserUsername(l,get_username(u));
            set_ListUserName(l,get_name(u));
            set_ListAccAgeDriver(l,get_driverCreateTime(d));
            set_ListAccAgeUser(l,get_userCreateTime(u));
            array[j]=l;
            j++;
            //printf("%d %s U->>%s %d/%d/%d %d/%d/%d \n",get_ListDriverID(l),get_ListDriverName(l),get_ListUserName(l),get_ListAccAge_driver(l).tm_mday,get_ListAccAge_driver(l).tm_mon,get_ListAccAge_driver(l).tm_year,get_ListAccAge_user(l).tm_mday,get_ListAccAge_user(l).tm_mon,get_ListAccAge_user(l).tm_year);
        }
    }
    bubbleListRides(array,j);
    //printf("%d\n",get_ListDriverID(array[0]));
    //printf("%d %s %d/%d/%d %d/%d/%d \n",get_ListDriverID(array[k]),get_ListDriverName(array[k]),get_ListAccAge_driver(array[k]).tm_mday,get_ListAccAge_driver(array[k]).tm_mon,get_ListAccAge_driver(array[k]).tm_year,get_ListAccAge_user(array[k]).tm_mday,get_ListAccAge_user(array[k]).tm_mon,get_ListAccAge_user(array[k]).tm_year);
    /* 
    for(int k=0;k<j;k++){
        printf("%d %s %d/%d/%d %d/%d/%d \n",get_ListDriverID(array[k]),get_ListDriverName(array[k]),get_ListAccAge_driver(array[k]).tm_mday,get_ListAccAge_driver(array[k]).tm_mon,get_ListAccAge_driver(array[k]).tm_year,get_ListAccAge_user(array[k]).tm_mday,get_ListAccAge_user(array[k]).tm_mon,get_ListAccAge_user(array[k]).tm_year);
    }
    */
}
/* 
void listDrivers(char *input,int N,char* filepointer){

    int avaliacao_total=0,n_viagens=0;
    double avaliacao_media=0;
    struct list *array[1500];
    int k=0;

    for(int j=1;j<=N;j++){
        struct driver *d = get_driverStruct(j);
        for(int i=1;i<=N;i++){
            struct ride *r= get_rideStruct(i);
            if(get_rideDriverId(r)==get_driverId(d)){
                avaliacao_total= avaliacao_total + get_DriverScore(r);
                n_viagens++;
            }
        }
        avaliacao_media=avaliacao_total/(double)n_viagens;
        struct list *l = malloc(sizeof(List));
        set_ListDriverID(l,get_driverId(d));
        set_ListDriverName(l,get_driverName(d));
        set_ListAvaliacaoMedia(l,avaliacao_media);
        array[k]=l;
        k++;
    }
    bubbleListDrivers(array,k);   
}

*/
