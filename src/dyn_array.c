#include "dyn_array.h"
#include <stdlib.h>
#include <stdio.h>

dyn_array create_empty_dyn_array(){

    int* data = calloc(MIN_SIZE, sizeof(int));
    dyn_array out;
    out.data = data;
    out.size = 0;
    out.mem_size = MIN_SIZE;

    return out;
}

void append(dyn_array *tab, int value){
    //printf("%i %i %i \n", tab->size, tab->mem_size, value);
    if (tab->size < tab->mem_size){
        printf("%i %i %i \n", tab->size, tab->mem_size, value);
        tab->data[tab->size] = value;
        tab->size++;
        return;
    }
    //printf("%i %i %i \n", tab->size, tab->mem_size, value);

    tab->data = realloc((void *) tab->data, tab->mem_size * 2);
    tab->data[tab->size] = value;
    tab->mem_size *= 2;
    tab->size++;
}

int pop(dyn_array *tab){
    /*pops the last element of the given dynamic array*/
    if (tab->size == 0){
        perror("trying to remove element from empty dynamic array\n");
        exit(EXIT_FAILURE);
    }
    int value = tab->data[tab->size - 1];
    tab->size--;
    if (tab->size * 2 < tab->mem_size && tab->mem_size > 5){
        tab->data = realloc((void *) tab->data, tab->mem_size * 2);
        tab->mem_size /= 2;
    }
    return value;
}

void free_dyn_array(dyn_array tab){

    free(tab.data);
}
