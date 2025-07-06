#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "enemy.h"
#include "display.h"
#include "player.h"
#include "display_cst.h"

int main(){
	
	srand(time(NULL));

	int width = 30;
	int height = 40;

	screen_section enemy_locations[3];

	for (int i = 0 ; i < 3; i++){
		enemy_locations[i] = init_screen_section(3 + 8 * i, 9, 2 + 8 * (i + 1), 16);
	}

	screen_section play_area = init_screen_section(1, height / 2, width - 1, height - 1);

	player prota = init_player((play_area.x_max - play_area.x_min) / 2 + play_area.x_min, (play_area.y_max - play_area.y_min) / 2 + play_area.y_min, 20, 100);
 
	pixel **screen = init_screen(width, height, play_area, enemy_locations);
	screen[prota.y][prota.x].layer[LAYER_PLAYER] = 1;

	screen_section health_bar = init_screen_section(width - 8, 3, width - 1, 4);

	screen_section stamina_bar = init_screen_section(width - 8, 7, width - 1, 8);

	update_health_bar(screen, prota, health_bar);
	update_stamina_bar(screen, prota, stamina_bar);

	text_section *health = init_text(width - 8, width - 1, 1, "HEALTH", 6);
	text_section *stamina = init_text(width - 8, width - 1, 5, "STAMINA", 7);
	text_section *enemy_name = init_text(1, 20, 1, "enemy name", 10);

	int nb_text_sections = 4;

	text_section **all_text = malloc(sizeof(text_section) * nb_text_sections);

	all_text[1] = health;
	all_text[2] = stamina;
	all_text[3] = enemy_name;

	for (int i = 1; i < nb_text_sections; i++){
		screen[all_text[i]->y][all_text[i]->x_min].layer[LAYER_TEXT] = i;
		for(int j = all_text[i]->x_min + 1 ; j < all_text[i]->x_max ; j++){
			screen[all_text[i]->y][j].layer[LAYER_TEXT_BEFORE] = i;
		}
	}

	change_aim(screen, &prota, enemy_locations, 0);

	enemy current_enemy = create_enemy();

	screen_section enemy_health = init_screen_section(3, 18, 26, 19);
	
	update_enemy_health_bar(screen, current_enemy, enemy_health);

	update_enemy_name(enemy_name, current_enemy);

	while (prota.health > 0) {
		print_screen(screen, width, height, all_text);
		char input = getchar();
		//scanf("%c",&input);
		int has_moved = move_player(screen, &prota, input, play_area, enemy_locations);
		if (has_moved) {
			update_attacks(screen, &prota, play_area);
			add_attack(screen, play_area, current_enemy);
			update_health_bar(screen, prota, health_bar);
			update_stamina_bar(screen, prota, stamina_bar);
			update_enemy_health_bar(screen, current_enemy, enemy_health);
		}
	}

	system("clear");
	printf("GAME OVER \n\n\n");

	free_screen(screen, height);
	for (int i = 0; i < nb_text_sections ; i++){
		free(all_text[i]);
	}
	free(all_text);
	return EXIT_SUCCESS;
}