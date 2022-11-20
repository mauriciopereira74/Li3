#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/hashtables.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glib.h>


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

void debugDriver(Driver d){
     
    printf("ID: %i; ",d->id);
    printf("Name: %s; ",d->name);
    printf("Birth Date: %d/%d/%d; ",d->birth_date.tm_mday,d->birth_date.tm_mon,d->birth_date.tm_year);
    printf("Gender: %s; ",d->gender);
    printf("Car Class: %s; ",d->Class);
    printf("License Plate %s; ",d->license_plate);
    printf("City: %s; ",d->city);
    printf("Account Creation: %d/%d/%d; ",d->created_time.tm_mday,d->created_time.tm_mon,d->created_time.tm_year);
    printf("Account Status: %s;\n",d->Acc_Status);

    
}

void debugUser(User u){
    
    printf("Username: %s; ",u->username);
    printf("Name: %s; ",u->name);
    printf("Gender: %s; ",u->gender);
    printf("Birth Date: %d/%d/%d; ",u->birth_date.tm_mday,u->birth_date.tm_mon,u->birth_date.tm_year);
    printf("Account Creation: %d/%d/%d; ",u->created_time.tm_mday,u->created_time.tm_mon,u->created_time.tm_year);
    printf("Pay Method: %s; ",u->pay_method);
    printf("Account Status: %s\n ",u->Acc_Status);
}

/**
 * 
 * @brief Função que realiza o parsing dos campos representados por uma data
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

struct tm date_parse(char* line){
    int day,month,year;
    struct tm date;
    day     = atoi(strsep(&line,DATE_DELIM));
    month   = atoi(strsep(&line,DATE_DELIM));
    year    = atoi(strsep(&line,DATE_DELIM));

    date.tm_mday = day;
    date.tm_mon  = month;
    date.tm_year = year;

    return date; 
}


//NOT SURE SE VAMOS USAR ESTA (NOT FINISHED ANYWAY)
/**
 * 
 * @brief Função que realiza o parsing do campo account_status
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

int accStatus_parse(char* line){
    enum Acc_Status status;

    if (strcmp(line,"active") == 1){
        status = 0;
    }
    else{status = 1;}
return status;
}


/**
 * 
 * @brief Função que realiza o parsing do ficheiro drivers.csv
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

void parse_drivers (char* line, Driver d){
    d->id               = atoi(strdup(strsep(&line,FILE_CSV_DELIM)));
    d->name             = strdup(strsep(&line,FILE_CSV_DELIM));
    d->birth_date       = date_parse(strdup(strsep(&line,FILE_CSV_DELIM)));
    d->gender           = strdup(strsep(&line,FILE_CSV_DELIM));
    d->Class            = strdup(strsep(&line,FILE_CSV_DELIM));
    d->license_plate    = strdup(strsep(&line,FILE_CSV_DELIM));
    d->city             = strdup(strsep(&line,FILE_CSV_DELIM));
    d->created_time     = date_parse(strdup(strsep(&line,FILE_CSV_DELIM)));
    d->Acc_Status       = strdup(strsep(&line,FILE_CSV_DELIM));

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


/**
 * 
 * @brief Função que realiza o parsing do ficheiro users.csv
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

void parse_users(char* line,User u){
   
    u->username         = strdup(strsep(&line,FILE_CSV_DELIM));
    u->name             = strdup(strsep(&line,FILE_CSV_DELIM));
    u->gender           = strdup(strsep(&line,FILE_CSV_DELIM));
    u->birth_date       = date_parse(strdup(strsep(&line,FILE_CSV_DELIM)));
    u->created_time     = date_parse(strdup(strsep(&line,FILE_CSV_DELIM)));
    u->pay_method       = strdup(strsep(&line,FILE_CSV_DELIM)); // could be type enum
    u->Acc_Status       = strdup(strsep(&line,FILE_CSV_DELIM));

}

User clone_user(User u){
    User aux = malloc(sizeof(struct user));
    memcpy(aux,u,sizeof(struct user));
    return aux;
}
Driver clone_driver(Driver d){
    Driver aux = malloc(sizeof(struct driver));
    memcpy(aux,d,sizeof(struct driver));
    return aux;
}

Ride clone_ride(Ride r){
    Ride aux=malloc(sizeof(struct ride));
    memcpy(aux,r,sizeof(struct ride));
    return aux;
}

/**
 * @brief Função que realiza o parsing de todos os ficheiros .csv.
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */ 
void parser(char* line,char* file_path,int num_lines[]){
    char* user_path = malloc(sizeof(file_path));
    char* driver_path = malloc(sizeof(file_path));
    char* rides_path = malloc(sizeof(file_path));

    strcpy(user_path,file_path);
    strcpy(driver_path,file_path);
    strcpy(rides_path,file_path);
    
    char* user_file = strcat(user_path,"/users.csv");
    char* driver_file = strcat(driver_path,"/drivers.csv");
    char* rides_file = strcat(rides_path,"/rides.csv");
    int count = 0;
    FILE* users_data = fopen(user_file,"r");
    
    fgets(line,LINE_SIZE,users_data);
    while(fgets(line,LINE_SIZE,users_data)){
        
        count++;
        User temp_user = malloc(sizeof(struct user));
        parse_users(line,temp_user); // a funçao retorna cada struct User criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess
        user_insert(temp_user);//user_insert(users_table,temp);
        free(temp_user);
    }
    fclose(users_data);
    free(line);
    num_lines[0] = count;
    count = 0;
    
    line = malloc(sizeof(char) * LINE_SIZE);
    
    FILE* drivers_data = fopen(driver_file,"r");
    fgets(line,LINE_SIZE,drivers_data);
    
    
    while(fgets(line,LINE_SIZE,drivers_data)){
        count++;
        Driver temp_driver = malloc(sizeof(struct driver));
        // a funçao retorna cada struct Driver criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess
        parse_drivers(line,temp_driver);
        driver_insert(temp_driver);
        free(temp_driver);

    }
    free(line);
    fclose(drivers_data);

    num_lines[1] = count;
    count = 0;

    line = malloc(sizeof(char) * LINE_SIZE);
    
    FILE* rides_data = fopen(rides_file,"r");
    fgets(line,LINE_SIZE,rides_data);

    while(fgets(line,LINE_SIZE,rides_data)){ 
        count++;
        Ride temp_ride = malloc(sizeof(struct ride));
        parse_rides(line,temp_ride); // a funçao retorna cada struct Ride criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess
        ride_insert(temp_ride);
        free(temp_ride);

    }
    free(line);
    fclose(rides_data);
    num_lines[2] = count;
    count = 0;
    
    free(user_file);
    free(rides_file);
    free(driver_file);
}

