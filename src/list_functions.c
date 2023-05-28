#include "dsh.h"

static bool is_empty(list *dasher){
    if(dasher == NULL) {return (true);}

    return (false);
}


static void create_lane(list *newLane, int position, char *lane){
    newLane->position = position;
    strcpy(newLane->lane, lane);
    newLane->next = NULL;
}


char *lane_at(list *dasher, int index){
    list *iterator = dasher;
    while(iterator->position != index){
        if(iterator->next == NULL) {return (NULL);}
        iterator = iterator->next;
    }

    return iterator->lane;
}


bool append(list **dasher, char *lane){
    list *iterator = *dasher;
    list *newLane = malloc(sizeof(list));
    if(newLane == NULL) {return (false);}

    newLane->lane = malloc(strlen(lane) + 1);
    if(newLane->lane == NULL) {return(false);}

    if(*dasher == NULL){
        create_lane(newLane, 0, lane);
        *dasher = newLane;
        return (true);
    }
    
    while(iterator->next != NULL){
        iterator = iterator->next;
    }
    if(iterator->position + 1 > MAX_LANES) {return (false);}

    create_lane(newLane, (iterator->position + 1), lane);
    iterator->next = newLane;
    return (true);
}


void print_list(list *dasher){
    list *iterator = dasher;
    if(is_empty(dasher)) {fprintf(stderr, "No lanes have been set\n");}

    while(iterator != NULL){
        printf("%d: %s\n", iterator->position, iterator->lane);
        iterator = iterator->next;
    }
}
