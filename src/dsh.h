#ifndef DSH_H
#define DSH_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LANES 4
#define MAX_COMMANDS 4
#define KILOBYTE 1024

typedef struct list{
    unsigned int position;
    char *lane;
    struct list *next;
}
list;


/* lane_functions.c  */
bool load_lanes(list **dasher);
bool grab_lane(list **dasher);
bool save_lanes(list *dasher);
void free_lanes(list *dasher);

/* list_functions.c */
char *lane_at(list *dasher, int index);
bool append(list **dasher, char *lane);
void print_list(list *dasher);

/* command_functions.c */
void add_command(list **dasher);

/* options.c */
char get_option(int argc, char **argv);
void closest_option(char option);
#endif
