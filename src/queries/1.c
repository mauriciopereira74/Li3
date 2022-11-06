#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/interpreter.h"

int age(struct tm birth_date){
    time_t rawtime;
    time(&rawtime);
    struct tm *info=localtime(&rawtime);

    int present_day= info->tm_mday;
    int present_month=info->tm_mon;
    int present_year= info->tm_year;

    int birth_day= birth_date.tm_mday;
    int birth_month= birth_date.tm_mon;
    int birth_year= birth_date.tm_year;

    int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    if (birth_day > present_day) {
      present_day = present_day + month[birth_month - 1];
      present_month = present_month - 1;
   }

   if (birth_month > present_month) {
      present_year = present_year - 1;
      present_month = present_month + 12;
   }

   int final_date = present_day - birth_day;
   int final_month = present_month - birth_month;
   int final_year = present_year - birth_year;

   return final_year;
}
