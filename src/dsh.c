#include "dsh.h"


int main(int argc, char **argv){
    if(argc <= 1){
        printf("Usage: dsh [-a | --add]\n");
    }
    list *dasher = NULL;
    load_lanes(&dasher);
    printf("%s\n", argv[0]); 
    printf("main: %d:%s\n %d:%s\n %d:%s\n", dasher->position, dasher->lane, dasher->next->position, dasher->next->lane, dasher->next->next->position, dasher->next->next->lane);
    save_lanes(dasher);
    free(dasher);
    return 0;
}
