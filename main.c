#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "display.h"
#include "player.h"
#include "enemy.h"

int main(){
	
	srand(time(NULL));

	int width = 30;
	int height = 40;

	screen_section play_area;

	play_area.x_min = 1;
	play_area.x_max = width - 1;
	play_area.y_min = height / 2 + 1;
	play_area.y_max = height - 1;
	play_area.width = play_area.x_max - play_area.x_min;
	play_area.height = play_area.y_max - play_area.y_min;

	player prota;
	prota.x = (play_area.x_max - play_area.x_min) / 2 + play_area.x_min;
	prota.y = (play_area.y_max - play_area.y_min) / 2 + play_area.y_min;
	prota.max_health = 20;
	prota.health = prota.max_health;
	prota.max_stamina = 20;
	prota.stamina = prota.max_stamina;
 
	pixel **screen = init_screen(width, height, play_area);
	screen[prota.y][prota.x].layer[0] = 1;

	screen_section health_bar;
	health_bar.x_min = width - 8;
	health_bar.x_max = width - 1;
	health_bar.y_min = 3;
	health_bar.y_max = 4;
	health_bar.width = health_bar.x_max - health_bar.x_min;
	health_bar.height = health_bar.y_max - health_bar.y_min;

	screen_section stamina_bar;
	stamina_bar.x_min = width - 8;
	stamina_bar.x_max = width - 1;
	stamina_bar.y_min = 7;
	stamina_bar.y_max = 8;
	stamina_bar.width = stamina_bar.x_max - stamina_bar.x_min;
	stamina_bar.height = stamina_bar.y_max - stamina_bar.y_min;

	update_health_bar(screen, prota, health_bar);
	update_stamina_bar(screen, prota, stamina_bar);

	while (prota.health > 0) {
		print_screen(screen, width, height);
		char input;
		scanf("%c",&input);
		int has_moved = move_player(screen, &prota, input, width, height, play_area);
		if (has_moved) {
			update_attacks(screen, width, height, &prota, play_area);
			add_attack(screen, play_area);
			update_health_bar(screen, prota, health_bar);
			update_stamina_bar(screen, prota, stamina_bar);
		}
	}
	free_screen(screen, width, height);
	return EXIT_SUCCESS;
}