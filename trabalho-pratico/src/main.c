#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/interpreter.h"
#include "../includes/profile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>

#include <glib.h>

int main(int argc, char *argv[]){

    if (argc == 0){
        printf("Path invalida\n");
    }
    else{
    int num_lines[3];

    char* line = malloc(sizeof(char) * LINE_SIZE);
    
    command_interpreter(line,num_lines,argv[1],argv[2]);
    return 0;
    }
}