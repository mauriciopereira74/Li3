#ifndef PARSER_H
#define PARSER_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

void debugUser(User u);
struct tm date_parse(char* line);
int accStatus_parse(char* line);
void parse_drivers(char* line, Driver d);
void parse_rides(char* line,Ride r);
void parse_users(char* line,User u);
void deleteFirstLine(char* buffer,char* filepath,char* flag);
User clone_user(User u);
Driver clone_driver(Driver d);
void parser(char* line);

#endif