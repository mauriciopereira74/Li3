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

/*
void nDrivers(int n){
    int n_viagens=0; int avaliacao_total=0;
    double avaliacao_media=0;

    char array[100000];

    int i=1,j=1;
    
    for(;i<=10000;i++){
        struct driver *d = g_hash_table_lookup(drivers_table,GINT_TO_POINTER(i));
        for(;j<=1000000;j++){
            struct ride *r = g_hash_table_lookup(rides_table,j);
            if(d->id==r->driver_id) {
                avaliacao_total= avaliacao_total + r->score_driver;
                n_viagens++;
            }
        }
        avaliacao_media=avaliacao_total/n_viagens;
        //array[i]=avaliacao_media;
    }

}
*/