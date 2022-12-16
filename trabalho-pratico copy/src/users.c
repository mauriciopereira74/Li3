#include "../includes/users.h"
#include "../includes/parse_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glib.h>

GHashTable *users_table;

struct user
{
    char *username, /**< string that represents the login of the user. */
         *name, /**< string that represents the name of the user. */
         *pay_method; /**< string that represents the payment method chosen by the user. */

    char* gender; /**< char that represents the gender of the user. */

    char* Acc_Status; /**< string to check the user account status. */

    struct tm created_time; /**< struct that represents the datetime on which the user account was created. */

    struct tm birth_date ; /**< struct that represents the user's date of birth. */

    
} ;

void debugUser(User u){
    
    printf("Username: %s; ",u->username);
    printf("Name: %s; ",u->name);
    printf("Gender: %s; ",u->gender);
    printf("Birth Date: %d/%d/%d; ",u->birth_date.tm_mday,u->birth_date.tm_mon,u->birth_date.tm_year);
    printf("Account Creation: %d/%d/%d; ",u->created_time.tm_mday,u->created_time.tm_mon,u->created_time.tm_year);
    printf("Pay Method: %s; ",u->pay_method);
    printf("Account Status: %s\n ",u->Acc_Status);
}


/**
 * 
 * @brief Função que realiza o parsing do ficheiro users.csv
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

void parse_users(char* line,User u){
   
    u->username         = strdup(strsep(&line,FILE_CSV_DELIM));
    u->name             = strdup(strsep(&line,FILE_CSV_DELIM));
    u->gender           = strdup(strsep(&line,FILE_CSV_DELIM));
    u->birth_date       = date_parse(strdup(strsep(&line,FILE_CSV_DELIM)));
    u->created_time     = date_parse(strdup(strsep(&line,FILE_CSV_DELIM)));
    u->pay_method       = strdup(strsep(&line,FILE_CSV_DELIM)); // could be type enum
    u->Acc_Status       = strdup(strsep(&line,FILE_CSV_DELIM));

}

User clone_user(User u){
    User aux = malloc(sizeof(struct user));
    memcpy(aux,u,sizeof(struct user));
    return aux;
}

void user_insert(User u){
    g_hash_table_insert(users_table,get_username(u),clone_user(u));
}

int user_check(char *name){
    if (g_hash_table_lookup(users_table,name)) return 1;
    else return 0;
}

struct user *get_userStruct(char *name){
    struct user *temp = g_hash_table_lookup(users_table,name);
    return temp;
}

char * get_username(User u){
    return u->username;
}

char *get_name(User u){
    return u->name;
}

char *get_userGender(User u){
    return u->gender;
}

struct tm get_userBirth(User u){
    return u->birth_date;
}
struct tm get_userCreateTime(User u){
    return u->created_time;
}

char *get_userPayMethod(User u){
    return u->pay_method;
}

char *get_userStatus(User u){
    return u->Acc_Status;
}

/**
 * @brief Função que realiza o parsing de todos os ficheiros .csv.
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */ 
void users(char* line,int num_lines[],char* path){

    char user_path [BUFSIZ];//= malloc(sizeof(path));
    strcpy(user_path,path);
    strcat(user_path,"/users.csv");

    users_table = g_hash_table_new(g_str_hash, g_str_equal);

    int count = 0;
    FILE* users_data = fopen(user_path,"r");
    fgets(line,LINE_SIZE,users_data);
    while(fgets(line,LINE_SIZE,users_data)){
        count++;
        User temp_user = malloc(sizeof(struct user));// a funçao retorna cada struct User criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess
        parse_users(line,temp_user);
        user_insert(temp_user);
        free(temp_user);
    }
    fclose(users_data);
    num_lines[0] = count;
}

