#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/interpreter.h"
#include "../includes/profile.h"
#include "../includes/hashtables.h"

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


void profile(char *id_s,int N,char* filepointer){
    int flag = 1;
    char ptr[BUFSIZ];
    int id= atoi(id_s);
    if(g_hash_table_contains(drivers_table,GINT_TO_POINTER(id))){
        
        struct driver *d = g_hash_table_lookup(drivers_table,GINT_TO_POINTER(id));

        if(strcmp(get_driverStatus(d),"active")==0){
            int avaliacao_total=0; int n_viagens=0;
            double total_auferido=0, avaliacao_media=0;

            int i= 1;
            for(;i<=N;i++){
                struct ride *r= g_hash_table_lookup(rides_table,GINT_TO_POINTER(i));
                if(get_rideDriverId(r)==id){
                    avaliacao_total= avaliacao_total + get_DriverScore(r);
                    n_viagens++;

                    if(strcmp(get_Class(d),"basic")==0) total_auferido += 3.25 + 0.62* (double)get_RideDistance(r) + get_tip(r);
                    else if(strcmp(get_Class(d),"green")==0) total_auferido += 4.00+ 0.79* (double)get_RideDistance(r) + get_tip(r);
                    else total_auferido += 5.20+ 0.94* (double)get_RideDistance(r) + get_tip(r);
                }
            }
            avaliacao_media=avaliacao_total/(double)n_viagens;

            sprintf(ptr,"%s;%s;%d;%.3f;%d;%.3f\n",get_driverName(d),get_driverGender(d),age(get_driverBirth(d)),avaliacao_media,n_viagens,total_auferido);
        }
        else{
            flag = 0;
        }
    }

    else if(g_hash_table_contains(users_table,id_s)){
        struct user *u = g_hash_table_lookup(users_table,id_s);

        if(strcmp(get_userStatus(u),"active")==0){

            int avaliacao_total=0, n_viagens=0;
            double total_gasto=0,avaliacao_media=0;

            int i= 1;
            for(;i<=N;i++){
                struct ride *r= g_hash_table_lookup(rides_table,GINT_TO_POINTER(i));
                if(strcmp(get_RideUsername(r),id_s)==0){
                    avaliacao_total= avaliacao_total + get_UserScore(r);
                    n_viagens++;

                    struct driver *d= g_hash_table_lookup(drivers_table,GINT_TO_POINTER(get_rideDriverId(r)));
                    
                    if(strcmp(get_Class(d),"basic")==0) total_gasto += 3.25 + 0.62 *get_RideDistance(r) + get_tip(r);
                    else if(strcmp(get_Class(d),"green")==0) total_gasto +=  4.00+ 0.79*get_RideDistance(r) + get_tip (r);
                    else total_gasto += 5.20+ 0.94 * get_RideDistance(r) + get_tip (r);
                    
                }
            }
            avaliacao_media=avaliacao_total/(double)n_viagens;
            sprintf(ptr,"%s;%s;%d;%.3f;%d;%.3f\n",get_name(u),get_userGender(u),age(get_userBirth(u)),avaliacao_media,n_viagens,total_gasto);
        }
        else{
            flag = 0;
        }
    }


   FILE* output = fopen(filepointer,"w");
    if(flag == 1){
    fprintf(output,"%s",ptr);
    }
   fclose(output);
}