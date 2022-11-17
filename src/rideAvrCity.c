#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/interpreter.h"
#include "../includes/hashtables.h"

int precoMedioViagens_cidade(char* city){
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
}

int precoMedioViagens_cidade(char* city){
    
}