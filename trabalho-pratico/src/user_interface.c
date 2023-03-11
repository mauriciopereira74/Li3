#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h> 
#include <stdlib.h>
#include <unistd.h>

#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/user_interface.h"
#include "../includes/interpreter.h"
#include "../includes/queries_itr.h"

#include <glib.h>

#define BUFFERSIZE 100

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

void print_queries(){

            printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈🮤 Queries 🮥 ┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\n");
            print_list_item("1", "Perfil de um utilizador ou de um condutor.");
            print_list_item("2", "Top N condutores com maior avaliação média.");
            print_list_item("3", "Top N utilizadores com maior distância viajada.");
            printf("┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈🮤 Página 1/3 🮥 ┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\n");
            printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈🮤 Queries 🮥 ┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\n");
            print_list_item("4", "Preço médio das viagens numa determinada cidade.");
            print_list_item("5", "Preço médio das viagens num dado intervalo de tempo.");
            print_list_item("6", "Distância média percorrida numa determinada cidade num dado intervalo de tempo.");
            printf("┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈🮤 Página 2/3 🮥 ┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\n");
            printf("\n┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈🮤 Queries 🮥 ┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\n");
            print_list_item("7", "Top N condutores numa determinada cidade.");
            print_list_item("8", "Viagens em que utilizador e o condutor são de um determinado género,e têm perfis com X ou mais anos.");
            print_list_item("9", "Viagens em que o passageiro deu gorjeta num determinado intervalo de tempo.");
            printf("┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈🮤 Página 3/3 🮥 ┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈\n");
            print_list_item("0", "Sair"); printf("\n");
            
}


void interface(char* line,int num_lines[],char* parserPath,char* path){

    char buffer[BUFFERSIZE];
    bool running = true;
    //int current_page = 1; int id = 0;

    GHashTable *users_table = users(line,num_lines,parserPath);
    GHashTable *drivers_table = drivers(line,num_lines,parserPath);
    GHashTable *rides_table = rides(line,num_lines,parserPath,drivers_table,users_table);

    while(running){
        clear_screen();
        print_boxed("Bem-vindo ao Projeto de LI3!\nPara comecar escolha a querie a ser executada, ou escreva '0' para sair.\n");
        printf("\n");
        print_queries();
        printf("\n🮤  Opcao 🮥 \n");
        getLine(buffer, BUFFERSIZE);
        int option; 
        if(sscanf(buffer, "%d", &option) != 1) continue;
        switch(option) {
            case 1:
                printf("Introduza o id do Utilizador/Condutor\n");
                char input[BUFFERSIZE];
                if (fgets(input,sizeof(input), stdin))
                querie1_itr(input,num_lines[2],users_table,drivers_table,rides_table);
                printf("\nPressione 'Enter' para continuar\n");
                char enter = 0;
                while (enter != '\r' && enter != '\n') { enter = getchar(); }
                break;
            case 2:
                printf("Introduza o N\n");
                if (fgets(input,sizeof(input), stdin))
                querie2_itr(input,num_lines[2],drivers_table);
                printf("\nPressione 'Enter' para continuar\n");
                enter = 0;
                while (enter != '\r' && enter != '\n') { enter = getchar(); }
                break;
            case 3:
                 printf("Introduza o N\n");
                if (fgets(input,sizeof(input), stdin))
                querie3_itr(input,num_lines[2],users_table);
                printf("\nPressione 'Enter' para continuar\n");
                enter = 0;
                while (enter != '\r' && enter != '\n') { enter = getchar(); }
                break;
            case 4:
                printf("Introduza a Cidade\n");
                if (fgets(input, sizeof(input), stdin))
                querie4_itr(input,num_lines[2],drivers_table,rides_table);
                printf("\nPressione 'Enter' para continuar\n");
                enter = 0;
                while (enter != '\r' && enter != '\n') { enter = getchar(); }
                break;
            case 5:
                printf("Introduza o intervalo de tempo\n");
                if (fgets(input,sizeof(input), stdin))
                querie5_itr(input,num_lines[2],drivers_table,rides_table);
                printf("\nPressione 'Enter' para continuar\n");
                enter = 0;
                while (enter != '\r' && enter != '\n') { enter = getchar(); }
                break;
            case 6:
                printf("Introduza a Cidade e o intervalo de tempo\n");
                if (fgets(input,sizeof(input), stdin))
                querie6_itr(input,num_lines[2],rides_table);
                printf("\nPressione 'Enter' para continuar\n");
                enter = 0;
                while (enter != '\r' && enter != '\n') { enter = getchar(); }
                break;
            case 7:
                printf("Introduza o N e a Cidade\n");
                if (fgets(input,sizeof(input), stdin))
                querie7_itr(input,num_lines[2],drivers_table,rides_table);
                printf("\nPressione 'Enter' para continuar\n");
                enter = 0;
                while (enter != '\r' && enter != '\n') { enter = getchar(); }
                break;
                break;
            case 8:
                printf("Introduza o género e a idade minima de perfil \n");
                if (fgets(input,sizeof(input), stdin))
                querie8_itr(input,num_lines[2],users_table,drivers_table,rides_table);
                printf("\nPressione 'Enter' para continuar\n");
                enter = 0;
                while (enter != '\r' && enter != '\n') { enter = getchar(); }
                break;
            case 9:
                printf("Introduza o intervalo de tempo\n");
                if (fgets(input,sizeof(input), stdin))
                querie9_itr(input,num_lines[2],rides_table);
                printf("\nPressione 'Enter' para continuar\n");
                enter = 0;
                while (enter != '\r' && enter != '\n') { enter = getchar(); }
                break;
            case 0:
                running = false;
                break;
        }
        system("clear");
    }
}