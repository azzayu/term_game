#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "enemy.h"

int main(){
	
	srand(time(NULL));

	int width = 30;
	int height = 40;

	screen_section play_area = init_screen_section(1, height / 2, width - 1, height - 1);

	player prota = init_player((play_area.x_max - play_area.x_min) / 2 + play_area.x_min, (play_area.y_max - play_area.y_min) / 2 + play_area.y_min, 20, 20);
 
	pixel **screen = init_screen(width, height, play_area);
	screen[prota.y][prota.x].layer[0] = 1;

	screen_section health_bar = init_screen_section(width - 8, 3, width - 1, 4);

	screen_section stamina_bar = init_screen_section(width - 8, 7, width - 1, 8);

	update_health_bar(screen, prota, health_bar);
	update_stamina_bar(screen, prota, stamina_bar);

	text_section health = init_text(width - 8, width - 1, 1, "HEALTH", 6);
	text_section stamina = init_text(width - 8, width - 1, 5, "STAMINA", 7);

	text_section *all_text = malloc(sizeof(text_section) * 3);

	all_text[1] = health;
	all_text[2] = stamina;

	screen[health.y][health.x_min].layer[LAYER_TEXT] = 1;
	
	for(int i = health.x_min + 1 ; i < health.x_max ; i++){
		screen[health.y][i].layer[LAYER_TEXT_BEFORE] = 1;
	}

	screen[stamina.y][stamina.x_min].layer[LAYER_TEXT] = 2;
	
	for(int i = stamina.x_min + 1 ; i < stamina.x_max ; i++){
		screen[stamina.y][i].layer[LAYER_TEXT_BEFORE] = 1;
	}

	while (prota.health > 0) {
		print_screen(screen, width, height, all_text);
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
	free(all_text);
	return EXIT_SUCCESS;
}