#include "dsh.h"

bool list_empty(list *dasher){
    if(dasher == NULL) {return (true);}

    return (false);
}

int lowest_position(list *dasher){
    list *iterator = dasher;
    int positionCount = 0;
    if(list_empty(dasher)){ return positionCount;}
    while(1){
       if(positionCount >= MAX_LANES) {return -1;}
       if(iterator->position == positionCount){
         iterator = dasher;
         positionCount++;
        }else{
            iterator = iterator->next;
            if(iterator == NULL) {return positionCount;}
        }
    }
}


void create_lane(list *newLane, int position, char *lane){
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


void append(list **dasher, list **newLane){
    list *iterator = *dasher;
    if(*dasher == NULL){
        dasher[0] = *newLane;
        return;
    }

    while(iterator->next != NULL){
        iterator = iterator->next;
    }

    iterator->next = *newLane;
    return;
}




void remove_at(list *dasher, int position){
    list *iterator = dasher;
    list *prev = NULL;
    while(iterator->position != position){
        prev = iterator;
        iterator = iterator->next;
    }

    prev->next = iterator->next;
    free(iterator->lane);
    free(iterator);
}














