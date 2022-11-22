#include "../includes/hashtables.h"
#include "../includes/parse_drivers.h"
#include "../includes/parser_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glib.h>


struct driver
{
    int id; /**< string that represents the id number of a driver. */

    char *license_plate; /**< long int that represents the license plate number of the driver. */

    char *name, /**< string that represents the name of the driver. */
         *city, /**< string that represents the city of the driver. */
         *Acc_Status; /**< string to check the driver account status. */

    struct tm birth_date ; /**< struct that represents the driver's date of birth. */

    char* gender; /**< char that represents the gender of the driver. */

    char* Class; /**< string that represents the car classe. */

    struct tm created_time; /**< struct that represents the datetime on which the driver account was created. */
    
};

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

Driver clone_driver(Driver d){
    Driver aux = malloc(sizeof(struct driver));
    memcpy(aux,d,sizeof(struct driver));
    return aux;
}


/**
 * @brief Função que realiza o parsing de todos os ficheiros .csv.
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */ 
void parser_drivers(char* line,int num_lines[],char* path){

    char driver_path [BUFSIZ];//= malloc(sizeof(path));
    strcpy(driver_path,path);
    strcat(driver_path,"/drivers.csv");

    int count = 0;
    FILE* drivers_data = fopen(driver_path,"r");
    fgets(line,LINE_SIZE,drivers_data);
    while(fgets(line,LINE_SIZE,drivers_data)){
        count++;
        Driver temp_driver = malloc(sizeof(struct driver));// a funçao retorna cada struct User criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess
        parse_drivers(line,temp_driver);
        driver_insert(temp_driver);
        free(temp_driver);
    }
    fclose(drivers_data);
    num_lines[1] = count;
}

int get_driverId(Driver d){
    return d->id;
}

char *get_licensePlate(Driver d){
    return d->license_plate;
}

char *get_driverName(Driver d){
    return d->name;
}

char *get_driverCity(Driver d){
    return d->city;
}


char *get_driverStatus(Driver d){
    return d->Acc_Status;
}

struct tm get_driverBirth(Driver d){
    return d->birth_date;
}

char *get_driverGender(Driver d){
    return d->gender;
}

char *get_Class(Driver d){
    return d->Class;
}

struct tm get_driverCreated(Driver d){
    return d->created_time;
}