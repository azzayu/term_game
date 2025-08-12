#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "enemy.h"
#include "display.h"
#include "player.h"
#include "display_cst.h"
#include "dyn_array.h"
#include "structs.h"

screen_section *create_enemy_locations()
{

	screen_section *enemy_locations = malloc(sizeof(screen_section) * 3);

	// initialises the enemy display boxes' location on the screen
	for (int i = 0; i < 3; i++)
	{
		int x_min = 3 + 8 * i;
		int y_min = 9;
		int x_max = 2 + 8 * (i + 1);
		int y_max = 16;
		enemy_locations[i] = init_screen_section(x_min, y_min, x_max, y_max);
	}

	return enemy_locations;
}

player initialise_player(screen_section play_area)
{
	int middle_play_area_x = (play_area.x_max - play_area.x_min) / 2 + play_area.x_min;
	int middle_play_area_y = (play_area.y_max - play_area.y_min) / 2 + play_area.y_min;
	int max_health = 20;
	int max_stamina = 100;

	player prota = init_player(middle_play_area_x, middle_play_area_y, max_health, max_stamina);

	return prota;
}

screen_section initialise_health_bar(int width)
{
	int health_bar_x_min = width - 8;
	int health_bar_y_min = 3;
	int health_bar_x_max = width - 1;
	int health_bar_y_max = 4;

	screen_section health_bar = init_screen_section(health_bar_x_min, health_bar_y_min, health_bar_x_max, health_bar_y_max);

	return health_bar;
}

screen_section initialise_stamina_bar(int width)
{
	int stamina_bar_x_min = width - 8;
	int stamina_bar_y_min = 7;
	int stamina_bar_x_max = width - 1;
	int stamina_bar_y_max = 8;

	screen_section stamina_bar = init_screen_section(stamina_bar_x_min, stamina_bar_y_min, stamina_bar_x_max, stamina_bar_y_max);

	return stamina_bar;
}

screen_section initialise_exp_bar(int width)
{
	int exp_bar_x_min = width - 16;
	int exp_bar_y_min = 3;
	int exp_bar_x_max = width - 8;
	int exp_bar_y_max = 4;

	screen_section stamina_bar = init_screen_section(exp_bar_x_min, exp_bar_y_min, exp_bar_x_max, exp_bar_y_max);

	return stamina_bar;
}

text_section **initialise_all_text(pixel **screen, int width)
{
	int health_text_x_min = width - 8;
	int health_text_x_max = width - 1;
	int health_text_y = 1;
	int health_text_length = 6;

	int stamina_text_x_min = width - 8;
	int stamina_text_x_max = width - 1;
	int stamina_text_y = 5;
	int stamina_text_length = 7;

	int enemy_name_x_min = 1;
	int enemy_name_x_max = 10;
	int enemy_name_y = 1;
	int enemy_name_length = 10;

	int exp_text_x_min = width - 16;
	int exp_text_x_max = width - 14;
	int exp_text_y = 1;
	int exp_text_length = 3;

	text_section *health = init_text(health_text_x_min, health_text_x_max, health_text_y, "HEALTH", health_text_length);
	text_section *stamina = init_text(stamina_text_x_min, stamina_text_x_max, stamina_text_y, "STAMINA", stamina_text_length);
	text_section *enemy_name = init_text(enemy_name_x_min, enemy_name_x_max, enemy_name_y, "enemy name", enemy_name_length);
	text_section *exp = init_text(exp_text_x_min, exp_text_x_max, exp_text_y, "EXP", exp_text_length);

	int nb_text_sections = 5;

	text_section **all_text = malloc(sizeof(text_section) * nb_text_sections);

	all_text[1] = health;
	all_text[2] = stamina;
	all_text[3] = enemy_name;
	all_text[4] = exp;

	for (int i = 1; i < nb_text_sections; i++)
	{
		screen[all_text[i]->y][all_text[i]->x_min].layer[LAYER_TEXT] = i;
		for (int j = all_text[i]->x_min + 1; j < all_text[i]->x_max; j++)
		{
			screen[all_text[i]->y][j].layer[LAYER_TEXT_BEFORE] = i;
		}
	}

	return all_text;
}

