#include "dsh.h"


int main(int argc, char **argv){
    if(argc <= 1){
        printf("Usage: dsh [-a | --add]\n");
    }
    list *dasher = NULL;
    
    grab_lane(&dasher);
printf("main : %s\n main: %d", dasher->lane, dasher->position);
    save_lanes(dasher);
    free(dasher);
printf("argv is here %s\n", argv[1]);
    return 0;
}
