#include "display.h"

#ifndef PLAYER_H
#define PLAYER_H

typedef struct player_s{
	int x;
	int y;
	int max_health;
	int health;
	int max_stamina;
	int stamina;

	int aiming;
} player;

int move_player(pixel **screen, player *prota, char input, screen_section play_area, screen_section enemy_locations[3]);

void update_health_bar(pixel **screen, player prota, screen_section health_bar);

void update_stamina_bar(pixel **screen, player prota, screen_section stamina_bar);

player init_player(int x, int y, int max_health, int max_stamina);

void change_aim(pixel **screen, player* prota, screen_section enemy_locations[3], int change);

#endif