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

void precoMedioViagens_cidade(char* city,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table){  // querie 4
    int i=1; double preco_viagem=0; int n_viagens=0;
    double preco_medio=0;
    char* ptr = malloc(sizeof(float));

    for(;i<=N;i++){
        struct ride *r= get_rideStruct(rides_table,i);
        if(strcmp(get_RideCity(r),city)==0){
            struct driver *d= get_driverStruct(drivers_table,get_rideDriverId(r));
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

void precoMedioViagens_datas(char *datas,int N,char* filepointer,GHashTable *drivers_table,GHashTable *rides_table){   // querie 5

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
        struct ride *r= get_rideStruct(rides_table,i);
        if((check_dates(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_dates(day_from,mon_from,year_from,get_rideDate(r))== 0 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==1) ||
           (check_dates(day_from,mon_from,year_from,get_rideDate(r))==-1 && check_dates(day_to,mon_to,year_to,get_rideDate(r))==0)) {
            struct driver *d= get_driverStruct(drivers_table,get_rideDriverId(r));
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

void distanciaMedia(char *input,int N,char* filepointer,GHashTable *rides_table){  // querie 6

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
        struct ride *r= get_rideStruct(rides_table,i);
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
/*
void exactly_age(struct tm birth_date){

    int REF_DAY = 9;
    int REF_MON = 10;
    int REF_YEAR = 2022;

    int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (birth_date.tm_mday > REF_DAY) {
        REF_DAY += month[birth_date.tm_mon - 1];
        REF_MON--;
    }
    if (birth_date.tm_mon > REF_MON) {
        REF_YEAR--;
        REF_MON += 12;
    }

    int final_date = REF_DAY - birth_date.tm_mday;
    int final_month = REF_MON - birth_date.tm_mon;
    int final_year = REF_YEAR - birth_date.tm_year;
}
*/

int compareWantedRides(const void *l1,const void *l2){

    List r1 = (List) l1;
    List r2 = (List) l2;
    printf("entrei no sort\n");
    int accAgeDriverl1 = age(get_ListAccAge_driver(r1));
    int accAgeDriverl2 = age(get_ListAccAge_driver(r2));
    int accAgeUserl1 = age(get_ListAccAge_user(r1));
    int accAgeUserl2 = age(get_ListAccAge_user(r2));

    if(accAgeDriverl1 == accAgeDriverl2){
        if(accAgeUserl1 > accAgeUserl2){
            return accAgeUserl1 - accAgeUserl2;
        }
    }
    else{
        return accAgeDriverl1 - accAgeDriverl2;
    }
}



void listRides(char *input,int N,char* filepointer,GHashTable *users_table,GHashTable *drivers_table,GHashTable *rides_table){

    char *gender =strtok(input," ");
    char *idade_ref = strtok(NULL," ");
    List *wanted_rides = malloc(1500 * sizeof(List));
    int j=0;

    for(int i=1;i<=N;i++){
        struct ride *r= get_rideStruct(rides_table,i);
        struct driver *d = get_driverStruct(drivers_table,get_rideDriverId(r));
        struct user *u = get_userStruct(users_table,get_RideUsername(r));

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
            int n = sizeof(List);
            memcpy(&wanted_rides[j],&l,sizeof(List));
            printf("%s\n",get_ListDriverName(wanted_rides[j]));
            //printf("N->%d\n",j);
            //printf("%d D->> %s U->>%s D->%d/%d/%d U->%d/%d/%d \n",get_ListDriverID(l),get_ListDriverName(l),get_ListUserName(l),get_ListAccAge_driver(l).tm_mday,get_ListAccAge_driver(l).tm_mon,get_ListAccAge_driver(l).tm_year,get_ListAccAge_user(l).tm_mday,get_ListAccAge_user(l).tm_mon,get_ListAccAge_user(l).tm_year);
            //sprintf(ptr,"%d D->> %s U->>%s D->%d/%d/%d U->%d/%d/%d \n",get_ListDriverID(l),get_ListDriverName(l),get_ListUserName(l),get_ListAccAge_driver(l).tm_mday,get_ListAccAge_driver(l).tm_mon,get_ListAccAge_driver(l).tm_year,get_ListAccAge_user(l).tm_mday,get_ListAccAge_user(l).tm_mon,get_ListAccAge_user(l).tm_year);
            free(l);   
            j++;     
        }
    }
    printf("%s\n",get_ListDriverName(wanted_rides[1]));
    printf("%s\n",get_ListDriverName(wanted_rides[2]));
    printf("%s\n",get_ListDriverName(wanted_rides[3]));

    //qsort(wanted_rides,j,sizeof(List),compareWantedRides);
}
/*
}
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
