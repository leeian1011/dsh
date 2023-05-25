#ifndef DSH_H
#define DSH_H

typedef struct list{
    unsigned int position;
    char *lane;
    struct list *next;
}
list;



/* lane_functions.c  */
int grab_lane(list *dasher);
int save_lanes(list *dasher);

/* list_functions.c */
char *laneAt(list *dasher, int index);
int append(list *dasher, char *lane);
#endif
