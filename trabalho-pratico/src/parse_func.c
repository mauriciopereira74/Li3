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


