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

	play_screen play_area;

	play_area.x_min = 1;
	play_area.x_max = width - 1;
	play_area.y_min = height / 2 + 1;
	play_area.y_max = height - 1;
	play_area.width = play_area.x_max - play_area.x_min;
	play_area.height = play_area.y_max - play_area.y_min;

	player prota;
	prota.x = (play_area.x_max - play_area.x_min) / 2 + play_area.x_min;
	prota.y = (play_area.y_max - play_area.y_min) / 2 + play_area.y_min;
	prota.max_health = 5;
	prota.health = prota.max_health;
 
	pixel **screen = init_screen(width, height, play_area);
	screen[prota.y][prota.x].layer[0] = 1;

	while (prota.health > 0) {
		print_screen(screen, width, height);
		char input;
		scanf("%c",&input);
		int has_moved = move_player(screen, &prota, input, width, height, play_area);
		if (has_moved) {
			update_attacks(screen, width, height, &prota, play_area);
			add_attack(screen, play_area);
		}
	}
	free_screen(screen, width, height);
	return EXIT_SUCCESS;
}