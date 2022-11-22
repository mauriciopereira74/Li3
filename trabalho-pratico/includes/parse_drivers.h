#ifndef PARSE_DRIVERS_H
#define PARSE_DRIVERS_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"


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
void parse_drivers (char* line, Driver d);
Driver clone_driver(Driver d);
void parser_drivers(char* line,int num_lines[],char* path);


int get_driverId(Driver d);
char *get_licensePlate(Driver d);
char *get_driverName(Driver d);
char *get_driverCity(Driver d);
char *get_driverStatus(Driver d);
struct tm get_driverBirth(Driver d);
char *get_driverGender(Driver d);
char *get_Class(Driver d);
struct tm get_driverCreated(Driver d);

#endif

