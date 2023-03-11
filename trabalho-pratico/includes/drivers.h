#ifndef DRIVERS_H
#define DRIVERS_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

#include <glib.h>


/**
 * @brief Types of Car Classes.
 */

enum Class { basic,
             green,
             premium };

/**
 * @brief Types of Driver elements.
 */
typedef struct driver *Driver;


void debugDriver(Driver d);
int parse_drivers (char* line, Driver d);
Driver clone_driver(Driver d);
void driver_insert(GHashTable *drivers_table,Driver d);
int driver_check(GHashTable *drivers_table,int id);
struct driver *get_driverStruct(GHashTable *drivers_table,int id);
int get_driverId(Driver d);
char *get_licensePlate(Driver d);
char *get_driverName(Driver d);
char *get_driverCity(Driver d);
char *get_driverStatus(Driver d);
struct tm get_driverBirth(Driver d);
char *get_driverGender(Driver d);
char *get_Class(Driver d);
struct tm get_driverCreateTime(Driver d);
GHashTable *drivers(char* line,int num_lines[],char* path);
int validateIdDriver(char *field,Driver d);
double get_driverTotalAuferido(Driver d);
int get_driverNumViagens(Driver d);
double get_driverAvalTotal(Driver d);
double get_driverAvalMedia(Driver d);
double get_driverTotalAuferido(Driver d);
struct tm get_driverLastRide(Driver d);
void set_driverInfo(Driver d, double avaliacao,double auferido,struct tm lastRide);
void hashToListDriver(gpointer key, gpointer value, gpointer list);
#endif

