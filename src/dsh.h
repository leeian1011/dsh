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



/* lane_functions.c  */
int grab_lane(list **dasher);
int save_lanes(list *dasher);

/* list_functions.c */
char *laneAt(list *dasher, int index);
bool append(list **dasher, char *lane);
#endif
