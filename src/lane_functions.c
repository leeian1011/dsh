#include "dsh.h"

static bool is_empty(FILE *persistentDir){
    fseek(persistentDir, 0, SEEK_END);
    long check = ftell(persistentDir);
    if(check > 0) {
        rewind(persistentDir);
        return false;
    }

    rewind(persistentDir);
    return true;
}


/*bool grab_lane(list **dasher){
    char directory[KILOBYTE]; 
    FILE *currentDirectory = popen("pwd", "r"); 
    if(currentDirectory == NULL){
        pclose(currentDirectory);
        return (false);
    }

    fread(directory, sizeof(char), KILOBYTE, currentDirectory); 
    directory[strlen(directory) - 1] = '\0'; 
    if(!append(&(*dasher),)){
        fprintf(stderr, "Maximum number of lanes have been saved\n");
        return (false);
    }
    ;
    pclose(currentDirectory);
    return (true);
}*/


bool save_lanes(list *dasher){
    FILE *persistentDir = fopen(".cache/lanes.txt", "w");
    if(persistentDir == NULL){
        fclose(persistentDir);
        return (false);
    }
    list *iterator = dasher;

   while(iterator != NULL){
       fprintf(persistentDir, "%d\n", iterator->position);
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
    int positionIndex = 0;
    int newLineCount = 0;
    int positions[MAX_LANES];
    char laneBuffer[MAX_LANES][KILOBYTE];
    list *newLane[MAX_LANES];

    FILE *persistentDir = fopen(".cache/lanes.txt", "r");
    if(persistentDir == NULL){
        fclose(persistentDir);
        return (false);
    }
    
    if(is_empty(persistentDir)){
        fclose(persistentDir);
        return (true);
    }
    printf("passes empt check\n");
    while((c = fgetc(persistentDir)) != EOF){
        if(newLineCount % 2 == 0){
            if(c == '\n') {
                newLineCount++;
                positionIndex++;
                continue;}
            positions[positionIndex] = (c - '0');
        }
        if(newLineCount % 2 != 0){
            if(c == '\n'){
                laneBuffer[laneIndex][laneByteCount] = '\0';
                laneByteCount = 0;
                laneIndex++;
                newLineCount++;
                continue;
            }
            laneBuffer[laneIndex][laneByteCount] = c;
            laneByteCount++;
        }
    }

    printf("passes whil c loop\n");
    for(int i = 0; i < laneIndex; i++){
        newLane[i] = malloc(sizeof(list));
        if(newLane[i] == NULL){
            for(int j = 0; j < i; j ++){
                free(newLane[j]);
            }
            free(newLane[i]);
            return (false);
        }
        newLane[i]->lane = malloc(strlen(laneBuffer[i]) + 1);
        if(newLane[i]->lane == NULL){
            for(int j = 0; j < i; j++){
                free(newLane[j]->lane);
                free(newLane[j]);
            }
            free(newLane[i]->lane);
            free(newLane[i]);
            return(false);
        }
    }
printf("survive allocation\n");

    for(int i = 0; i < laneIndex; i++){
        create_lane(newLane[i], positions[i], laneBuffer[i]);
        printf("%s\n%d\n", newLane[i]->lane, newLane[i]->position);
        append(&(*dasher), &newLane[i]);
        printf("loading : dasher = %s", dasher[0]->lane);
    }
         
    
    fclose(persistentDir);
    return (true); 
    
}


void free_lanes(list *dasher){
    list *iterator = dasher;
    list *previous = NULL;

    while(iterator != NULL){
        previous = iterator;
        iterator = iterator->next;
        free(previous->lane);
        free(previous);
    }
}












