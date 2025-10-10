#include "player.h"
#include "display_cst.h"
#include "enemy.h"

int move_player(pixel **screen, player *prota, char input, screen_section play_area, screen_section enemy_locations[3], enemy *current_enemy)
{
	/*
		returns 1 if move succesfull
		0 if not
	*/

	if (input == 'z' && prota->y > play_area.y_min && prota->stamina > 0)
	{
		if (prota->charged == 1)
		{
			prota->charged = 0;
			if (prota->y - 3 > play_area.y_min)
			{
				screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
				prota->y -= 3;
				screen[prota->y][prota->x].colour = VALUE_YELLOW;
				prota->stamina--;
			}
			else
			{
				screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
				prota->y = play_area.y_min;
				screen[prota->y][prota->x].colour = VALUE_YELLOW;
				prota->stamina--;
			}
			return 1;
		}
		else
		{
			screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
			prota->y -= 1;
			screen[prota->y][prota->x].colour = VALUE_YELLOW;
			prota->stamina--;
			return 1;
		}
	}

	if (input == 's' && prota->y < play_area.y_max - 1 && prota->stamina > 0)
	{
		if (prota->charged == 1)
		{
			prota->charged = 0;
			if (prota->y + 3 < play_area.y_max - 1)
			{
				screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
				prota->y += 3;
				screen[prota->y][prota->x].colour = VALUE_YELLOW;
				prota->stamina--;
			}
			else
			{
				screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
				prota->y = play_area.y_max - 1;
				screen[prota->y][prota->x].colour = VALUE_YELLOW;
				prota->stamina--;
			}
			return 1;
		}
		else
		{
			screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
			prota->y += 1;
			screen[prota->y][prota->x].colour = VALUE_YELLOW;
			prota->stamina--;
			return 1;
		}
	}

	if (input == 'd' && prota->x < play_area.x_max - 1 && prota->stamina > 0)
	{
		if (prota->charged == 1)
		{
			prota->charged = 0;
			if (prota->x + 3 < play_area.x_max - 1)
			{
				screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
				prota->x += 3;
				screen[prota->y][prota->x].colour = VALUE_YELLOW;
				prota->stamina--;
			}
			else
			{
				screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
				prota->x = play_area.x_max - 1;
				screen[prota->y][prota->x].colour = VALUE_YELLOW;
				prota->stamina--;
			}
			return 1;
		}
		else
		{
			screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
			prota->x += 1;
			screen[prota->y][prota->x].colour = VALUE_YELLOW;
			prota->stamina--;
			return 1;
		}
	}

	if (input == 'q' && prota->x > play_area.x_min && prota->stamina > 0)
	{
		if (prota->charged == 1)
		{
			prota->charged = 0;
			if (prota->x - 3 > play_area.x_min)
			{
				screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
				prota->x -= 3;
				screen[prota->y][prota->x].colour = VALUE_YELLOW;
				prota->stamina--;
			}
			else
			{
				screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
				prota->x = play_area.x_min + 1;
				screen[prota->y][prota->x].colour = VALUE_YELLOW;
				prota->stamina--;
			}
			return 1;
		}
		else
		{
			screen[prota->y][prota->x].colour = VALUE_BRIGHT_CYAN;
			prota->x -= 1;
			screen[prota->y][prota->x].colour = VALUE_YELLOW;
			prota->stamina--;
			return 1;
		}
	}

	if (input == 'w' || input == ' ')
	{
		// counts as resting
		prota->stamina += 3;
		if (prota->stamina > prota->max_stamina)
		{
			prota->stamina = prota->max_stamina;
		}
		return 1;
	}

	if (input == 'a' && prota->aiming != 0)
	{
		change_aim(screen, prota, enemy_locations, -1);
		return 1;
	}

	if (input == 'e' && prota->aiming != 2)
	{
		change_aim(screen, prota, enemy_locations, 1);
		return 1;
	}

	if (input == 'r' && prota->stamina > 0 && prota->aiming == current_enemy->location)
	{
		current_enemy->health -= prota->attack;
		prota->stamina--;
		return 1;
	}

	if (input == 'f' && prota->stamina > 5)
	{
		prota->charged = 1;
		prota->stamina -= 4;
		return 0;
	}

	if (input == 'c' && prota->stamina > 10 && prota->health < prota->max_health)
	{
		prota->stamina -= 10;
		prota->health += 2;
		return 3;
	}
	return 0;
}

