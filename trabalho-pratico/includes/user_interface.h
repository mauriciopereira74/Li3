#ifndef UI_H
#define UI_H

#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void print_boxed(char *content);
void clear_screen();
void print_list_item(char *list_number, char *content);
void interface(char* line,int num_lines[],char* parserPath,char* path);

#endif