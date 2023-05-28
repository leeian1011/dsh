#include "dsh.h"

static bool is_empty(FILE *persistentDir){
    fseek(persistentDir, 0, SEEK_END);
    long check = ftell(persistentDir);
    if(check > 0) {return false;}

    rewind(persistentDir);
    return true;
}


bool grab_lane(list **dasher){
    char directory[KILOBYTE]; 
    FILE *currentDirectory = popen("pwd", "r"); 
    if(currentDirectory == NULL){
        pclose(currentDirectory);
        return (false);
    }

    fread(directory, sizeof(char), KILOBYTE, currentDirectory); 
    directory[strlen(directory) - 1] = '\0'; 
    append(&*dasher, directory);
    pclose(currentDirectory);
    return (true);
}


bool save_lanes(list *dasher){
    FILE *persistentDir = fopen("cache/lanes.txt", "w");
    if(persistentDir == NULL){
        fclose(persistentDir);
        return (false);
    }
    list *iterator = dasher;

   while(iterator != NULL){
        fprintf(persistentDir, "%s\n", iterator->lane);
        iterator = iterator->next;
   }
    
   fclose(persistentDir);
   return (true);
}


bool load_lanes(list **dasher){
    char c;
    int laneIndex = 0;
    int laneByteCount = 0;

    FILE *persistentDir = fopen("cache/lanes.txt", "r");
    if(persistentDir == NULL){
        fclose(persistentDir);
        return (false);
    }
    
    char laneBuffer[MAX_LANES][KILOBYTE];
   
    while((c = fgetc(persistentDir)) != EOF){
        if(c == '\n'){
            laneBuffer[laneIndex][laneByteCount] = '\0';
            laneIndex++;
            laneByteCount = 0;
            continue;
        }

        laneBuffer[laneIndex][laneByteCount] = c;
        laneByteCount++;
    }
       
    if(is_empty(persistentDir)){
        fclose(persistentDir);
        return (true);
    }

    for(int i = 0; i < laneIndex; i++){
        append(*&dasher, laneBuffer[i]);
    }
    
    fclose(persistentDir);
    return (true); 
    
}
