#ifndef PARSER_H
#define PARSER_H

#define LINE_SIZE 1000
#define FILE_CSV_DELIM ";\n"
#define DATE_DELIM     "/\n"

struct tm date_parse(char* line);
int validateStrFields(char* field);
int validateEnumTypes(char* field);
int ValidateCaps(char* field);
#endif