void update_health_bar(pixel **screen, player prota, screen_section health_bar)
{
	double health_per_block = (double)prota.max_health / (double)health_bar.width;

	for (int j = 0; j < health_bar.width; j++)
	{
		screen[health_bar.y_min][health_bar.x_min + j].colour = VALUE_BLACK;
		screen[health_bar.y_min][health_bar.x_min + j].pixel_type = PIXEL_FULL_BLOCK;
	}

	int i = 0;
	while ((i + 1) * health_per_block <= prota.health)
	{
		screen[health_bar.y_min][health_bar.x_min + i].colour = VALUE_RED;
		i++;
	}

	screen[health_bar.y_min][health_bar.x_min + i].colour = VALUE_RED;

	// displays the last partial bar
	if ((i + 0.75) * health_per_block <= prota.health)
	{	
		screen[health_bar.y_min][health_bar.x_min + i].pixel_type = PIXEL_THREE_QUART_BLOCK;
	}
	else if ((i + 0.5) * health_per_block <= prota.health)
	{	
		
		screen[health_bar.y_min][health_bar.x_min + i].pixel_type = PIXEL_HALF_BLOCK;
	}
	else if ((i + 0.25) * health_per_block <= prota.health)
	{
		screen[health_bar.y_min][health_bar.x_min + i].pixel_type = PIXEL_QUART_BLOCK;
	}
}

void update_exp_bar(pixel **screen, player prota, screen_section exp_bar)
{
	double exp_per_block = (double)prota.exp_to_next_level / (double)exp_bar.width;

	for (int j = 0; j < exp_bar.width; j++)
	{
		screen[exp_bar.y_min][exp_bar.x_min + j].colour = VALUE_BLACK;
		screen[exp_bar.y_min][exp_bar.x_min + j].pixel_type = PIXEL_FULL_BLOCK;
	}

	int i = 0;
	while ((i + 1) * exp_per_block <= prota.exp)
	{
		screen[exp_bar.y_min][exp_bar.x_min + i].colour = VALUE_BRIGHT_YELLOW;
		i++;
	}

	screen[exp_bar.y_min][exp_bar.x_min + i].colour = VALUE_BRIGHT_YELLOW;

	// displays the last partial bar
	if ((i + 0.75) * exp_per_block <= prota.exp)
	{	
		screen[exp_bar.y_min][exp_bar.x_min + i].pixel_type = PIXEL_THREE_QUART_BLOCK;
	}
	else if ((i + 0.5) * exp_per_block <= prota.exp)
	{	
		
		screen[exp_bar.y_min][exp_bar.x_min + i].pixel_type = PIXEL_HALF_BLOCK;
	}
	else if ((i + 0.25) * exp_per_block <= prota.exp)
	{
		screen[exp_bar.y_min][exp_bar.x_min + i].pixel_type = PIXEL_QUART_BLOCK;
	}
}

