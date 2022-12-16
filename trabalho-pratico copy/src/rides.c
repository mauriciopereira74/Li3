#include "../includes/rides.h"
#include "../includes/drivers.h"
#include "../includes/list.h"
#include "../includes/parse_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glib.h>

GHashTable *rides_table;

struct ride
{
    
    int id,        /**< string that represents the id number of a ride. */
        driver_id; /**< Driver of the ride. */

    struct tm date;     /**< struct that represents the ride's date. */

    char *city,          /**< string that represents the city of the ride. */
      *comment,          /**< string that represents the comment that was given to the driver/ride. */
      *user_username;        /**< User of the ride. */
      
    double tip;           /**< float that represents the tip that was given to the driver. */

    int score_user,      /**< int that represents the score of the user. */
        distance,      /**< float that represents the distance of the ride. */
        score_driver;    /**< int that represents the score of the driver. */
 
};


void debugRide(Ride r){

    printf("ID: %i; ",r->id);
    printf("Date: %d/%d/%d; ",r->date.tm_mday,r->date.tm_mon,r->date.tm_year);
    printf("Driver: %i; ",r->driver_id);
    printf("User: %s; ",r->user_username);
    printf("City: %s; ",r->city);
    printf("Distance: %d; ",r->distance);
    printf("Score User: %d; ",r->score_user);
    printf("Score Driver: %d; ",r->score_driver);
    printf("Tip: %.3f; ",r->tip);
    printf("Comment: %s;\n",r->comment);

}

/**
 * 
 * @brief Função que realiza o parsing do ficheiro rides.csv
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

void parse_rides (char* line, Ride r){

    r->id               = atoi(strdup(strsep(&line,FILE_CSV_DELIM)));
    r->date             = date_parse(strdup(strsep(&line,FILE_CSV_DELIM)));
    r->driver_id        = atoi(strdup(strsep(&line,FILE_CSV_DELIM)));
    r->user_username    = strdup(strsep(&line,FILE_CSV_DELIM));
    r->city             = strdup(strsep(&line,FILE_CSV_DELIM));
    r->distance         = atoi(strdup(strsep(&line,FILE_CSV_DELIM))); // could be int instead of float
    r->score_user       = atoi(strdup(strsep(&line,FILE_CSV_DELIM)));
    r->score_driver     = atoi(strdup(strsep(&line,FILE_CSV_DELIM)));
    r->tip              = atof(strdup(strsep(&line,FILE_CSV_DELIM)));
    r->comment          = strdup(strsep(&line,FILE_CSV_DELIM));

}


Ride clone_ride(Ride r){
    Ride aux=malloc(sizeof(struct ride));
    memcpy(aux,r,sizeof(struct ride));
    return aux;
}

void ride_insert(Ride r){
    g_hash_table_insert(rides_table,GINT_TO_POINTER(get_rideId(r)),clone_ride(r));
}

int ride_check(char *id){
    if (g_hash_table_lookup(rides_table, id)) return 1;
    else return 0;
}

struct ride *get_rideStruct(int id){
    struct ride *temp = g_hash_table_lookup(rides_table,GINT_TO_POINTER(id));
    return temp;
}

char *get_RideUsername(Ride r){
    return r->user_username;
}

int get_rideId(Ride r){
    return r->id;
}

int get_rideDriverId(Ride r){
    return r->driver_id;
}

int get_RideDistance(Ride r){
    return r->distance;
}

struct tm get_rideDate(Ride r){
    return r->date;
}

char *get_RideCity(Ride r){
    return r->city;
}

char *get_UserRide(Ride r){
    return r->user_username;
}

char *get_RideComment(Ride r){
    return r->comment;
}

int get_UserScore(Ride r){
    return r->score_user;
}

int get_DriverScore(Ride r){
    return r->score_driver;
}

double get_tip(Ride r){
    return r->tip;
}


/**
 * @brief Função que realiza o parsing de todos os ficheiros .csv.
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */ 
void rides(char* line,int num_lines[],char* path){

    char ride_path [BUFSIZ];// malloc(sizeof(path));
    strcpy(ride_path,path);
    strcat(ride_path,"/rides.csv");

    rides_table= g_hash_table_new(g_direct_hash, g_direct_equal);

    int count = 0;    
    FILE* rides_data = fopen(ride_path,"r");
    fgets(line,LINE_SIZE,rides_data);

    while(fgets(line,LINE_SIZE,rides_data)){ 
        count++;
        Ride temp_ride = malloc(sizeof(struct ride));
        parse_rides(line,temp_ride); // a funçao retorna cada struct Ride criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess
        ride_insert(temp_ride);
        free(temp_ride);

    }
    fclose(rides_data);
    num_lines[2] = count;
}
