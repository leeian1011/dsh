#include "dsh.h"

/* Used specifically in lane_functions.c functions 
 * checks if a the file lanes.txt is empty */
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

/* function that returns a string pointer to directory path where lanes.txt is stored */ 
char *cache(){
    char *pathToCache = getenv("DASH_CACHE");
    if(pathToCache == NULL){
        fprintf(stderr, "dsh: DASH_CACHE environment variable not set\n");
        return (NULL);
    }
    char *directory = malloc(strlen(pathToCache) + 1);
    if(directory == NULL){
        free(directory);
        fprintf(stderr, "dsh: memory error in load_lane\n");
        return(NULL);
    }
    strcpy(directory, pathToCache);

    return directory;
}

/* function that returns a string pointer to the current working directory */
char *set_directory(){
    char *directory = malloc(KILOBYTE);
    FILE *currentDirectory = popen("pwd", "r");
    if(currentDirectory == NULL){
        pclose(currentDirectory);
        free(directory);
        return (NULL);
    }

    fread(directory, sizeof(char), KILOBYTE, currentDirectory);
    pclose(currentDirectory);
    
    directory[strlen(directory) - 1] = '\0';
    return directory;
}

/* writes to lanes.txt the list separating position & lanes with '\n' */
bool save_lanes(list *dasher){
    char *cacheDir = cache();
    FILE *persistentDir = fopen(cacheDir, "w");
    if(persistentDir == NULL){
        fclose(persistentDir);
        return (false);
    }
    list *iterator = dasher;
    if(list_empty(dasher)){
        fclose(persistentDir);
        return(true);
    }
   while(iterator != NULL){
        fprintf(persistentDir, "%d\n", iterator->position);
        fprintf(persistentDir, "%s\n", iterator->lane);
        iterator = iterator->next;
   }

   fclose(persistentDir);
   free(cacheDir); 
   return (true);
}

/* reads from lanes.txt into the list structure dasher */
bool load_lanes(list **dasher){
    char c;
    int laneIndex = 0;
    int laneByteCount = 0;
    int positionIndex = 0;
    int newLineCount = 0;
    int positions[MAX_LANES];
    char laneBuffer[MAX_LANES][KILOBYTE];
    char *pathToCache = cache();
    FILE *persistentDir = fopen(pathToCache, "r");
    if(persistentDir == NULL){
        fclose(persistentDir);
        return (false);
    }
    
    if(is_empty(persistentDir)){
        free(pathToCache);
        fclose(persistentDir);
        return (true);
    }
    
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
    free(pathToCache);
    
     list *newLane[laneIndex];
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

    for(int i = 0; i < laneIndex; i++){
        create_lane(newLane[i], positions[i], laneBuffer[i]);
        append(&(*dasher), &newLane[i]);
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

/* checks if current working directory already exists in list */
bool check_duplicate(list *dasher, char *directory){
    list *iterator = dasher;
    while(iterator != NULL){
        if(strcmp(iterator->lane, directory) == 0) {return(false);}
        iterator = iterator->next;
    }

    return (true);
}

