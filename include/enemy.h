#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "dyn_array.h"
#include "structs.h"

#define NB_ENEMY_TYPES 4

void add_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn);

void update_attacks(pixel **screen, player *prota, screen_section play_area, dyn_array *tab, int current_turn);

void update_enemy_health_bar(pixel **screen, enemy monster, screen_section health_bar);

void update_enemy_name(text_section *name_place, enemy monster);

enemy create_enemy();

#endif