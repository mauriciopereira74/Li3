#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/users.h"
#include "../includes/drivers.h"
#include "../includes/rides.h"
#include "../includes/interpreter.h"
#include "../includes/querie_aux.h"
#include "../includes/queries.h"

#include <glib.h>

#define filenametemplate "./Resultados/command%d_output.txt"

char* filename_changer(int filecounter){
    char* ptr = malloc(sizeof(char) * (strlen(filenametemplate) + sizeof(int)));
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

    GHashTable *users_table = users(line,num_lines,parserPath);
    GHashTable *drivers_table = drivers(line,num_lines,parserPath);
    GHashTable *rides_table = rides(line,num_lines,parserPath,drivers_table,users_table);
    while(fgets(line,LINE_SIZE,commands_file)){

        output_counter++;// para colocar o numero no ficheiro de output
        char* querie_id = strdup(strsep(&line," ")); // analisa qual a querie a executar
        
        if(atoi(querie_id) == 1){
        
            filepointer = filename_changer(output_counter); // altera o nome do ficheiro de output (COLOCA-O NA PASTA RESULTADOS)
            input = strdup(strsep(&line,FILE_CSV_DELIM)); // pega no restante texto após o numero da querie e passa à funçao de execuçao da querie (pode requerer parsing posterior dependendo da querie a executar)
            querie1(input,num_lines[2],filepointer,users_table,drivers_table,rides_table);
        }
        if(atoi(querie_id) == 2){
            
            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            querie2(input,num_lines[2],filepointer,drivers_table);
        }
        if(atoi(querie_id) == 3){
            
            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            querie3(input,num_lines[2],filepointer,users_table);

        }
        if(atoi(querie_id) == 4){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            querie4(input,num_lines[2],filepointer,drivers_table,rides_table);
            
        }
        if(atoi(querie_id) == 5){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            querie5(input,num_lines[2],filepointer,drivers_table,rides_table);
            
        }
        if(atoi(querie_id) == 6){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            querie6(input,num_lines[2],filepointer,rides_table);
            
        }
        if(atoi(querie_id) == 7){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            querie7(input,num_lines[2],filepointer,drivers_table,rides_table);
        }
        if(atoi(querie_id) == 8){
            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            querie8(input,num_lines[2],filepointer,users_table,drivers_table,rides_table);
            
        }
        if(atoi(querie_id) == 9){

            filepointer = filename_changer(output_counter);
            input = strdup(strsep(&line,FILE_CSV_DELIM));
            querie9(input,num_lines[2],filepointer,rides_table);

        }

    }
    g_hash_table_destroy(drivers_table);
    g_hash_table_destroy(rides_table);
    g_hash_table_destroy(users_table);
    fclose(commands_file);
    free(filepointer);
    free(line);
}
/* 
void querie_interpreter(){
    if (query_id == 1) exec_1(statistics, id);
    if (query_id == 2) exec_2(statistics, users, commits, id);
    if (query_id == 3) exec_3(statistics, id);
    if (query_id == 4) exec_4(statistics, id);
    if (query_id == 5) exec_5(users, commits, id);
    if (query_id == 6) exec_6(users, commits, repos, id);
    if (query_id == 7) exec_7(repos, commits, id);
    if (query_id == 8) exec_8(repos, id);
    if (query_id == 9) exec_9(users, commits, repos, id);
    if (query_id == 10) exec_10(users, commits, repos, id);
}
*/