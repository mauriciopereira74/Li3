#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/interpreter.h"
#include "../includes/profile.h"
#include "../includes/rideAvr.h"

#include <glib.h>

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

void command_interpreter(char* line,int num_lines[],char* parserPath,char* path){
    FILE* commands_file = fopen(path,"r");
    int output_counter = 0;
    char* filepointer, *input;

    GHashTable *rides_table = rides(line,num_lines,parserPath);
    GHashTable *users_table = users(line,num_lines,parserPath);
    GHashTable *drivers_table = drivers(line,num_lines,parserPath);
    
    while(fgets(line,LINE_SIZE,commands_file)){

        output_counter++;// para colocar o numero no ficheiro de output
        char* querie_id = strdup(strsep(&line," ")); // analisa qual a querie a executar
        
        if(atoi(querie_id) == 1){
        
            filepointer = filename_changer(output_counter); // altera o nome do ficheiro de output (COLOCA-O NA PASTA RESULTADOS)
            input = strdup(strsep(&line,FILE_CSV_DELIM)); // pega no restante texto após o numero da querie e passa à funçao de execuçao da querie (pode requerer parsing posterior dependendo da querie a executar)
            profile(input,num_lines[2],filepointer,users_table,drivers_table,rides_table);
        }
        if(atoi(querie_id) == 2){
            
            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            //listDrivers(input,num_lines[2],filepointer);

        }
        if(atoi(querie_id) == 3){
            
            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));


        }
        if(atoi(querie_id) == 4){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            precoMedioViagens_cidade(input,num_lines[2],filepointer,drivers_table,rides_table);
            
        }
        if(atoi(querie_id) == 5){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            precoMedioViagens_datas(input,num_lines[2],filepointer,drivers_table,rides_table);
            
        }
        if(atoi(querie_id) == 6){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            distanciaMedia(input,num_lines[2],filepointer,rides_table);
            
        }
        if(atoi(querie_id) == 7){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            
        }
        if(atoi(querie_id) == 8){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            listRides(input,num_lines[2],filepointer,users_table,drivers_table,rides_table);
            
        }
        if(atoi(querie_id) == 9){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            
        }

    }
    g_hash_table_destroy(drivers_table);
    g_hash_table_destroy(rides_table);
    g_hash_table_destroy(users_table);
    fclose(commands_file);
    free(line);
}