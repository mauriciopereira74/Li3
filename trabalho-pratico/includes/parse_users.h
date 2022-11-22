#ifndef PARSE_USERS_H
#define PARSE_USERS_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

/**
 * @brief Types of Account Status.
 */

enum Acc_Status { Active,
                  Inactive };

typedef struct user *User;

void debugUser(User u);
void parse_users(char* line,User u);
User clone_user(User u);
void parser_users(char* line,int num_lines[],char* path);

char * get_username(User u);
char *get_name(User u);
char *get_userGender(User u);
struct tm get_userBirth(User u);
struct tm get_userCreateTime(User u);
char *get_userPayMethod(User u);
char *get_userStatus(User u);

#endif