#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/list.h"
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

int validateDateDriver(char* field, Driver d, int N){
    int r = 1;
    int day,mon,year;
    int date_format = sscanf(field,"%d/%d/%d",&day,&mon,&year);
    if(date_format != 3 && 1 > day && day > 31 && 1 > mon && mon > 12 && 1 > year && year > 2022 && strlen(field) != 10 && (N != 1 || N != 2)){
        r = 0;
    }
    else{
        if(N == 1){
            d->birth_date.tm_mday = day;
            d->birth_date.tm_mon = mon;
            d->birth_date.tm_year = year;
        }
        else if(N == 2){
            d->created_time.tm_mday = day;
            d->created_time.tm_mon = mon;
            d->created_time.tm_year = year;
        }
    }
    return r;
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

/**
 * 
 * @brief Fun????o que realiza o parsing do ficheiro drivers.csv
 * 
 * @param line apontador para um espa??o em mem??ria onde ser?? guardada a string(linha)
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

    if (validateIdDriver(id,d) == 0 || validateStrFields(d->name) == 0 || 
        validateStrFields(d->gender) == 0  || validateStrFields(d->license_plate) == 0 || validateStrFields(d->city) == 0||
        validateDateDriver(birth_date,d,1) == 0 || validateDateDriver(created_time,d,2) == 0 || validateEnumTypes(d->Acc_Status) == 0 ||
        validateEnumTypes(d->Class) == 0){ // unfinished
        free(d);
        r = 0;
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

/**
 * @brief Fun????o que realiza o parsing de todos os ficheiros .csv.
 * 
 * @param line apontador para um espa??o em mem??ria onde ser?? guardada a string(linha)
 * 
 */ 
GHashTable *drivers(char* line,int num_lines[],char* path){

    char driver_path [BUFSIZ];//= malloc(sizeof(path));
    strcpy(driver_path,path);
    strcat(driver_path,"/drivers.csv");

    GHashTable *drivers_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    //struct list *driversRate[1500];

    int count = 0;
    FILE* drivers_data = fopen(driver_path,"r");
    fgets(line,LINE_SIZE,drivers_data);
    
    while(fgets(line,LINE_SIZE,drivers_data)){
        count++;
        Driver temp_driver = malloc(sizeof(struct driver));// a fun??ao retorna cada struct User criada por isso a importa??ao para a hashtable deve ser feita dentro de cada ciclo while i guess
        int is_driver_inserted = parse_drivers(line,temp_driver);
        if(is_driver_inserted == 1){
            driver_insert(drivers_table,temp_driver);
            free(temp_driver);
        }
/* 
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
            printf("%d %s %f\n",get_ListDriverID(driversRate[k]),get_ListDriverName(driversRate[k]),get_ListAvaliacaoMedia(driversRate[k]));
            k++;
            */
    }
    fclose(drivers_data);
    num_lines[1] = count;

    return drivers_table;
}


