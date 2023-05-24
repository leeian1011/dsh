#ifndef DSH_H
#define DSH_H

typedef struct list{
    unsigned int position;
    char *lane;
    struct list *next;
}
list;

/* dir_functions.c  */
int grab_dir(list *dasher);

/* save_dir.c */
int save_dir(list *dasher);

/* list_functions.c */
char *laneAt(list *dasher, int index);

#endif
