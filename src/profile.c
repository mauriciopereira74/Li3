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


int age(struct tm birth_date){
    time_t rawtime;
    time(&rawtime);
    struct tm *info=localtime(&rawtime);
    int present_year= info->tm_year+1900;
    int birth_year= birth_date.tm_year;

    
   int final_year = present_year - birth_year;

   return final_year;
}

void profile(char *id_r,int N,char* filepointer){
    char ptr[100];
    if(g_hash_table_contains(drivers_table,atoi(id_r))){
        
        long int id= atoi(id_r);
        struct driver *d = g_hash_table_lookup(drivers_table,GINT_TO_POINTER(id));

        int avaliacao_total=0; int n_viagens=0; int distancia=0;
        double total_auferido=0, avaliacao_media=0;

        long int i= 1;
        for(;i<=N;i++){
            struct ride *r= g_hash_table_lookup(rides_table,i);
            if(get_rideDriverId(r)==id){
                avaliacao_total= avaliacao_total + get_DriverScore(r);
                n_viagens++;
                distancia= distancia +get_RideDistance(r);
            }
        }
        avaliacao_media=avaliacao_total/n_viagens;

        if(strcmp(get_Class(d),"basic")==0) total_auferido= total_auferido + 3.25 + 0.62* distancia;
            else if(strcmp(get_Class(d),"green")==0) total_auferido= total_auferido +4.00+ 0.79* distancia;
                else total_auferido= total_auferido + 5.20+ 0.94*distancia;

        sprintf(ptr,"%s;%s;%d;%f;%d;%f\n",get_driverName(d),get_driverGender(d),age(get_driverBirth(d)),avaliacao_media,n_viagens,total_auferido);
    }



    else if(g_hash_table_contains(users_table,id_r)){
        struct user *u = g_hash_table_lookup(users_table,id_r);
        int avaliacao_total=0; int n_viagens=0;
        double total_custo=0, avaliacao_media=0;
        
        

        long int i= 000000000001;
        for(;i<=N;i++){
            struct ride *r= g_hash_table_lookup(rides_table,i);
            if(strcmp(get_RideUsername(r),id_r)==0){
                avaliacao_total= avaliacao_total + get_UserScore(r);
                n_viagens++;
                struct driver *d= g_hash_table_lookup(drivers_table,GINT_TO_POINTER(get_rideDriverId(r)));
                if(strcmp(get_Class(d),"basic")==0) total_custo= total_custo + 3.25 + 0.62*get_RideDistance(r);
                else if(strcmp(get_Class(d),"green")==0) total_custo= total_custo +4.00+ 0.79*get_RideDistance(r);
                else total_custo= total_custo + 5.20+ 0.94*get_RideDistance(r);
            }   
        }
        avaliacao_media=avaliacao_total/n_viagens;
        sprintf(ptr,"%s;%s;%d;%f;%d;%f\n",get_name(u),get_userGender(u),age(get_userBirth(u)),avaliacao_media,n_viagens,total_custo);
        //strcpy(ptr,aux);
        //printf("%s\n",ptr);
    }


   FILE* output = fopen(filepointer,"w");
   fprintf(output,"%s",ptr);;
   fclose(output);
}

