#include <stdio.h>
#include <string.h>
#include <ctype.h>

void clean_line(char* line){
    char* command_line = strchr(line, '#');
    if(command_line != NULL){
        *command_line = '\0';
    }
    int len = strlen(line);
    while(len > 0 && isspace((char)line[len - 1])){
        line[len-1] = '\0';
    }
}