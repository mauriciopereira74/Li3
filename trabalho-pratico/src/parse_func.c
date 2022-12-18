#include "../includes/parse_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glib.h>

/**
 * 
 * @brief Função que realiza o parsing dos campos representados por uma data
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

struct tm date_parse(char* line){
    int day,month,year;
    struct tm date;
    day     = atoi(strsep(&line,DATE_DELIM));
    month   = atoi(strsep(&line,DATE_DELIM));
    year    = atoi(strsep(&line,DATE_DELIM));

    date.tm_mday = day;
    date.tm_mon  = month;
    date.tm_year = year;

    return date; 
}

int ValidateCaps(char* field){
    int r = 1;
    if( field[0] == 'a' || field[0] == 'A' || 
        field[1] == 'c' || field[1] == 'C' || 
        field[2] == 't' || field[2] == 'T' || 
        field[3] == 'i' || field[3] == 'I' ||
        field[4] == 'v' || field[4] == 'V' ||
        field[5] == 'e' || field[5] == 'E');

    else if(field[0] == 'i' || field[0] == 'I' || 
            field[1] == 'n' || field[1] == 'N' || 
            field[2] == 'a' || field[2] == 'A' || 
            field[3] == 'c' || field[3] == 'C' || 
            field[4] == 't' || field[4] == 'T' || 
            field[5] == 'i' || field[5] == 'I' ||
            field[6] == 'v' || field[6] == 'V' ||
            field[7] == 'e' || field[7] == 'E');

    else if(field[0] == 'p' || field[0] == 'P' || 
            field[1] == 'r' || field[1] == 'R' || 
            field[2] == 'e' || field[2] == 'E' || 
            field[3] == 'm' || field[3] == 'M' || 
            field[4] == 'i' || field[4] == 'I' || 
            field[5] == 'u' || field[5] == 'U' ||
            field[6] == 'm' || field[6] == 'M');
    
    else if(field[0] == 'g' || field[0] == 'G' || 
            field[1] == 'r' || field[1] == 'R' || 
            field[2] == 'e' || field[2] == 'E' || 
            field[3] == 'e' || field[3] == 'E' || 
            field[4] == 'n' || field[4] == 'N');
    
    else if(field[0] == 'b' || field[0] == 'B' || 
            field[1] == 'a' || field[1] == 'A' || 
            field[2] == 's' || field[2] == 'S' || 
            field[3] == 'i' || field[3] == 'I' || 
            field[4] == 'c' || field[4] == 'C');

    else{
        r = 0;
    }
    return r;

}
int validateEnumTypes(char* field){
    int r = 1;
    if(strlen(field) == 6 && ValidateCaps(field) == 1);
    else if(strlen(field) == 8 && ValidateCaps(field) == 1);
    else if(strlen(field) == 7 && ValidateCaps(field) == 1);
    else if(strlen(field) == 5 && ValidateCaps(field) == 1);
    else{
        r = 0;
    }
    return r;
}

int validateStrFields(char* field){
    int r = 1;
    if (strlen(field) == 0){
        r = 0;
    }
    return r;
}

