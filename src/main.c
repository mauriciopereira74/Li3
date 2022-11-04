#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>


int main(){
    char* line = malloc(sizeof(char) * LINE_SIZE);
    command_interpreter(line);
    return 0;
}