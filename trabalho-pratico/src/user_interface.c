#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h> 
#include <stdlib.h>
#include <unistd.h>

#include "../includes/interface_func.h"
#include "../includes/user_interface.h"

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
            
}

void interface(){

    bool interface_state = true;
    int current_page = 1; int id = 0;

    while(interface_state){
        clear_screen();
        print_boxed("Bem-vindo ao Projeto de LI3!\nPara comecar escolha a query a ser executada, ou escreva 'h' para abrir o menu de ajuda.\n");
        printf("\n");
        print_queries();
        interface_state=0;
    }
}