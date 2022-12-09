#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/list.h"
#include "../includes/parse_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glib.h>

GHashTable *drivers_table;

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

void driver_insert(Driver d){
    g_hash_table_insert(drivers_table,GINT_TO_POINTER(get_driverId(d)),clone_driver(d));
}

int driver_check(int id){
    if (g_hash_table_contains(drivers_table,GINT_TO_POINTER(id))) return 1;
    else return 0;
}

struct driver *get_driverStruct(int id){
    struct driver *temp = g_hash_table_lookup(drivers_table,GINT_TO_POINTER(id));
    return temp;
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

struct tm get_driverCreateTime(Driver d){
    return d->created_time;
}

/**
 * @brief Função que realiza o parsing de todos os ficheiros .csv.
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */ 
void drivers(char* line,int num_lines[],char* path){

    char driver_path [BUFSIZ];//= malloc(sizeof(path));
    strcpy(driver_path,path);
    strcat(driver_path,"/drivers.csv");

    drivers_table= g_hash_table_new(g_direct_hash, g_direct_equal);
    struct list *driversRate[1500];

    int count = 0;
    FILE* drivers_data = fopen(driver_path,"r");
    fgets(line,LINE_SIZE,drivers_data);
    while(fgets(line,LINE_SIZE,drivers_data)){
        count++;
        Driver temp_driver = malloc(sizeof(struct driver));// a funçao retorna cada struct User criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess
        parse_drivers(line,temp_driver);
        driver_insert(temp_driver);

            int avaliacao_total=0,n_viagens=0;
                for(int i=1;i<=num_lines[2];i++){
                    struct ride *r= get_rideStruct(i);
                    if(get_rideDriverId(r) == get_driverId(temp_driver)){
                        avaliacao_total= avaliacao_total + get_DriverScore(r);
                        n_viagens++;
                    }
                }
            double avaliacao_media=avaliacao_total/(double)n_viagens;
            struct list *l = malloc(sizeof(List));
            set_ListDriverID(l,get_driverId(temp_driver));
            set_ListDriverName(l,get_driverName(temp_driver));
            set_ListAvaliacaoMedia(l,avaliacao_media);
            int k=0;
            driversRate[k]=l;
            //printf("%d %s %f\n",get_ListDriverID(driversRate[k]),get_ListDriverName(driversRate[k]),get_ListAvaliacaoMedia(driversRate[k]));
            k++;

        free(temp_driver);
    }
    fclose(drivers_data);
    num_lines[1] = count;
}


