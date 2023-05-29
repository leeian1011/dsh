#include "dsh.h"

int main(void){
    list *dasher = NULL;
    
    load_lanes(&dasher);
    list *iterator = dasher;
    printf("%s\n", dasher->lane);
    printf("%s\n", iterator->lane);
    while(iterator != NULL){
        printf("%d: %s\n", iterator->position, iterator->lane);
        iterator = iterator->next;
    }
    save_lanes(dasher);
    free_lanes(dasher);

    while(iterator != NULL){
        printf("%d: %s\n", iterator->position, iterator->lane);
        iterator = iterator->next;
    }
}
