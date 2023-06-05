#include "dsh.h"

void add_command(list **dasher){
    int newPosition = lowest_position(*dasher);
    if(lowest_position(*dasher) == -1){
        fprintf(stderr, "dsh: all %d lanes are used\n\tdsh rm \[index] to remove a lane\n", MAX_LANES);
        free_lanes(*dasher);
        return;
    }

    char *newDirectory = NULL;
    newDirectory = set_directory();
    if(newDirectory == NULL){
        fprintf(stderr, "dsh: error getting current working directory\n");
        free(newDirectory);
        free_lanes(*dasher);
        return;
    }

    list *newLane = malloc(sizeof(list));
    if(newLane == NULL){
        free(newLane);
        free(newDirectory);
        free_lanes(*dasher);
        return;
    }

    newLane->lane = malloc(strlen(newDirectory) + 1);
    if(newLane->lane == NULL){
        free(newLane->lane);
        free(newLane);
        free(newDirectory);
        free_lanes(*dasher);
        return;
    }

    create_lane(newLane, newPosition, newDirectory);
    printf("lane in add command:\n%s\n%d\n",newLane->lane, newLane->position);
    append(&(*dasher), &newLane); 

    if(!save_lanes(*dasher)){
        fprintf(stderr, "dsh: could not save current directory\n");
        free_lanes(*dasher);
        return;
    }
    
    free_lanes(*dasher);
}


