#include "dsh.h"
#include <unistd.h>

int add_command(list **dasher){
    int newPosition = lowest_position(*dasher);
    if(lowest_position(*dasher) == -1){
        fprintf(stderr, "dsh: all %d lanes are used\n\tdsh rm \[index] to remove a lane\n", MAX_LANES);
        free_lanes(*dasher);
        return (-1);
    }

    char *newDirectory = NULL;
    newDirectory = set_directory();
    if(newDirectory == NULL){
        fprintf(stderr, "dsh: error getting current working directory\n");
        free(newDirectory);
        free_lanes(*dasher);
        return (-1);
    }
    
    if(!check_duplicate(*dasher, newDirectory)){
        fprintf(stderr, "dsh: %s already saved\n", newDirectory);
        free(newDirectory);
        free_lanes(*dasher);
        return (-1);
    }

    list *newLane = malloc(sizeof(list));
    if(newLane == NULL){
        fprintf(stderr, "dsh: memory error!\n");
        free(newLane);
        free(newDirectory);
        free_lanes(*dasher);
        return (-1);
    }

    newLane->lane = malloc(strlen(newDirectory) + 1);
    if(newLane->lane == NULL){
        fprintf(stderr, "dsh: memory error!\n");
        free(newLane->lane);
        free(newLane);
        free(newDirectory);
        free_lanes(*dasher);
        return (-1);
    }

    create_lane(newLane, newPosition, newDirectory);
    append(&(*dasher), &newLane); 
    sort(&(*dasher));
    if(!save_lanes(*dasher)){
        fprintf(stderr, "dsh: could not save current directory\n");
        free_lanes(*dasher);
        return (-1);
    }
    
    free(newDirectory);
    free_lanes(*dasher);
    return (0);
}

int remove_command(list *dasher, char *argv){
    int removePosition = (int) argv[0] - '0';
    list *iterator = dasher;
    if(list_empty(iterator)){
        fprintf(stderr, "dsh: no lanes have been set check `dsh h`\n");
        free_lanes(dasher);
        return (-1);
    }
    list *prev = NULL;

    while(!list_empty(iterator)){
        if(dasher->position == removePosition && dasher->next == NULL){
            free(dasher->lane);
            free(dasher);
            save_lanes(dasher);
            return(0);
        }

        if(iterator->position == removePosition && dasher->position == removePosition){
            dasher = iterator->next;
            break;
        }else if(iterator->position == removePosition){
            prev->next = iterator->next;
            break;
        }else{
            prev = iterator;
            iterator = iterator->next;
        }
    }
    if(list_empty(iterator)){
        fprintf(stderr, "dsh: lane position '%s' does not exist\n", argv);
        free_lanes(dasher);
        return (-1);
    }

    free(iterator->lane);
    free(iterator);

    save_lanes(dasher);
    free_lanes(dasher);
    return (0);
}

void list_command(list *dasher){
    list *iterator = dasher;
    if(list_empty(dasher)) {fprintf(stderr, "No lanes have been set\n");}

    while(!list_empty(iterator)){
        fprintf(stdout, "%d: %s\n", iterator->position, iterator->lane);
        iterator = iterator->next;
    }

    free_lanes(dasher);
}

int dash_command(list *dasher, char *argv){
    int dashTo = atoi(argv);
    if(dashTo >= MAX_LANES){
        fprintf(stderr, "dsh: position '%d' does not exist\n\tOnly '0' to '%d' lanes available\n", dashTo, (MAX_LANES - 1));
        free_lanes(dasher);
        return (-1);
    }
    list *iterator = dasher;
    while(!list_empty(iterator)){
        if(iterator->position == dashTo) {break;}
        iterator = iterator->next;
    }
    if(list_empty(iterator)){
        fprintf(stderr, "dsh: lane '%d' does not exist check 'dsh h'\n", dashTo);
        free_lanes(dasher);
        return (-1);
    }
    
    fprintf(stdout, "%s\n", iterator->lane);
    free_lanes(dasher);
    return (0);
}

void help_command(){
    fprintf(stdout, "Usage: dsh [a] [rm] [ls] [lane index]\n\t   [mv] [h] [sort]\n\n");
    fprintf(stdout, "\ta\t adds current working directory to list of lanes\n");
    fprintf(stdout, "\trm\t removes [lane index] from list of lanes\n");
    fprintf(stdout, "\tls\t list all currently saved lanes and their positions\n");
    fprintf(stdout, "   [lane index]\t 'dashes' to lane saved at specific index (changes directory)\n");
    fprintf(stdout, "\tmv\t moves lane from current index position to next index position\n");
}

void move_command(list **dasher, char **argv){
    int oldPosition = (int) argv[2][0] - '0';
    int newPosition = (int) argv[3][0] - '0';
    
    if(oldPosition > 4 || newPosition > 4){
        fprintf(stderr, "dsh: maximum position index = 4\n");
        free_lanes(*dasher);
        return;
    }
    move((*dasher), oldPosition, newPosition);
    sort(&(*dasher));
    save_lanes((*dasher));
    free_lanes((*dasher));
}