screen_section initialise_enemy_health_bar()
{
	int enemy_health_bar_x_min = 3;
	int enemy_health_bar_y_min = 18;
	int enemy_health_bar_x_max = 26;
	int enemy_health_bar_y_max = 19;

	screen_section enemy_health = init_screen_section(enemy_health_bar_x_min, enemy_health_bar_y_min, enemy_health_bar_x_max, enemy_health_bar_y_max);

	return enemy_health;
}

int main()
{

	srand(time(NULL));

	int width = 30;
	int height = 40;
	int turn = 0;
	int enemies_defeated = 0;

	screen_section *enemy_locations = create_enemy_locations();

	screen_section play_area = init_screen_section(1, height / 2, width - 1, height - 1);

	player prota = initialise_player(play_area);

	pixel **screen = init_screen(width, height, play_area, enemy_locations);
	screen[prota.y][prota.x].layer[LAYER_PLAYER] = 1;

	screen_section health_bar = initialise_health_bar(width);
	screen_section stamina_bar = initialise_stamina_bar(width);
	screen_section exp_bar = initialise_exp_bar(width);

	update_health_bar(screen, prota, health_bar);
	update_stamina_bar(screen, prota, stamina_bar);
	update_exp_bar(screen, prota, exp_bar);

	int nb_text_sections = 5;
	text_section **all_text = initialise_all_text(screen, width);

	change_aim(screen, &prota, enemy_locations, 0);

	enemy current_enemy = create_enemy(screen, enemy_locations, enemies_defeated);

	screen_section enemy_health = initialise_enemy_health_bar();

	update_enemy_health_bar(screen, current_enemy, enemy_health);

	update_enemy_name(all_text[3], current_enemy);

	dyn_array tab = create_empty_dyn_array();

	print_screen(screen, width, height, all_text);

	while (prota.health > 0)
	{
		while (current_enemy.health > 0 && prota.health > 0)
		{
			// printf("turn : %i\n", turn);
			char input = getchar();
			// scanf("%c",&input);
			int has_moved = move_player(screen, &prota, input, play_area, enemy_locations, &current_enemy);
			while (has_moved > 0)
			{
				turn += 1;
				update_attacks(screen, &prota, play_area, &tab, turn);
				add_attack(play_area, current_enemy, &tab, turn);
				update_health_bar(screen, prota, health_bar);
				update_stamina_bar(screen, prota, stamina_bar);
				update_enemy_health_bar(screen, current_enemy, enemy_health);
				update_enemy_location(screen, &current_enemy, enemy_locations);
				print_screen(screen, width, height, all_text);
				// print_dyn_array(tab);
				has_moved--;
			}
		}

		if (prota.health <= 0)
		{
			break;
		}

		enemies_defeated++;
		int current_level = prota.level;

		gain_exp(&prota, current_enemy.enemy_type.base_exp_reward);
		update_exp_bar(screen, prota, exp_bar);
		clear_attacks(screen, play_area, &tab);
		print_screen(screen, width, height, all_text);

		if (current_level != prota.level)
		{
			printf("you leveled up! level : %i -> %i\n", current_level, prota.level);
		}

		printf("You won enter q to quit and c to continue\n");

		int chose_to_continue = 1;
		while (chose_to_continue)
		{
			char input = getchar();

			if (input == 'q')
			{
				printf("Hope you had fun!\n");
				return EXIT_SUCCESS;
			}
			else if (input == 'c')
			{
				chose_to_continue = 0;
			}
			else
			{
				continue;
			}
		}

		current_enemy = create_enemy(screen, enemy_locations, enemies_defeated);
		update_enemy_health_bar(screen, current_enemy, enemy_health);
		update_enemy_name(all_text[3], current_enemy);
		print_screen(screen, width, height, all_text);
	}

	printf("GAME OVER \n\n");

	free_dyn_array(tab);
	free(enemy_locations);
	free_screen(screen, height);
	for (int i = 0; i < nb_text_sections; i++)
	{
		free(all_text[i]);
	}
	free(all_text);
	return EXIT_SUCCESS;
}
