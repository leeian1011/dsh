#include "dsh.h"

int main(int argc, char **argv){
    if(argc <= 1){
        printf("Usage: %s [-a | --add]\n", argv[0]);
        return (-1);
    }
    
    char c = get_option(argc, argv);
    switch(c) {
        case 0:
            printf("%s and found 'add'\n", *++argv);
            break;
        case 1:
            printf("rm works i guess\n");
            break;
        case 2:
            printf("list called\n");
            break;
        case 3:
            printf("help called\n");
            break;
        case 'g':
            if(atoi(*argv) < MAX_LANES){
                fprintf(stderr, "%s is more than the maximum number of lanes (%d)", *++argv, MAX_LANES);
                return (-1);
            }
            break;        
        default :
            fprintf(stderr, "'%s' is not a valid command, use 'dsh h' for help.\n", argv[1]);
            closest_option(argv[1][0]);
            return(-1);
    }
     

    //printf("main: %d:%s\n %d:%s\n %d:%s\n", dasher->position, dasher->lane, dasher->next->position, dasher->next->lane, dasher->next->next->position, dasher->next->next->lane);
    return 0;
}
