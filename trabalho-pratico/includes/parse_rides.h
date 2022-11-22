#ifndef PARSE_RIDES_H
#define PARSE_RIDES_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

typedef struct ride *Ride;

void debugRide(Ride r);
void parse_rides (char* line, Ride r);
Ride clone_ride(Ride r);
void parser_rides(char* line,int num_lines[],char* path);

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

#endif

