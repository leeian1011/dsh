#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dsh.h"

int grab_dir(list *dasher){
    FILE *currentDirectory = popen("pwd", "r");
    if(currentDirectory == NULL){
        return -1;
    }
    char directory[1024];

    fread(directory, sizeof(char), 1024, currentDirectory);
    pclose(currentDirectory);
    
    dasher->lane = malloc(strlen(directory) + 1);
    if(dasher->lane == NULL){
        return -1;
    }
    dasher->position = 0;
    strcpy(dasher->lane, directory);
    dasher->lane[strlen(dasher->lanes) - 1] = '\0'; 
    return 0;
}

