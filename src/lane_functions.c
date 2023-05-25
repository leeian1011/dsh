#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dsh.h"

int grab_lane(list *dasher){
    FILE *currentDirectory = popen("pwd", "r");
    if(currentDirectory == NULL){
        return -1;
    }
    char directory[1024];

    fread(directory, sizeof(char), 1024, currentDirectory);
    directory[strlen(directory) - 1] = '\0';

    append(dasher, directory);
    printf("grab_lane : %s\n", directory);
    pclose(currentDirectory);
    return 0;
}


int save_lanes(list *dasher){
    FILE *persistentDir = fopen("cache/lanes.txt", "w");
    if(persistentDir == NULL){
        return -1;
    }
    list *iterator = dasher;

   while(iterator != NULL){
        fprintf(persistentDir, "%d\n", iterator->position);
        fprintf(persistentDir, "%s\n", iterator->lane);
        iterator = iterator->next;
   }
    
   fclose(persistentDir);
   return 0;
}


