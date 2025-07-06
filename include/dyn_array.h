#include "enemy.h"

#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#define MIN_SIZE 5

typedef struct dyn_array {

    int mem_size;
    int size;
    attack* attack_queue;

} dyn_array;

dyn_array create_empty_dyn_array();

void append(dyn_array *tab, attack value);

attack pop(dyn_array *tab);

void free_dyn_array(dyn_array tab);

#endif
