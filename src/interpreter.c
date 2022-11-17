#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/drivers.h"
#include "../includes/users.h"
#include "../includes/rides.h"
#include "../includes/parser.h"
#include "../includes/interpreter.h"
#include "../includes/profile.h"
#include "../includes/nAVR.h"
#include "../includes/hashtables.h"


#define filenametemplate "../Resultados/command%d_output.txt"

char* filename_changer(int filecounter){
    char* ptr = malloc(sizeof(char)* strlen(filenametemplate));
    sprintf(ptr,filenametemplate,filecounter);
    
    return ptr;
}

//DEBUG
void file_writer(char*filepointer, char* input){
    FILE* resultado = fopen(filepointer,"w");
    fprintf(resultado,"%s",input);
    fclose(resultado);
}

void command_interpreter(char* line){
    FILE* commands_file = fopen("../entrada/commands.txt","r");
    int output_counter = 0;
    char* filepointer, *input;
    while(fgets(line,LINE_SIZE,commands_file)){
        output_counter++;// para colocar o numero no ficheiro de output
        char* querie_id = strdup(strsep(&line," ")); // analisa qual a querie a executar
        
        if(atoi(querie_id) == 1){
            filepointer = filename_changer(output_counter); // altera o nome do ficheiro de output (COLOCA-O NA PASTA RESULTADOS)
            input = strdup(strsep(&line,FILE_CSV_DELIM)); // pega no restante texto após o numero da querie e passa à funçao de execuçao da querie (pode requerer parsing posterior dependendo da querie a executar)
            if(g_hash_table_contains(users_table,input))profileU(input);
            else if (g_hash_table_contains(drivers_table,atoi(input))) profileD(input);
            
            file_writer(filepointer,input); // funçao pra debug ---> pseudo "executa querie 1"
            //execQuerie1(input, filepointer); ---> ideia é executar a querie e escrever no file de output tudo dentro da funçao
        }
        if(atoi(querie_id) == 2){
            
            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            nDrivers(atoi(input));

        }
        if(atoi(querie_id) == 3){
            
            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));


        }
        if(atoi(querie_id) == 4){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            
        }
        if(atoi(querie_id) == 5){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            
        }
        if(atoi(querie_id) == 6){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            
        }
        if(atoi(querie_id) == 7){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            
        }
        if(atoi(querie_id) == 8){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            
        }
        if(atoi(querie_id) == 9){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            
        }

    }
    fclose(commands_file);
    free(line);
}


