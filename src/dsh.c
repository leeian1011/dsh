#include "dsh.h"

int main(int argc, char **argv){
    if(argc <= 1){
        return (-1);
    }
    list *dasher = NULL;
    if(!load_lanes(&dasher)) {
        fprintf(stderr, "dsh: error loading lanes\n");
        return (-1);
    }

    char c = get_option(argc, argv);
    switch(c) {
        case 0:
            add_command(&dasher);  
            break;
        case 1:
            printf("rm works i guess\n");
            break;
        case 2:
            print_list(dasher);
            break;
        case 3:
            printf("help called\n");
            break;
        case 'g':
            if(argc > 2){
                fprintf(stderr, "Usage: dsh [lane index]\n");
                return (-1);
            }

            if(atoi(*++argv) > MAX_LANES){
                fprintf(stderr, "dsh: Index %s does not exist\nMax number of lanes: 0-%d\n", *argv, MAX_LANES);
                return (-1);
            }
            break;        
        default :
            fprintf(stderr, "dsh: '%s' is not a valid command, use 'dsh h' for help.\n", argv[1]);
            closest_option(argv[1][0]);
            return(-1);
    }
     
    return 0;
}
