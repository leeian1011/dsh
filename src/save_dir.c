#include <stdio.h>

#include "dsh.h"

int save_dir(list *dasher){
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
