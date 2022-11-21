#ifndef HASHTABLES_H
#define HASHTABLES_H

#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"

#include <glib.h>

GHashTable *users_table;
GHashTable *drivers_table;
GHashTable *rides_table;

void user_insert( User user);
void driver_insert(Driver driver);
void ride_insert(Ride ride);

int user_check(char *name);
int driver_check(char *id);
int ride_check(char *id);

char * get_username(User u);
char *get_name(User u);
char *get_userGender(User u);
struct tm get_userBirth(User u);
struct tm get_userCreateTime(User u);
char *get_userPayMethod(User u);
char *get_userStatus(User u);

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