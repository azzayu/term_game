#ifndef ATTACKS_H
#define ATTACKS_H

#include "structs.h"
#include "enemy.h"
#include <stdlib.h>

void slash_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void spike_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void meteor_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void bouncy_ball(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void twinkles_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void stab_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void tail_slap_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void fire_breath_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

#endif
