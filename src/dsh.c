#include <stdio.h>
#include <stdlib.h>

#include "dsh.h"

int main(int argc, char **argv){
    if(argc <= 1){
        printf("Usage: dsh [-a | --add]\n");
    }
    list *dasher = malloc(sizeof(list));

    grab_dir(dasher);
    save_dir(dasher);
printf("argv is here %s\n", argv[1]);
    return 0;
}
