#include "dsh.h"

bool argc_check(int argc, int reqOptionCount, char command){
    if(argc != reqOptionCount){
        switch(command){
            case 'a':
                fprintf(stderr, "Usage: dsh a\n");
                break;
            case 'd':
                fprintf(stderr, "Usage: dsh rm [lane index]\n");
                break;
            default:
                return false;
        }
        return false;
    }
    return true;
}

int main(int argc, char **argv){
    if(argc == 1){
        printf("Usage: dsh [a] [rm] [h] [ls]\n");
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
            if(!argc_check(argc, 2, 'a')) { return (-1);}
            add_command(&dasher);  
            break;
        case 1:
            if(argc != 3){
                fprintf(stderr, "Usage: dsh rm [lane index]\n");
                return(-1);
            }
            save_lanes(dasher);
            break;
        case 2:
            list_command(dasher);
            break;
        case 3:
            printf("help called\n");
            break;
        case 4:
            printf("moving called\n");
            break;
        case 5:
            printf("sort called\n");
            break;
        case 'g':
            printf("go called\n");
            if(argc > 2){
                fprintf(stderr, "Usage: dsh [lane index]\n");
                return (-1);
            }

            if(atoi(*++argv) >= MAX_LANES){
                fprintf(stderr, "dsh: Index %s does not exist\nMax number of lanes: 0-%d\n", *argv, MAX_LANES - 1);
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
