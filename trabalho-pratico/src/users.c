#include "../includes/users.h"
#include "../includes/parse_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glib.h>

struct user
{
    char *username, /**< string that represents the login of the user. */
         *name, /**< string that represents the name of the user. */
         *pay_method; /**< string that represents the payment method chosen by the user. */

    char* gender; /**< char that represents the gender of the user. */

    char* Acc_Status; /**< string to check the user account status. */

    struct tm created_time; /**< struct that represents the datetime on which the user account was created. */

    struct tm birth_date ; /**< struct that represents the user's date of birth. */

    double avaliacao_total;
    int n_viagens;
    double avaliacao_media;
    double total_gasto;
    int distancia_total;
    struct tm lastride;
} ;

void debugUser(User u){
    
    printf("Username: %s; ",u->username);
    printf("Name: %s; ",u->name);
    printf("Gender: %s; ",u->gender);
    printf("Birth Date: %d/%d/%d; ",u->birth_date.tm_mday,u->birth_date.tm_mon,u->birth_date.tm_year);
    printf("Account Creation: %d/%d/%d; ",u->created_time.tm_mday,u->created_time.tm_mon,u->created_time.tm_year);
    printf("Pay Method: %s; ",u->pay_method);
    printf("Account Status: %s\n",u->Acc_Status);
}


void insert_birthdateUser(User u, char* date){
    int day,mon,year;

    day= atoi(strsep(&date,"/"));
    mon= atoi(strsep(&date,"/"));
    year=atoi(strsep(&date,"\0"));

    u->birth_date.tm_mday = day;
    u->birth_date.tm_mon  = mon;
    u->birth_date.tm_year = year;

}

void insert_createddateUser(User u, char* date){
    int day,mon,year;
    day= atoi(strsep(&date,"/"));
    mon= atoi(strsep(&date,"/"));
    year=atoi(strsep(&date,"\0"));

    u->created_time.tm_mday = day;
    u->created_time.tm_mon  = mon;
    u->created_time.tm_year = year;

}

/**
 * 
 * @brief Função que realiza o parsing do ficheiro users.csv
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */

int parse_users(char* line,User u){
    int r = 1;
    char* birth_date, *created_time;
    u->username         = strdup(strsep(&line,FILE_CSV_DELIM));
    u->name             = strdup(strsep(&line,FILE_CSV_DELIM));
    u->gender           = strdup(strsep(&line,FILE_CSV_DELIM));
    birth_date          = strdup(strsep(&line,FILE_CSV_DELIM));//uso isto porque tenho de verificar se a data é valida enquanto for uma string.. mas ela é guardada no user como struct tm o que leva a que apesar dos numeros poderem ser validos o formato geral da data ser errado (ex. separada por hifens)
    created_time        = strdup(strsep(&line,FILE_CSV_DELIM));
    u->pay_method       = strdup(strsep(&line,FILE_CSV_DELIM)); // could be type enum
    u->Acc_Status       = strdup(strsep(&line,FILE_CSV_DELIM));
    u->avaliacao_total  = 0;
    u->n_viagens        = 0;
    u->total_gasto      = 0;
    u->distancia_total  = 0;
    u->avaliacao_media  = 0;

    lowercase(u->Acc_Status);
    if (validateStrFields(u->username) == 0 || validateStrFields(u->name) == 0 || 
        validateStrFields(u->gender) == 0  || validateStrFields(u->pay_method) == 0 ||
        check_date_format(birth_date) == 0 || check_date_format(created_time)==0 || 
        (strcmp(u->Acc_Status,"active") != 0  && strcmp(u->Acc_Status,"inactive") != 0)){ // unfinished
        free(u);
        r = 0;
    }
    else{
        insert_birthdateUser(u,birth_date);
        insert_createddateUser(u,created_time);
    }
    return r;
}

User clone_user(User u){
    User aux = malloc(sizeof(struct user));
    memcpy(aux,u,sizeof(struct user));
    return aux;
}

void user_insert(GHashTable *users_table,User u){
    g_hash_table_insert(users_table,get_username(u),clone_user(u));
}

int user_check(GHashTable *users_table,char *name){
    if (g_hash_table_lookup(users_table,name)) return 1;
    else return 0;
}

struct user *get_userStruct(GHashTable *users_table,char *name){
    struct user *temp = g_hash_table_lookup(users_table,name);
    return temp;
}

char * get_username(User u){
    return u->username;
}

char *get_user_name(User u){
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

struct tm get_userLastRide(User u){
    return u->lastride;
}


char *get_userPayMethod(User u){
    return u->pay_method;
}

char *get_userStatus(User u){
    return u->Acc_Status;
}

double get_userAvalTotal(User u){
    return u->avaliacao_total;
}

double get_userAvalMedia(User u){
    return u->avaliacao_media;
}

int get_userNumViagens(User u){
    return u->n_viagens;
}

double get_userTotalGasto(User u){
    return u->total_gasto;
}

int get_userDistanciaTotal(User u){
    return u->distancia_total;
}

void set_userInfo(User u,double avaliacao,double gasto,int distancia,struct tm last_ride){
    if(get_userNumViagens(u)==0){
        u->avaliacao_total=u->avaliacao_total+avaliacao;
        u->total_gasto=u->total_gasto+gasto;
        u->distancia_total=u->distancia_total+distancia;
        u->n_viagens=1;
        u->avaliacao_media=u->avaliacao_total/(double)u->n_viagens;
        u->lastride=last_ride;
    }
    else {
        u->avaliacao_total=u->avaliacao_total+avaliacao;
        u->total_gasto=u->total_gasto+gasto;
        u->distancia_total=u->distancia_total+distancia;
        u->n_viagens++;
        u->avaliacao_media=u->avaliacao_total/(double)u->n_viagens;
        u->lastride=last_ride;

    }
}

/**
 * @brief Função que realiza o parsing de todos os ficheiros .csv.
 * 
 * @param line apontador para um espaço em memória onde será guardada a string(linha)
 * 
 */ 
GHashTable *users(char* line,int num_lines[],char* path){
    char user_path [BUFSIZ];//= malloc(sizeof(path));
    strcpy(user_path,path);
    strcat(user_path,"/users.csv");
    GHashTable *users_table = g_hash_table_new_full(g_str_hash, g_str_equal,NULL,g_free);

    int count = 0;
    FILE* users_data = fopen(user_path,"r");
    fgets(line,LINE_SIZE,users_data);
    
    while(fgets(line,LINE_SIZE,users_data) != NULL){
        count++;
        User temp_user = malloc(sizeof(struct user));// a funçao retorna cada struct User criada por isso a importaçao para a hashtable deve ser feita dentro de cada ciclo while i guess
        int is_valid_user = parse_users(line,temp_user);
        if(is_valid_user == 1){
            user_insert(users_table,temp_user);
            free(temp_user); // este free so ocorre quando o user é valido por isso nao leva free no parse_users e foi inserido na hash
        }
    }
    fclose(users_data);
    num_lines[0] = count;
    return users_table;
}

