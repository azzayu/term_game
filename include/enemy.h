#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "dyn_array.h"
#include "structs.h"

#define NB_ENEMY_TYPES 9

void add_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, player prota, int current_turn);

void update_attacks(pixel **screen, player *prota, screen_section play_area, dyn_array *tab, int current_turn);

void update_enemy_health_bar(pixel **screen, enemy monster, screen_section health_bar);

void update_enemy_name(text_section *name_place, enemy monster);

void update_enemy_location(pixel **screen, enemy *current_enemy, screen_section enemy_locations[3]);

enemy create_enemy(pixel **screen, screen_section enemy_locations[3], int enemies_defeated);

void clear_attacks(pixel **screen, screen_section play_area, dyn_array *tab);

int get_attack_damage(enemy current_enemy, enum attack_types attack);

void append_attack(screen_section play_area, dyn_array *tab, int x, int y, int turn, int damage);

#endif
