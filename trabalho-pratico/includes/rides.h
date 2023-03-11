#ifndef RIDES_H
#define RIDES_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

#include <glib.h>

typedef struct ride *Ride;

void debugRide(Ride r);
int parse_rides (char* line, Ride r);
int check_fieldsize(char* field);
int check_nums(char* field);
int check_tip(char* field);
void insert_ride_distance(Ride r, char* distance);
void insert_ride_tip(Ride r,char* tip);
void insert_ride_scoreuser(Ride r, char* score_user);
void insert_ride_scoredriver(Ride r, char* score_driver);
void insert_ride_driverid(Ride r, char* driver_id);
void insert_ride_date(Ride r, char* date);
void insert_ride_id(Ride r,char* id);
Ride clone_ride(Ride r);
void ride_insert(GHashTable *rides_table,Ride r);
int ride_check(GHashTable *rides_table,char *id);
struct ride *get_rideStruct(GHashTable *rides_table,int id);
char *get_RideUsername(Ride r);
int get_rideId(Ride r);
int get_rideDriverId(Ride r);
int get_RideDistance(Ride r);
struct tm get_rideDate(Ride r);
char *get_RideCity(Ride r);
char *get_UserRide(Ride r);
char *get_RideComment(Ride r);
int get_UserScore(Ride r);
void set_q8(Ride r);
int get_q8(Ride r);
int get_DriverScore(Ride r);
double get_tip(Ride r);
GHashTable *rides(char* line,int num_lines[],char* path,GHashTable *drivers_table,GHashTable *users_table);


#endif

