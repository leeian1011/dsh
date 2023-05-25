#include <stdio.h>
#include <stdlib.h>

#include "dsh.h"

int main(int argc, char **argv){
    if(argc <= 1){
        printf("Usage: dsh [-a | --add]\n");
    }
    list *dasher = malloc(sizeof(list));
    list *dasherHead = dasher;
    append(dasherHead, "test");
    append(dasherHead, "try2");
    printf("LIST\n Position: %d\nLane: %s\n", dasher->position, dasher->lane);
    printf("Position: %d\nLane %s\n", dasher->next->position, dasher->next->lane);
    save_lanes(dasher);

printf("argv is here %s\n", argv[1]);
    return 0;
}
