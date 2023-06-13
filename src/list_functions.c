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
    if(list_empty(*dasher)){
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


void move(list *dasher, int newPosition, int oldPosition){
    list *iterator = dasher;
    
    while(iterator != NULL){
        if(iterator->position == newPosition){
            iterator->position = oldPosition;
            iterator = iterator->next;
            continue;
        }else if(iterator->position == oldPosition){
            iterator->position = newPosition;
            iterator = iterator->next;
            continue;
        }

        iterator = iterator->next;
    }
}

static int list_length(list *dasher){
    list *iterator = dasher;
    int length = 0;
    while(1){
        if(iterator->next == NULL) {
            return length;
        }
        length++;
        iterator = iterator->next;
    }

}

void sort(list **dasher){
    list *iterator = (*dasher)->next;
    if(iterator == NULL){
        return;
    }
    list *previousIterator = (*dasher);
    list *sortedIterator = (*dasher);
    list *previousSortedIterator = NULL;
   
    int dasherLen = list_length(*dasher) + 1;
    int count = 1;
    while(count < dasherLen){
        for(int i = 0; i < count; i++){
            if(iterator->position < sortedIterator->position){
                if(previousSortedIterator == NULL){
                    previousIterator->next = iterator->next;;
                    iterator->next = sortedIterator;
                    *dasher = iterator;
                    break;
                }
                previousIterator->next = iterator->next;
                iterator->next = sortedIterator;
                previousSortedIterator->next = iterator;
                previousSortedIterator = previousSortedIterator->next;
                break;
            }
            if(sortedIterator->next == iterator){
                previousIterator = iterator;
                break;
            }
            previousSortedIterator = sortedIterator;
            sortedIterator = sortedIterator->next;
        }
        iterator = previousIterator->next;
        sortedIterator = (*dasher);
        previousSortedIterator = NULL;
        count++;
    }
}

