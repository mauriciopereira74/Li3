#ifndef PARSER_H
#define PARSER_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

int validateStrFields(char* field);
void lowercase(char *field);
int check_date_format(char *date);
#endif