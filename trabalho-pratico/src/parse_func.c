#include "../includes/parse_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <glib.h>


int check_date_format(char *date){
    int day, mon, year;
    if (sscanf(date, "%d/%d/%d", &day, &mon, &year) != 3) {
        return 0;  // not enough values were extracted
    }
    if (day < 1 || day > 31) {
        return 0;  // invalid day
    }
    if (mon < 1 || mon > 12) {
        return 0;  // invalid month
    }
    if (year < 0) {
        return 0;  // invalid year
    }
    return 1;  // date is formatted correctly
}

void lowercase(char *field){ // not working properly
    for ( ; *field; ++field) *field = tolower(*field);
}

int validateStrFields(char* field){
    int r = 1;
    if (strlen(field) == 0){
        r = 0;
    }
    return r;
}

