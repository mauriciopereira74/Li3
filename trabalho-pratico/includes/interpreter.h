#ifndef INTERPRETER_H
#define INTERPRETER_H

char* filename_changer(int filecounter);
void file_writer(char*filepointer, char* input);
void command_interpreter(char* line,int num_lines[],char* path);

#endif