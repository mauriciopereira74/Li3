#ifndef USERS_H
#define USERS_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

#include <glib.h>


/**
 * @brief Types of Account Status.
 */

enum Acc_Status { Active,
                  Inactive };

typedef struct user *User;

void debugUser(User u);
int parse_users(char* line,User u);
User clone_user(User u);
void user_insert(GHashTable *users_table,User u);
int user_check(GHashTable *users_table,char *name);
struct user *get_userStruct(GHashTable *users_table,char *name);
char * get_username(User u);
char *get_name(User u);
char *get_userGender(User u);
struct tm get_userBirth(User u);
struct tm get_userCreateTime(User u);
char *get_userPayMethod(User u);
char *get_userStatus(User u);
GHashTable *users(char* line,int num_lines[],char* path);
int validateDateUser(char* field,User u,int N);

#endif