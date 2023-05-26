#ifndef DSH_H
#define DSH_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct list{
    unsigned int position;
    char *lane;
    struct list *next;
}
list;

#define MAX_LANES 5
#define KILOBYTE 1024
/* lane_functions.c  */
bool grab_lane(list **dasher);
bool save_lanes(list *dasher);
bool load_lanes(list **dasher);
/* list_functions.c */
char *laneAt(list *dasher, int index);
bool append(list **dasher, char *lane);
#endif
