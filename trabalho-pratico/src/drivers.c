#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/parse_func.h"
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

    double avaliacao_total;
    int n_viagens;
    double avaliacao_media;
    double total_auferido;
    struct tm lastride;
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
    printf("AVAL TOTAL: %f;\n",d->avaliacao_total);
    printf("N viagens: %d;\n",d->n_viagens);
    printf("Last Ride: %d/%d/%d; ",d->lastride.tm_mday,d->lastride.tm_mon,d->lastride.tm_year);

    
}


int validateIdDriver(char *field,Driver d) {
    int r = 1;
	char *p = field;
	if (p[0] == '\0' || p[0] == '-')
		r = 0;
	while (*p)
	{
		if (*p < '0' || *p > '9')	
			r = 0;
		p++;
	}

    if(r != 0){
        d->id = atoi(field);
    }
	return r;
}

void insert_birthdateDriver(Driver d, char* date){
    int day,mon,year;

    day= atoi(strsep(&date,"/"));
    mon= atoi(strsep(&date,"/"));
    year=atoi(strsep(&date,"\0"));

    d->birth_date.tm_mday = day;
    d->birth_date.tm_mon  = mon;
    d->birth_date.tm_year = year;

}

void insert_createddateDriver(Driver d, char* date){
    int day,mon,year;
    day= atoi(strsep(&date,"/"));
    mon= atoi(strsep(&date,"/"));
    year=atoi(strsep(&date,"\0"));

    d->created_time.tm_mday = day;
    d->created_time.tm_mon  = mon;
    d->created_time.tm_year = year;

}

/**
 * 
 * @brief Função que realiza o parsing do ficheiro drivers.csv
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

int parse_drivers (char* line, Driver d){
    int r = 1;
    char* birth_date, *created_time, *id;

    id                  = strdup(strsep(&line,FILE_CSV_DELIM));
    d->name             = strdup(strsep(&line,FILE_CSV_DELIM));
    birth_date          = strdup(strsep(&line,FILE_CSV_DELIM));
    d->gender           = strdup(strsep(&line,FILE_CSV_DELIM));
    d->Class            = strdup(strsep(&line,FILE_CSV_DELIM));
    d->license_plate    = strdup(strsep(&line,FILE_CSV_DELIM));
    d->city             = strdup(strsep(&line,FILE_CSV_DELIM));
    created_time        = strdup(strsep(&line,FILE_CSV_DELIM));
    d->Acc_Status       = strdup(strsep(&line,FILE_CSV_DELIM));
    d->avaliacao_total  = 0;
    d->n_viagens        = 0;
    d->avaliacao_media  = 0;

    lowercase(d->Class);
    lowercase(d->Acc_Status);
    
    if (validateIdDriver(id,d) == 0 || validateStrFields(d->name) == 0 || 
        validateStrFields(d->gender) == 0  || validateStrFields(d->license_plate) == 0 || validateStrFields(d->city) == 0||
        check_date_format(birth_date) == 0 || check_date_format(created_time) == 0 || 
        (strcmp(d->Acc_Status,"active") != 0 && strcmp(d->Acc_Status,"inactive") != 0) ||
        (strcmp(d->Class,"premium") != 0 && strcmp(d->Class,"green") != 0 && strcmp(d->Class,"basic") != 0)){ 
        
        r = 0;
    }
    else{
        insert_birthdateDriver(d,birth_date);
        insert_createddateDriver(d,created_time);
    }
    return r;
}

Driver clone_driver(Driver d){
    Driver aux = malloc(sizeof(struct driver));
    memcpy(aux,d,sizeof(struct driver));
    return aux;
}

void driver_insert(GHashTable *drivers_table, Driver d){
    g_hash_table_insert(drivers_table,GINT_TO_POINTER(get_driverId(d)),clone_driver(d));
}

int driver_check(GHashTable *drivers_table,int id){
    if (g_hash_table_contains(drivers_table,GINT_TO_POINTER(id))) return 1;
    else return 0;
}

struct driver *get_driverStruct(GHashTable *drivers_table,int id){
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

double get_driverAvalTotal(Driver d){
    return d->avaliacao_total;
}

double get_driverAvalMedia(Driver d){
    return d->avaliacao_media;
}

int get_driverNumViagens(Driver d){
    return d->n_viagens;
}

double get_driverTotalAuferido(Driver d){
    return d->total_auferido;
}

struct tm get_driverLastRide(Driver d){
    return d->lastride;
}

void set_driverInfo(Driver d, double avaliacao,double auferido,struct tm lastRide){
    if(get_driverNumViagens(d)==0){
        d->avaliacao_total=d->avaliacao_total+avaliacao;
        d->total_auferido=d->total_auferido+auferido;
        d->lastride=lastRide;
        d->n_viagens=1;
        d->avaliacao_media=d->avaliacao_total/(double)d->n_viagens;
    }
    else {
        d->avaliacao_total=d->avaliacao_total+avaliacao;
        d->total_auferido=d->total_auferido+auferido;
        d->lastride=lastRide;
        d->n_viagens++;
        d->avaliacao_media=d->avaliacao_total/(double)d->n_viagens;
    }
}

void hashToListDriver(gpointer key, gpointer value, gpointer list){
    g_array_append_val(list,*(struct driver*) value);
}
/**
 * @brief Função que realiza o parsing de todos os ficheiros .csv.
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */ 
GHashTable *drivers(char* line,int num_lines[],char* path){

    char driver_path [BUFSIZ];//= malloc(sizeof(path));
    strcpy(driver_path,path);
    strcat(driver_path,"/drivers.csv");

    GHashTable *drivers_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    int count = 0;
    FILE* drivers_data = fopen(driver_path,"r");
    fgets(line,LINE_SIZE,drivers_data);
    
    while(fgets(line,LINE_SIZE,drivers_data)){
        count++;
        Driver temp_driver = malloc(sizeof(struct driver));// a funçao retorna cada struct User criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess
        int is_driver_valid = parse_drivers(line,temp_driver);
        if (is_driver_valid == 1){
            driver_insert(drivers_table,temp_driver);
            free(temp_driver);
        }
    }
    fclose(drivers_data);
    num_lines[1] = count;

    return drivers_table;
}


