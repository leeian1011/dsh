#ifndef DSH_H
#define DSH_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LANES 5 
#define MAX_COMMANDS 6
#define KILOBYTE 1024

typedef struct list{
    unsigned int position;
    char *lane;
    struct list *next;
}
list;


/* lane_functions.c  */
char *set_directory();
bool save_lanes(list *dasher);
void free_lanes(list *dasher);
bool load_lanes(list **dasher);

/* list_functions.c */
int lowest_position(list *dasher);
void create_lane(list *newLane, int position, char *lane);
char *lane_at(list *dasher, int index);
void append(list **dasher, list **newLane);
void remove_at(list *dasher, int position);
void print_list(list *dasher);

/* command_functions.c */
void add_command(list **dasher);

/* options.c */
char get_option(int argc, char **argv);
void closest_option(char option);
#endif