void update_stamina_bar(pixel **screen, player prota, screen_section stamina_bar)
{
	double stamina_per_block = (double)prota.max_stamina / (double)stamina_bar.width;

	for (int j = 0; j < stamina_bar.width; j++)
	{
		screen[stamina_bar.y_min][stamina_bar.x_min + j].colour = VALUE_BLACK;
		screen[stamina_bar.y_min][stamina_bar.x_min + j].pixel_type = PIXEL_FULL_BLOCK;
	}

	int i = 0;
	while ((i + 1) * stamina_per_block <= prota.stamina)
	{
		screen[stamina_bar.y_min][stamina_bar.x_min + i].colour = VALUE_BLUE;
		i++;
	}

	screen[stamina_bar.y_min][stamina_bar.x_min + i].colour = VALUE_BLUE;

	// displays the last partial bar
	if ((i + 0.75) * stamina_per_block <= prota.stamina)
	{	
		screen[stamina_bar.y_min][stamina_bar.x_min + i].pixel_type = PIXEL_THREE_QUART_BLOCK;
	}
	else if ((i + 0.5) * stamina_per_block <= prota.stamina)
	{	
		
		screen[stamina_bar.y_min][stamina_bar.x_min + i].pixel_type = PIXEL_HALF_BLOCK;
	}
	else if ((i + 0.25) * stamina_per_block <= prota.stamina)
	{
		screen[stamina_bar.y_min][stamina_bar.x_min + i].pixel_type = PIXEL_QUART_BLOCK;
	}
}

player init_player(int x, int y, int max_health, int max_stamina)
{
	player prota;

	prota.x = x;
	prota.y = y;
	prota.max_health = max_health;
	prota.max_stamina = max_stamina;
	prota.charged = 0;

	prota.health = max_health;
	prota.stamina = max_stamina;

	prota.aiming = 1;

	prota.level = 1;
	prota.exp = 0;
	prota.exp_to_next_level = 5;

	prota.attack = 1;

	return prota;
}

void change_aim(pixel **screen, player *prota, screen_section enemy_locations[3], int change)
{
	/*
	change is either -1 or 1 checked by move_player
	*/

	int is_selected;

	prota->aiming += change;

	for (int i = 0; i < 3; i++)
	{

		is_selected = 0;
		if (prota->aiming == i)
		{
			is_selected = 1;
		}

		screen[enemy_locations[i].y_min][enemy_locations[i].x_min].colour = 1 + is_selected * (VALUE_YELLOW - VALUE_BRIGHT_WHITE);
		screen[enemy_locations[i].y_min][enemy_locations[i].x_max].colour = 1 + is_selected * (VALUE_YELLOW - VALUE_BRIGHT_WHITE);
		screen[enemy_locations[i].y_max][enemy_locations[i].x_max].colour = 1 + is_selected * (VALUE_YELLOW - VALUE_BRIGHT_WHITE);
		screen[enemy_locations[i].y_max][enemy_locations[i].x_min].colour = 1 + is_selected * (VALUE_YELLOW - VALUE_BRIGHT_WHITE);

		for (int j = 1; j < enemy_locations[i].width; j++)
		{
			screen[enemy_locations[i].y_min][enemy_locations[i].x_min + j].colour = 1 + is_selected * (VALUE_YELLOW - VALUE_BRIGHT_WHITE);
			screen[enemy_locations[i].y_max][enemy_locations[i].x_min + j].colour = 1 + is_selected * (VALUE_YELLOW - VALUE_BRIGHT_WHITE);
		}

		for (int j = 1; j < enemy_locations[i].height; j++)
		{
		 	screen[enemy_locations[i].y_min + j][enemy_locations[i].x_min].colour = 1 + is_selected * (VALUE_YELLOW - VALUE_BRIGHT_WHITE);
			screen[enemy_locations[i].y_min + j][enemy_locations[i].x_max].colour = 1 + is_selected * (VALUE_YELLOW - VALUE_BRIGHT_WHITE);
		}
	}
}

void gain_exp(player *prota, int exp)
{
	prota->exp += exp;

	while (prota->exp_to_next_level <= prota->exp)
	{
		prota->level += 1;
		int exp_left_to_gain = prota->exp - prota->exp_to_next_level;

		prota->exp_to_next_level += prota->level;
		prota->exp = exp_left_to_gain;

		prota->max_health += 1;
		prota->health += 1;
		if (prota->health > prota->max_health)
		{
			prota->health = prota->max_health;
		}
		prota->max_stamina += 5;
		prota->stamina += 5;
		if (prota->stamina > prota->max_stamina)
		{
			prota->stamina = prota->max_stamina;
		}

		if (prota->level % 3 == 0)
		{
			prota->attack += 1;
		}
	}
}
