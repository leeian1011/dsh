#include "dsh.h"

static void create_lane(list *newLane, int position, char *lane){
    newLane->position = position;
    strcpy(newLane->lane, lane);
    newLane->next = NULL;
}


char *laneAt(list *dasher, int index){
    list *iterator = dasher;
    while(iterator->position != index){
        if(iterator->next == NULL){
            return (NULL);
        }
        iterator = iterator->next;
    }

    return iterator->lane;
}


bool append(list **dasher, char *lane){
    list *iterator = *dasher;
    list *newLane = malloc(sizeof(list));
    if(newLane == NULL){
        return (-1);
    }
    newLane->lane = malloc(strlen(lane) + 1);
    if(newLane->lane == NULL){
        return (-1);
    }
    if(*dasher == NULL){
        create_lane(newLane, 0, lane);
        *dasher = newLane;
        return 0;
    }
    
    while(iterator->next != NULL){
        iterator = iterator->next;
    }
    
    create_lane(newLane, ++iterator->position, lane);
    iterator->next = newLane;
    return 0;
}

