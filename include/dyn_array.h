#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#define MIN_SIZE 5

#include "structs.h"

dyn_array create_empty_dyn_array();

void append(dyn_array *tab, attack value);

attack pop(dyn_array *tab);

void free_dyn_array(dyn_array tab);

void sort(dyn_array *tab);

void print_dyn_array(dyn_array tab);

#endif
