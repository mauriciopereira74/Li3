#ifndef PARSER_H
#define PARSER_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

void debugUser(User u);
struct tm date_parse(char* line);
int accStatus_parse(char* line);
Driver parse_drivers(char* line);
Ride parse_rides(char* line);
User parse_users(char* line);
void deleteFirstLine(char* buffer,char* filepath,char* flag);
void parser(char* line);

#endif