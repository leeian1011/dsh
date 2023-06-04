#include "dsh.h"

static bool is_empty(list *dasher){
    if(dasher == NULL) {return (true);}

    return (false);
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


bool append(list **dasher, list **newLane){
    list *iterator = *dasher;
    if(*dasher == NULL){
        *dasher = *newLane;
        return (true);
    }

    while(iterator->next != NULL){
        iterator = iterator->next;
    }


    iterator->next = *newLane;
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














