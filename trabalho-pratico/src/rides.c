#include "../includes/rides.h"
#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/parse_func.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glib.h>

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
    
    double preco_viagem;
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

int validateDateRide(char* field, Ride r){
    int res = 1;
    int day,mon,year;
    int date_format = sscanf(field,"%d/%d/%d",&day,&mon,&year);
    if(strlen(field) == 10){
        if(field[2] == '/'){ 
            if(field[5] == '/'){
                if(field[10] == '\0'){
                    if(date_format != 3 && 1 > day && day > 31 && 1 > mon && mon > 12 && 1 > year && year > 2022){
                        res = 0;
                    }
                    else{
                        r->date.tm_mday = day;
                        r->date.tm_mon = mon;
                        r->date.tm_year = year;
                    }
                }
            }
        }
    }  
    return res;
}

/**
 * 
 * @brief Função que realiza o parsing do ficheiro rides.csv
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

void insert_ride_id(Ride r,char* id){
    r->id = atoi(id);
}

void insert_ride_date(Ride r, char* date){
    int day,mon,year;

    day= atoi(strsep(&date,"/"));
    mon= atoi(strsep(&date,"/"));
    year=atoi(strsep(&date,"\0"));

    r->date.tm_mday = day;
    r->date.tm_mon  = mon;
    r->date.tm_year = year;

}

void insert_ride_driverid(Ride r, char* driver_id){
    r->driver_id = atoi(driver_id);
}

void insert_ride_scoredriver(Ride r, char* score_driver){
    r->score_driver = atoi(score_driver);
}

void insert_ride_scoreuser(Ride r, char* score_user){
    r->score_user = atoi(score_user);
}

void insert_ride_tip(Ride r,char* tip){
    r->tip = atof(tip);
}

void insert_ride_distance(Ride r, char* distance){
    r->distance = atoi(distance);
}

int check_fieldsize(char* field){
    int r = 1;
    if (strlen(field) == 0) r = 0;

    return r;
}

int check_nums(char* field){
    int r = 1;
    int value_i;
    int num_dig;
    int result_i = sscanf(field, "%d", &value_i);
    if (result_i != 1){
       r = 0;
    }
    else{
        num_dig = (int)log10(value_i) + 1;
        if(strlen(field) != num_dig || value_i < 0) r = 0;
    }

    return r;
}

int check_tip(char* field){
    int r = 1;
    float number;
    int result = sscanf(field, "%f", &number);
    if (result != 1 || number <= 0.0 || isnan(number)) {
        r = 0;
    }
    return r;
}

int parse_rides (char* line, Ride r){
    int res = 1;
    char *date, *id,*driver_id, *distance,*score_driver,*score_user,*tip;

    id                  = strdup(strsep(&line,FILE_CSV_DELIM));
    date                = strdup(strsep(&line,FILE_CSV_DELIM));
    driver_id           = strdup(strsep(&line,FILE_CSV_DELIM));
    r->user_username    = strdup(strsep(&line,FILE_CSV_DELIM));
    r->city             = strdup(strsep(&line,FILE_CSV_DELIM));
    distance            = strdup(strsep(&line,FILE_CSV_DELIM)); //could be int instead of float
    score_user          = strdup(strsep(&line,FILE_CSV_DELIM));
    score_driver        = strdup(strsep(&line,FILE_CSV_DELIM));
    tip                 = strdup(strsep(&line,FILE_CSV_DELIM));
    r->comment          = strdup(strsep(&line,FILE_CSV_DELIM));
    r->preco_viagem     = 0;
    if (validateStrFields(id) == 0 || check_date_format(date) == 0 || 
        validateStrFields(driver_id) == 0  || validateStrFields(r->user_username) == 0 || validateStrFields(r->city) == 0||
        check_nums(distance) == 0 || check_nums(score_user) == 0 || check_nums(score_driver) == 0 ||
        check_tip(tip) == 0// unfinished
        ){
        free(r);
        res = 0;
    }
    else{
        insert_ride_id(r,id);
        insert_ride_driverid(r,driver_id);
        insert_ride_date(r,date);
        insert_ride_scoredriver(r,score_driver);
        insert_ride_scoreuser(r,score_user);
        insert_ride_tip(r,tip);
        insert_ride_distance(r,distance);
    }
    return res;
}


Ride clone_ride(Ride r){
    Ride aux=malloc(sizeof(struct ride));
    memcpy(aux,r,sizeof(struct ride));
    return aux;
}

void ride_insert(GHashTable *rides_table,Ride r){
    g_hash_table_insert(rides_table,GINT_TO_POINTER(get_rideId(r)),clone_ride(r));
}

int ride_check(GHashTable *rides_table, char *id){
    if (g_hash_table_lookup(rides_table, id)) return 1;
    else return 0;
}

struct ride *get_rideStruct(GHashTable *rides_table, int id){
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

void set_rideInfo(Ride r,double preco_viagem){
    r->preco_viagem=r->preco_viagem+preco_viagem;
}


/**
 * @brief Função que realiza o parsing de todos os ficheiros .csv.
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */ 
GHashTable *rides(char* line,int num_lines[],char* path,GHashTable *drivers_table,GHashTable *users_table){

    char ride_path [BUFSIZ];// malloc(sizeof(path));
    strcpy(ride_path,path);
    strcat(ride_path,"/rides.csv");

    GHashTable *rides_table = g_hash_table_new(g_direct_hash, g_direct_equal);

    int count = 0;   
    FILE* rides_data = fopen(ride_path,"r");
    fgets(line,LINE_SIZE,rides_data);

    Ride temp_ride = malloc(sizeof(struct ride));

    while(fgets(line,LINE_SIZE,rides_data)){ 
        count++;
        Ride temp_ride = malloc(sizeof(struct ride));
        int is_valid_ride = parse_rides(line,temp_ride); // a funçao retorna cada struct Ride criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess  
        if(is_valid_ride == 1){
        ride_insert(rides_table,temp_ride);
        
        // DRIVER THINGS
            struct driver *d;
            if((d = get_driverStruct(drivers_table,get_rideDriverId(temp_ride))) != NULL){
                double total_auferido=0;

                if(strcmp(get_Class(d),"basic")==0) total_auferido += 3.25 + 0.62* (double)get_RideDistance(temp_ride) + get_tip(temp_ride);
                else if(strcmp(get_Class(d),"green")==0) total_auferido += 4.00+ 0.79* (double)get_RideDistance(temp_ride) + get_tip(temp_ride);
                else total_auferido += 5.20+ 0.94* (double)get_RideDistance(temp_ride) + get_tip(temp_ride);
                
            set_driverInfo(d,get_DriverScore(temp_ride),total_auferido,get_rideDate(temp_ride));
            }
            
            // USER THINGS
            struct user *u;
            if((u = get_userStruct(users_table,get_RideUsername(temp_ride)))!=NULL){
                double total_gasto=0;
                struct driver *d= get_driverStruct(drivers_table,get_rideDriverId(temp_ride));
                if(strcmp(get_Class(d),"basic")==0) total_gasto += 3.25 + 0.62 *get_RideDistance(temp_ride) + get_tip(temp_ride);
                else if(strcmp(get_Class(d),"green")==0) total_gasto +=  4.00+ 0.79*get_RideDistance(temp_ride) + get_tip (temp_ride);
                else total_gasto += 5.20+ 0.94 * get_RideDistance(temp_ride) + get_tip (temp_ride);
                
                set_userInfo(u,get_UserScore(temp_ride),total_gasto,get_RideDistance(temp_ride),get_rideDate(temp_ride));
            }

            // RIDE THINGS
            double preco_viagem=0;
            d = (get_driverStruct(drivers_table,get_rideDriverId(temp_ride)));

                if(strcmp(get_Class(d),"basic")==0) preco_viagem= preco_viagem + 3.25 + 0.62*get_RideDistance(temp_ride);
                else if(strcmp(get_Class(d),"green")==0) preco_viagem= preco_viagem +4.00+ 0.79*get_RideDistance(temp_ride);
                else preco_viagem= preco_viagem + 5.20+ 0.94*get_RideDistance(temp_ride);
                
                set_rideInfo(temp_ride,preco_viagem);
        }
    }
    free(temp_ride);
    fclose(rides_data);
    num_lines[2] = count;

    return rides_table;
}
