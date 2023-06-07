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
    append(&(*dasher), &newLane); 

    if(!save_lanes(*dasher)){
        fprintf(stderr, "dsh: could not save current directory\n");
        free_lanes(*dasher);
        return;
    }
    
    free(newDirectory);
    free_lanes(*dasher);
}

void remove_command(list *dasher, char *argv){
    int removePosition = (int) argv[0] - '0';
    list *iterator = dasher;
    if(list_empty(iterator)){
        fprintf(stderr, "dsh: no lanes have been set check `dsh h`\n");
        free_lanes(dasher);
        return;
    }
    list *prev = NULL;

    while(iterator != NULL){
        if(iterator->position == removePosition && dasher->position == removePosition){
            dasher = iterator->next;
            break;
        }else if(iterator->position == removePosition){
            prev->next = iterator->next;
            break;
        }else{
            prev = iterator;
            iterator = iterator->next;
        }
    }
    if(list_empty(iterator)){
        fprintf(stderr, "dsh: lane position '%s' does not exist\n", argv);
        free_lanes(dasher);
        return;
    }

    free(iterator->lane);
    free(iterator);

    save_lanes(dasher);
    free_lanes(dasher);
}

void list_command(list *dasher){
    list *iterator = dasher;
    if(list_empty(dasher)) {fprintf(stderr, "No lanes have been set\n");}

    while(iterator != NULL){
        printf("%d: %s\n", iterator->position, iterator->lane);
        iterator = iterator->next;
    }

    free_lanes(dasher);
}
