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

void small_smash_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void big_smash_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void simple_spiral_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void double_spiral_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void wave_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void direct_slash_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, player prota, int current_turn);

void close_in_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, player prota, int current_turn);

void crumble_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void shatter_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void mist_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void explosion_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void tetris_fall_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void player_circle_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, player prota, int current_turn);

void player_square_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, player prota, int current_turn);

void snake_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

#endif
