#include "dyn_array.h"
#include "display_cst.h"
#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    
    dyn_array tab = create_empty_dyn_array();
    print_dyn_array(tab);
    for (int i = 0; i < 21; i++){
        attack data;
        data.x = 0;
        data.y = 0;
        data.damage = 0;
        data.turn = (i * 21) % 4;
        append(&tab, data);
        print_dyn_array(tab);
    }

    sort(&tab);
    print_dyn_array(tab);

    for (int i = 0; i < 21; i++){
        pop(&tab);
        print_dyn_array(tab);
    }

    free_dyn_array(tab);

    default_test_screen();

    return EXIT_SUCCESS;
}
