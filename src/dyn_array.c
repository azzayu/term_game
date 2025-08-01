#include "dyn_array.h"
#include "enemy.h"
#include "display_cst.h"
#include "structs.h"
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
        tab->attack_queue = realloc((void *) tab->attack_queue, sizeof(attack) * (tab->mem_size / 2));
        tab->mem_size /= 2;
    }
    return value;
}

void free_dyn_array(dyn_array tab){
    free(tab.attack_queue);
}

static void internal_sort(attack* attack_queue, int start, int end){

    if (end == start || start + 1 == end){
        return;
    }


    if (end == start + 2){
        if (attack_queue[start].turn < attack_queue[end - 1].turn){
            attack temp = attack_queue[start];
            attack_queue[start] = attack_queue[end - 1];
            attack_queue[end - 1] = temp;
        }

        return;
    }
    

    int smaller_processed = start;
    int bigger_processed = end - 2;

    int pivot_value = attack_queue[end - 1].turn;

    while(smaller_processed < bigger_processed){
        if (attack_queue[smaller_processed].turn < pivot_value){
            attack temp = attack_queue[smaller_processed];
            attack_queue[smaller_processed] = attack_queue[bigger_processed];
            attack_queue[bigger_processed] = temp;
            bigger_processed--;
        } else {
            smaller_processed++;
        }
    }

    if (attack_queue[end - 1].turn > attack_queue[bigger_processed].turn){
        attack temp = attack_queue[end - 1];
        attack_queue[end - 1] = attack_queue[bigger_processed];
        attack_queue[bigger_processed] = temp;
    } else {
        smaller_processed++;
    }
    
    /*
    printf("%i %i %i %i \n array :", start, smaller_processed, bigger_processed + 1, end);

    for(int i = start; i < end; i++){
        if (i == bigger_processed){
            printf("%s", RED);
        }
        printf("%i%s ", attack_queue[i].turn, WHITE);
    }

    printf("\n");
    */

    internal_sort(attack_queue, start, smaller_processed);
    internal_sort(attack_queue, bigger_processed + 1, end);
}

void sort(dyn_array *tab){
    internal_sort(tab->attack_queue, 0, tab->size);
}

void print_dyn_array(dyn_array tab){

    printf("%s size : %d, mem size : %d\n", WHITE, tab.size, tab.mem_size);
    for (int i = 0; i < tab.mem_size; i++){
        if (tab.size == i){
            printf("%s", RED);
        }
        printf("(t: %i, d: %i)", tab.attack_queue[i].turn, tab.attack_queue[i].damage);
    }
    printf("%s", WHITE);
    printf("\n \n");
}
