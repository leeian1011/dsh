#include <stdlib.h>
#include <stdio.h>
#include "dsh.h"

static list *createLane(list *newLane, int position, char *lane){
    printf("createLane: %s\n", lane);
    newLane->lane = lane;
    newLane->position = position;
    newLane->next = NULL;
    printf("newLane = :\nlane = %s\npositiion = %d\n", newLane->lane, newLane->position);
    return newLane;
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
static int is_empty(list *dasherHead){
    printf("%s\n", dasherHead->lane);
    if(dasherHead->lane == NULL && dasherHead->next == NULL){
        printf("iterator is empty\n");
        return (1);
    }
    printf("not empty\n");
    return 0;
}

int append(list *dasher, char *lane){
    list *iterator = dasher;
    list *newLane = malloc(sizeof(list));
    if(is_empty(dasher)){
        dasher->position = 0;
        dasher->lane = lane;
        dasher->next = NULL;
        printf("dasher is set to %s\n%d\n", dasher->lane, dasher->position);
        free(newLane);
        return 0;
    }

    while(iterator->next != NULL){
        iterator = iterator->next;
    }

    createLane(newLane, (iterator->position + 1),lane);

    iterator->next = newLane; 
    return 0;
}

