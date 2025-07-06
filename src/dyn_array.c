#include "dyn_array.h"
#include "enemy.h"
#include <stdlib.h>
#include <stdio.h>


dyn_array create_empty_dyn_array(){

    attack* attack_queue = calloc(MIN_SIZE, sizeof(attack));
    dyn_array out;
    out.attack_queue = attack_queue;
    out.size = 0;
    out.mem_size = MIN_SIZE;

    return out;
}

void append(dyn_array *tab, attack value){
    if (tab->size < tab->mem_size){
        tab->attack_queue[tab->size] = value;
        tab->size++;
        return;
    }

    tab->attack_queue = realloc((void *) tab->attack_queue, tab->mem_size * 2 * sizeof(attack));
    tab->attack_queue[tab->size] = value;
    tab->mem_size *= 2;
    tab->size++;
}

attack pop(dyn_array *tab){
    /*pops the last element of the given dynamic array*/
    if (tab->size == 0){
        perror("trying to remove element from empty dynamic array\n");
        exit(EXIT_FAILURE);
    }
    attack value = tab->attack_queue[tab->size - 1];
    tab->size--;
    if (tab->size * 4 < tab->mem_size && tab->mem_size > 5){
        tab->attack_queue = realloc((void *) tab->attack_queue, tab->mem_size * 2);
        tab->mem_size /= 2;
    }
    return value;
}

void free_dyn_array(dyn_array tab){
    free(tab.attack_queue);
}
