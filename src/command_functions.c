#include "dsh.h"

void add_command(list **dasher){
    /*if(!grab_lane(&(*dasher))){
        fprintf(stderr, "dsh: could not grab current directory\n");
        free_lanes(*dasher);
        return;
    }*/
    
    if(!save_lanes(*dasher)){
        fprintf(stderr, "dsh: could not save current directory\n");
        free_lanes(*dasher);
        return;
    }
    
    free_lanes(*dasher);
}


