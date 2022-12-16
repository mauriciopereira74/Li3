#ifndef RIDES_H
#define RIDES_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

#include <glib.h>

typedef struct ride *Ride;

void debugRide(Ride r);
void parse_rides (char* line, Ride r);
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
int get_DriverScore(Ride r);
double get_tip(Ride r);
GHashTable *rides(char* line,int num_lines[],char* path);


#endif

