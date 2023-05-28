#include "dsh.h"
#include <ctype.h>

static const char *COMMANDS[MAX_COMMANDS] = {"a", "rm", "ls", "h"};

static bool check_option_digit(char **argv){
    int optionLength = strlen(*++argv);
    char c;
    for(int i = 0; i < optionLength; i++){
        c = (*argv)[i];
        if(!isdigit(c)) {return false;}
    }
    return true;
}


static int check_option_commands(char **argv){
    for(int i = 0; i < MAX_COMMANDS; i++){
        if(strcmp(argv[1], COMMANDS[i]) == 0) {return i;}
    }
    return -1;
}


char get_option(int argc, char **argv){
    char returnedOption = check_option_commands(argv);

    if(check_option_digit(argv)) {return 'g';}
    
    for(int i = 0; i < MAX_COMMANDS; i++){
        if(returnedOption == i) {return i;}
    }
    return '?';
}
    
                
void closest_option(char option){
    fprintf(stderr, "The most similar command is\n");
    for(int i = 0; i < MAX_COMMANDS; i++){
        if(strchr(COMMANDS[i], option) != NULL) {fprintf(stderr, "\t%s\n", COMMANDS[i]);}
    }
}
