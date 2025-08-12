#ifndef PLAYER_H
#define PLAYER_H

#include "display.h"
#include "structs.h"

int move_player(pixel **screen, player *prota, char input, screen_section play_area, screen_section enemy_locations[3], enemy *current_enemy);

void update_health_bar(pixel **screen, player prota, screen_section health_bar);

void update_stamina_bar(pixel **screen, player prota, screen_section stamina_bar);

void update_exp_bar(pixel **screen, player prota, screen_section exp_bar);

player init_player(int x, int y, int max_health, int max_stamina);

void change_aim(pixel **screen, player *prota, screen_section enemy_locations[3], int change);

void gain_exp(player *prota, int exp);

#endif
