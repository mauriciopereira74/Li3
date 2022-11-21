#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/hashtables.h"

#include <stdio.h>
#include <glib.h>

GHashTable *users_table;
GHashTable *drivers_table;
GHashTable *rides_table;

void user_insert(User user){
    g_hash_table_insert(users_table,user->username,clone_user(user));
}

void driver_insert(Driver driver){
    g_hash_table_insert(drivers_table,GINT_TO_POINTER(driver->id),clone_driver(driver));
}

void ride_insert(Ride ride){
    g_hash_table_insert(rides_table,GINT_TO_POINTER(ride->id),clone_ride(ride));
}

int user_check(char *name){
    if (g_hash_table_lookup(users_table,name)) return 1;
    else return 0;
}

int driver_check(char *id){
    if (g_hash_table_lookup(drivers_table,id)) return 1;
    else return 0;
}

int ride_check(char *id){
    if (g_hash_table_lookup(rides_table, id)) return 1;
    else return 0;
}

char * get_username(User u){
    return u->username;
}

char *get_name(User u){
    return u->name;
}

char *get_userGender(User u){
    return u->gender;
}

struct tm get_userBirth(User u){
    return u->birth_date;
}
struct tm get_userCreateTime(User u){
    return u->created_time;
}

char *get_userPayMethod(User u){
    return u->pay_method;
}

char *get_userStatus(User u){
    return u->Acc_Status;
}

char *get_RideUsername(Ride r){
    return r->user_username;
}

int get_rideId(Ride r){
    return r->id;
}

int get_rideDriverId(Ride r){
    return r->driver_id;
}

int get_RideDistance(Ride r){
    return r->distance;
}

struct tm get_rideDate(Ride r){
    return r->date;
}

char *get_RideCity(Ride r){
    return r->city;
}

char *get_UserRide(Ride r){
    return r->user_username;
}

char *get_RideComment(Ride r){
    return r->comment;
}

int get_UserScore(Ride r){
    return r->score_user;
}

int get_DriverScore(Ride r){
    return r->score_driver;
}

double get_tip(Ride r){
    return r->tip;
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