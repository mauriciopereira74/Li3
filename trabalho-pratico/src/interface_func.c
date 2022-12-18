#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../includes/interface_func.h"

void print_boxed(char *content){
    char *tok = strtok(strdup(content), "\n");
    int max_length = 0; int current = 0;

    while(tok != NULL) 
    {
        current = strlen(tok);

        if (max_length < current) max_length = current;
        tok = strtok(NULL, "\n");
    }

    printf("╭");
    for (int i = 0; i < max_length + 2; i++) printf("─");
    printf("╮\n");

    char *token = strtok(strdup(content), "\n");
    int aux = 0;

    while(token != NULL) 
    {
        printf("│ ");
        printf("%s", token);

        int white_space = max_length - strlen(token);

        if (aux == 0)
            for (int j = 0; j < white_space + 1; j++) putchar(' ');
        else
            for (int j = 0; j < white_space + 1; j++) putchar(' ');

        printf("│\n");

        token = strtok(NULL, "\n");
        aux++;	
    }

    printf("╰");
    for (int i = 0; i < max_length + 2; i++) printf("─");
    printf("╯");
}

void clear_screen(){
    printf("\e[1;1H\e[2J");
}

void print_list_item(char *list_number, char *content){
    print_boxed(list_number);
    printf("\033[%dA\033[%dL", 0, -1);
    printf(" %s\n", content);
    printf("\033[%dB", 1);
}
