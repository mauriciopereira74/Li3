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

    //int present_day= info->tm_mday;
    //int present_month=info->tm_mon;
    int present_year= info->tm_year+1900;

    //int birth_day= birth_date.tm_mday;
    //int birth_month= birth_date.tm_mon;
    int birth_year= birth_date.tm_year;

    //int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    //if (birth_day > present_day) {
      //present_day = present_day + month[birth_month - 1];
     // present_month = present_month - 1;
   //}

   //if (birth_month > present_month) {
     // present_year = present_year - 1;
      //present_month = present_month + 12;
   //}

   //int final_date = present_day - birth_day;
   //int final_month = present_month - birth_month;
   int final_year = present_year - birth_year;

   return final_year;
}

void profileU(char *id){
   struct user *u = g_hash_table_lookup(users_table,id);
   int avaliacao_total=0; int avaliacao_media=0; int n_viagens=0;
   double total_custo=0;

   long int i= 000000000001;
   for(;i<=1000000;i++){
      struct ride *r= g_hash_table_lookup(rides_table,i);
      if(strcmp(r->user_username,id)==0){
         avaliacao_total= avaliacao_total + r->score_user;
         n_viagens++;
         struct driver *d= g_hash_table_lookup(drivers_table,GINT_TO_POINTER(r->driver_id));
         if(strcmp(d->Class,"basic")==0) total_custo= total_custo + 3.25 + 0.62* r->distance;
         else if(strcmp(d->Class,"green")==0) total_custo= total_custo +4.00+ 0.79* r->distance;
         else total_custo= total_custo + 5.20+ 0.94*r->distance;
      }   
   }
   avaliacao_media=avaliacao_total/n_viagens;
   printf("%s;%s;%d;%d;%d;%f\n",u->name,u->gender,age(u->birth_date),avaliacao_media,n_viagens,total_custo);

}


void profileD(char *id_r){
   long int id= atoi(id_r);
   struct driver *d = g_hash_table_lookup(drivers_table,GINT_TO_POINTER(id));

   int avaliacao_total=0; int avaliacao_media=0; int n_viagens=0; int distancia=0;
   double total_auferido=0;

   long int i= 1;
   for(;i<=1000000;i++){
      struct ride *r= g_hash_table_lookup(rides_table,i);
      if(r->driver_id==id){
         avaliacao_total= avaliacao_total + r->score_driver;
         n_viagens++;
         distancia= distancia + r->distance;
      }
   }
   avaliacao_media=avaliacao_total/n_viagens;

   if(strcmp(d->Class,"basic")==0) total_auferido= total_auferido + 3.25 + 0.62* distancia;
      else if(strcmp(d->Class,"green")==0) total_auferido= total_auferido +4.00+ 0.79* distancia;
         else total_auferido= total_auferido + 5.20+ 0.94*distancia;

   printf("%s;%s;%d;%d;%d;%f\n",d->name,d->gender,age(d->birth_date),avaliacao_media,n_viagens,total_auferido);
}
