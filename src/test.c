#include "dyn_array.h"
#include "display_cst.h"
#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>


void print_dyn_array(dyn_array tab){

    printf("%s size : %d, mem size : %d\n", WHITE, tab.size, tab.mem_size);
    for (int i = 0; i < tab.mem_size; i++){
        if (tab.size == i){
            printf("%s", RED);
        }
        printf("%i ", tab.attack_queue[i].turn);
    }
    printf("WHITE \n \n");
}


int main(){
    
    dyn_array tab = create_empty_dyn_array();
    print_dyn_array(tab);
    for (int i = 0; i < 21; i++){
        attack data;
        data.x = 0;
        data.y = 0;
        data.damage = 0;
        data.turn = i;
        append(&tab, data);
        print_dyn_array(tab);
    }

    for (int i = 0; i < 21; i++){
        pop(&tab);
        print_dyn_array(tab);
    }

    free_dyn_array(tab);
    return EXIT_SUCCESS;
}