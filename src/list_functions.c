#include <stdlib.h>

#include "dsh.h"

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
