#include "dsh.h"

/* Checks corresponding command and it's required number of arugments */ 
bool argc_check(int argc, int reqOptionCount, char command){
    if(argc != reqOptionCount){
        switch(command){
            case 'a':
                fprintf(stderr, "Usage: dsh a\n");
                break;
            case 'd':
                fprintf(stderr, "Usage: dsh rm [lane index]\n");
                break;
            case 'g':
                fprintf(stderr, "Usage: dsh [lane index]\n");
                break;
            case 'm':
                fprintf(stderr, "Usage: dsh mv [oldPosition] [newPosition]\n");
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
        fprintf(stderr, "Usage: dsh [a] [rm] [ls] [lane index]\n\t   [mv] [h]\n");
        exit(-1);
    }
    char commandIdentifier[] = {'a', 'd', 'g', 'm'};
    list *dasher = NULL;
    if(!load_lanes(&dasher)) {
        fprintf(stderr, "dsh: error loading lanes\n");
        exit(-1);
    }
    char c = get_option(argc, argv);
    switch(c) {
        case 0:
            if(!argc_check(argc, 2, commandIdentifier[0])) { exit(-1);}
            if(add_command(&dasher) == -1) {exit(-1);}  
            break;
        case 1:
            if(!argc_check(argc, 3, commandIdentifier[1])) { exit(-1);}
            if(remove_command(dasher, argv[2]) == -1) {exit(-1);}
            break;
        case 2:
            list_command(dasher);
            break;
        case 3:
            help_command();
            free_lanes(dasher);
            break;
        case 4:
            if(!argc_check(argc, 4, commandIdentifier[3])) {exit(-1);}
            move_command(&dasher, argv);
            break;
        case 'g':
            if(!argc_check(argc, 2, commandIdentifier[2])) {exit(-1);}
            if(dash_command(dasher, argv[1]) == -1) {exit(-1);}
            break;        
        default :
            fprintf(stderr, "dsh: '%s' is not a valid command, use 'dsh h' for help.\n", argv[1]);
            closest_option(argv[1][0]);
            free_lanes(dasher);
            return(-1);
    }
    return 0;
}
