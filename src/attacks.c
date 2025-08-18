#include "attacks.h"
#include "structs.h"
#include "structs.h"
#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int distance_2(int x1, int y1, int x2, int y2)
{
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int distance_man(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

double double_abs(double x)
{
	if (x >= 0)
	{
		return x;
	}
	return -1 * x;
}

void slash_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, SLASH);

	int line = rand() % play_area.height;
	int left_right = rand() % 2;
	for (int x = play_area.x_min; x <= play_area.x_max; x++)
	{
		if (left_right)
		{
			append_attack(tab, x, line + play_area.y_min, current_turn + 4 + ((x - play_area.x_min) / 2), damage);
		}
		else
		{
			append_attack(tab, play_area.x_max - x + play_area.x_min - 1, line + play_area.y_min, current_turn + 4 + (x - play_area.x_min) / 2, damage);
		}
	}
}

void spike_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, SPIKES);

	int column = rand() % play_area.width;
	for (int y = play_area.y_min; y <= play_area.y_max; y++)
	{
		append_attack(tab, play_area.x_min + column, play_area.y_max - y + play_area.y_min - 1, current_turn + 4 + y - play_area.y_min, damage);
	}
}

void meteor_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, METEOR);

	int column = rand() % play_area.width;
	for (int y = play_area.y_min; y <= play_area.y_max; y++)
	{
		append_attack(tab, play_area.x_min + column, y, current_turn + 4 + y - play_area.y_min, damage);
	}
}

void bouncy_ball(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, BOUNCY_BALL);

	int x = rand() % play_area.width + play_area.x_min;
	int y = rand() % play_area.height + play_area.y_min;
	int x_dir = (rand() % 2) * 2 - 1;
	int y_dir = (rand() % 2) * 2 - 1;

	for (int i = 0; i < 200; i++)
	{
		for (int x_off_set = 0; x_off_set < 2; x_off_set++)
		{
			for (int y_off_set = 0; y_off_set < 2; y_off_set++)
			{
				if (play_area.x_min <= x + x_off_set && x + x_off_set < play_area.x_max && play_area.y_min <= y + y_off_set && y + y_off_set < play_area.y_max)
				{
					append_attack(tab, x + x_off_set, y + y_off_set, current_turn + i + 4, damage);
				}
			}
		}

		x += x_dir;
		y += y_dir;

		if (x < play_area.x_min || x > play_area.x_max)
		{
			x -= 1 * x_dir;
			y -= 1 * y_dir;
			x_dir *= -1;
			// y_dir *= -1;
		}
		if (y < play_area.y_min || y > play_area.y_max)
		{
			x -= 1 * x_dir;
			y -= 1 * y_dir;
			// x_dir *= -1;
			y_dir *= -1;
		}
	}
}

void twinkles_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, TWINKLES);

	for (int i = 0; i < 5; i++)
	{

		int x_center = rand() % play_area.width + play_area.x_min;
		int y_center = rand() % play_area.height + play_area.y_min;

		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (play_area.x_min <= x + x_center && x + x_center < play_area.x_max && play_area.y_min <= y + y_center && y + y_center < play_area.y_max)
				{
					append_attack(tab, x + x_center, y + y_center, current_turn + 5, damage);
				}
			}
		}
		append_attack(tab, x_center, y_center, current_turn + 4, damage);
	}
}

void stab_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, STAB);

	int x_center = rand() % play_area.width + play_area.x_min;
	int y_center = rand() % play_area.height + play_area.y_min;

	for (int x = -1; x < 2; x++)
	{
		if (play_area.x_min <= x + x_center && x + x_center < play_area.x_max)
		{
			append_attack(tab, x_center + x, y_center, current_turn + 5, damage);
		}
	}
	for (int y = -1; y < 2; y++)
	{
		if (play_area.y_min <= y + y_center && y + y_center < play_area.y_max)
		{
			append_attack(tab, x_center, y_center + y, current_turn + 5, damage);
		}
	}

	append_attack(tab, x_center, y_center, current_turn + 4, damage);
}

void tail_slap_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, TAIL_SLAP);

	int line = rand() % play_area.height;
	int left_right = rand() % 2;
	for (int y = -1; y < 2; y++)
	{
		if (0 <= y + line && y + line < play_area.height)
		{
			for (int x = play_area.x_min; x <= play_area.x_max; x++)
			{
				if (left_right)
				{
					append_attack(tab, x, line + play_area.y_min + y, current_turn + 4 + (x - play_area.x_min) / 2, damage);
				}
				else
				{
					append_attack(tab, play_area.x_max - x + play_area.x_min, line + play_area.y_min + y, current_turn + 4 + (x - play_area.x_min) / 2, damage);
				}
			}
		}
	}
}

void fire_breath_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, FIRE_BREATH);

	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;

	for (int radius = 6; radius > 0; radius--)
	{
		for (int x = center_x - radius + play_area.x_min; x < center_x + radius + play_area.x_min; x++)
		{
			for (int y = center_y - radius + play_area.y_min; y < center_y + radius + play_area.y_min; y++)
			{
				if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max)
				{
					if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) < radius * radius)
					{
						append_attack(tab, x, y, current_turn + radius + 4, damage);
					}
				}
			}
		}
	}
}

void small_smash_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, SMALL_SMASH);

	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;

	for (int radius = 5; radius > 0; radius--)
	{
		for (int x = center_x - radius + play_area.x_min; x < center_x + radius + play_area.x_min; x++)
		{
			for (int y = center_y - radius + play_area.y_min; y < center_y + radius + play_area.y_min; y++)
			{
				if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max)
				{
					if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) < radius * radius)
					{
						if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) >= (radius - 1) * (radius - 1))
						{
							append_attack(tab, x, y, current_turn + radius + 4, damage);
						}
					}
				}
			}
		}
	}
}

void big_smash_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, BIG_SMASH);

	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;

	for (int radius = 50; radius > 0; radius -= 2)
	{
		for (int x = center_x - radius + play_area.x_min; x < center_x + radius + play_area.x_min; x++)
		{
			for (int y = center_y - radius + play_area.y_min; y < center_y + radius + play_area.y_min; y++)
			{
				if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max)
				{
					if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) < radius * radius)
					{
						if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) >= (radius - 1) * (radius - 1))
						{
							append_attack(tab, x, y, current_turn + (radius / 2) + 4, damage);
						}
					}
				}
			}
		}
	}
}

void simple_spiral_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, SIMPLE_SPIRAL);

	int center_x = rand() % play_area.width + play_area.x_min;
	int center_y = rand() % play_area.height + play_area.y_min;

	int attack_pattern[11][11] = {
		{0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
		{0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 9, 0, 6, 6, 6, 6, 6, 6, 7, 0},
		{0, 9, 0, 5, 0, 0, 0, 0, 0, 7, 0},
		{0, 9, 0, 5, 0, 2, 2, 3, 0, 7, 0},
		{0, 9, 0, 5, 0, 1, 0, 3, 0, 7, 0},
		{0, 9, 0, 5, 0, 0, 0, 3, 0, 7, 0},
		{0, 9, 0, 5, 4, 4, 4, 4, 0, 7, 0},
		{0, 9, 0, 0, 0, 0, 0, 0, 0, 7, 0},
		{0, 9, 8, 8, 8, 8, 8, 8, 8, 8, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};

	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			int screen_x = center_x + x - 6;
			int screen_y = center_y + y - 6;

			if (play_area.x_min <= screen_x && screen_x < play_area.x_max && play_area.y_min <= screen_y && screen_y < play_area.y_max)
			{
				if (attack_pattern[y][x] != 0)
				{
					append_attack(tab, screen_x, screen_y, current_turn + 4 + attack_pattern[y][x], damage);
				}
			}
		}
	}
}

void double_spiral_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, DOUBLE_SPIRAL);

	int center_x = rand() % play_area.width + play_area.x_min;
	int center_y = rand() % play_area.height + play_area.y_min;

	int attack_pattern[11][11] = {
		{0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
		{0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 5, 0, 4, 4, 4, 4, 4, 4, 5, 0},
		{0, 5, 0, 3, 0, 0, 0, 0, 0, 5, 0},
		{0, 5, 0, 3, 0, 2, 2, 3, 0, 5, 0},
		{0, 5, 0, 3, 0, 1, 0, 3, 0, 5, 0},
		{0, 5, 0, 3, 2, 2, 0, 3, 0, 5, 0},
		{0, 5, 0, 0, 0, 0, 0, 3, 0, 5, 0},
		{0, 5, 4, 4, 4, 4, 4, 4, 0, 5, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0},
	};

	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			int screen_x = center_x + x - 6;
			int screen_y = center_y + y - 6;

			if (play_area.x_min <= screen_x && screen_x < play_area.x_max && play_area.y_min <= screen_y && screen_y < play_area.y_max)
			{
				if (attack_pattern[y][x] != 0)
				{
					append_attack(tab, screen_x, screen_y, current_turn + 4 + attack_pattern[y][x], damage);
				}
			}
		}
	}
}

void wave_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, DOUBLE_SPIRAL);

	int center_y = rand() % play_area.height + play_area.y_min;

	int y_offset = 0;
	int y_offset_change = 1;

	int counter = 0;

	for (int x = play_area.x_min; x < play_area.x_max; x += 2)
	{
		int y = center_y + y_offset;
		if (play_area.y_min < y && y < play_area.y_max)
		{
			append_attack(tab, x, y, current_turn + 4 + counter, damage);
			append_attack(tab, x + 1, y, current_turn + 4 + counter, damage);
		}

		counter++;

		if (y_offset != 0)
		{
			y_offset_change *= -1;
		}

		y_offset += y_offset_change;
	}
}

void direct_slash_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, player prota, int current_turn)
{
	int damage = get_attack_damage(current_enemy, DIRECT_SLASH);

	int choose_wall = rand() % 4;

	int x_start;
	int y_start;

	switch (choose_wall)
	{
	case 0:
		x_start = rand() % play_area.width + play_area.x_min;
		y_start = play_area.y_min;
		break;
	case 1:
		x_start = rand() % play_area.width + play_area.x_min;
		y_start = play_area.y_max - 1;
		break;
	case 2:
		x_start = play_area.x_min;
		y_start = rand() % play_area.height + play_area.y_min;
		break;
	case 3:
		x_start = play_area.x_max - 1;
		y_start = rand() % play_area.height + play_area.y_min;
		break;
	}

	while (x_start == prota.x)
	{
		x_start = rand() % play_area.width + play_area.x_min;
	}

	while (y_start == prota.y)
	{
		y_start = rand() % play_area.height + play_area.y_min;
	}

	double slope = (double)(prota.y - y_start) / (double)(prota.x - x_start);

	for (int x = play_area.x_min; x < play_area.x_max; x++)
	{

		if (x == x_start)
		{
			continue;
		}

		for (int y = play_area.y_min; y < play_area.y_max; y++)
		{
			double current_slope = (double)(y - y_start) / (double)(x - x_start);
			if (double_abs(current_slope - slope) < 0.1)
			{
				int distance = sqrt(distance_2(x, y, x_start, y_start));
				append_attack(tab, x, y, current_turn + 4 + distance, damage);
			}
		}
	}
}

void close_in_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, player prota, int current_turn)
{
	int damage = get_attack_damage(current_enemy, CLOSE_IN);

	int center_x = prota.x;
	int center_y = prota.y;

	for (int radius = 0; radius < 7; radius++)
	{
		for (int x = center_x - radius; x < center_x + radius; x++)
		{
			for (int y = center_y - radius; y < center_y + radius; y++)
			{
				if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max)
				{
					if (distance_2(x, y, center_x, center_y) < radius * radius)
					{
						if (distance_2(x, y, center_x, center_y) >= (radius - 1) * (radius - 1))
						{
							append_attack(tab, x, y, current_turn + (7 - radius) + 4, damage);
						}
					}
				}
			}
		}
	}
}

void crumble_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, CRUMBLE);

	for (int x = play_area.x_min + 9 * current_enemy.location + 1; x <= play_area.x_min + 9 * (1 + current_enemy.location); x++)
	{
		for (int y = play_area.y_min; y < play_area.y_max; y += 3)
		{
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max)
			{
				append_attack(tab, x, y, current_turn + 4 + ((y - play_area.y_min) / 3), damage);
				if (y + 1 < play_area.y_max)
				{
					append_attack(tab, x, y + 1, current_turn + 4 + ((y - play_area.y_min) / 3), damage);
				}
				if (y + 2 < play_area.y_max)
				{

					append_attack(tab, x, y + 2, current_turn + 4 + ((y - play_area.y_min) / 3), damage);
				}
			}
		}
	}
}

void shatter_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, SHATTER);
	for (int i = 0; i < 3; i++)
	{
		int choose_wall1 = rand() % 4;

		int x_start;
		int y_start;

		int x_end;
		int y_end;

		switch (choose_wall1)
		{
		case 0:
			x_start = rand() % play_area.width + play_area.x_min;
			y_start = play_area.y_min;

			x_end = rand() % play_area.width + play_area.x_min;
			y_end = play_area.y_max;
			break;
		case 1:
			x_start = rand() % play_area.width + play_area.x_min;
			y_start = play_area.y_max;

			x_end = rand() % play_area.width + play_area.x_min;
			y_end = play_area.y_min;
			break;
		case 2:
			x_start = play_area.x_min;
			y_start = rand() % play_area.height + play_area.y_min;

			x_end = play_area.x_max;
			y_end = rand() % play_area.height + play_area.y_min;
			break;
		case 3:
			x_start = play_area.x_max;
			y_start = rand() % play_area.height + play_area.y_min;

			x_end = play_area.x_min;
			y_end = rand() % play_area.height + play_area.y_min;
			break;
		}

		while (x_end == x_start)
		{
			x_end = rand() % play_area.width + play_area.x_min;
		}

		double slope = (double)(y_end - y_start) / (double)(x_end - x_start);

		for (int x = play_area.x_min; x < play_area.x_max; x++)
		{
			if (x == x_start)
			{
				continue;
			}
			for (int y = play_area.y_min; y < play_area.y_max; y++)
			{
				double current_slope = (double)(y - y_start) / (double)(x - x_start);
				if (double_abs(current_slope - slope) < 0.1)
				{
					int distance = sqrt(distance_2(x, y, x_start, y_start));
					append_attack(tab, x, y, current_turn + 4 + distance, damage);
				}
			}
		}
	}
}

void mist_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, MIST);

	for (int x = play_area.x_min; x < play_area.x_max; x++)
	{
		for (int y = play_area.y_min; y < play_area.y_max; y++)
		{
			append_attack(tab, x, y, current_turn + 4, damage);
		}
	}
}

void explosion_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, EXPLOSION);

	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;

	for (int radius = 5; radius > 0; radius--)
	{
		for (int x = center_x - radius + play_area.x_min; x < center_x + radius + play_area.x_min; x++)
		{
			for (int y = center_y - radius + play_area.y_min; y < center_y + radius + play_area.y_min; y++)
			{
				if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max)
				{
					if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) < radius * radius)
					{
						if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) >= (radius - 1) * (radius - 1))
						{
							append_attack(tab, x, y, current_turn + radius + 4, damage);
						}
					}
				}
			}
		}
	}

	int radius = 7;

	for (int x = center_x - radius + play_area.x_min; x < center_x + radius + play_area.x_min; x++)
	{
		for (int y = center_y - radius + play_area.y_min; y < center_y + radius + play_area.y_min; y++)
		{
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max)
			{
				if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) < radius * radius)
				{
					if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) >= (radius - 1) * (radius - 1))
					{
						append_attack(tab, x, y, current_turn + radius + 4 - 1, damage);
					}
				}
			}
		}
	}

	for (int x = play_area.x_min; x < play_area.x_max; x++)
	{
		append_attack(tab, x, center_y + play_area.y_min, current_turn + radius + 4 - 1, damage);
	}

	for (int y = play_area.y_min; y < play_area.y_max; y++)
	{
		append_attack(tab, center_x + play_area.x_min, y, current_turn + radius + 4 - 1, damage);
	}
}

void tetris_fall_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, TETRIS_FALL);

	int x = rand() % play_area.width + play_area.x_min;

	int attack_patterns[18][4][4] = {
		{{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // long hori
		{{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}, // long vert
		{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // pyramid up
		{{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // pyramid down
		{{1, 0, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}, // pyramid right
		{{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, // pyramid left
		{{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}, // z 1
		{{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, // z 2
		{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // z 3
		{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // z 4
		{{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}, // all L
		{{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
		{{1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{{1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
		{{1, 1, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
	};

	int pattern_y_offset[18] = {1, 4, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3};

	int step = 0;

	int pattern = rand() % 18;

	for (int y = play_area.y_min; y < play_area.y_max; y += pattern_y_offset[pattern])
	{
		for (int pattern_x = 0; pattern_x < 4; pattern_x++)
		{
			for (int pattern_y = 0; pattern_y < 4; pattern_y++)
			{
				int screen_x = x + pattern_x;
				int screen_y = y + pattern_y;

				if (play_area.x_min <= screen_x && screen_x < play_area.x_max && play_area.y_min <= screen_y && screen_y < play_area.y_max)
				{
					if (attack_patterns[pattern][pattern_y][pattern_x] == 1)
					{
						append_attack(tab, screen_x, screen_y, current_turn + 4 + step, damage);
					}
				}
			}
		}
		step++;
	}
}

void player_circle_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, player prota, int current_turn)
{
	int damage = get_attack_damage(current_enemy, PLAYER_CIRCLE);

	int center_x = prota.x;
	int center_y = prota.y;

	int attack_pattern[7][7] = {
		{0, 0, 8, 1, 1, 0, 0},
		{0, 8, 8, 0, 1, 2, 0},
		{7, 7, 0, 0, 0, 2, 2},
		{7, 0, 0, 0, 0, 0, 3},
		{6, 6, 0, 0, 0, 3, 3},
		{0, 6, 5, 0, 4, 4, 0},
		{0, 0, 5, 5, 4, 0, 0},
	};

	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			int screen_x = center_x - 3 + x;
			int screen_y = center_y - 3 + y;

			if (play_area.x_min <= screen_x && screen_x < play_area.x_max && play_area.y_min <= screen_y && screen_y < play_area.y_max)
			{
				if (attack_pattern[y][x] != 0)
				{
					append_attack(tab, screen_x, screen_y, current_turn + 4 + attack_pattern[y][x], damage);
				}
			}
		}
	}
}

void player_square_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, player prota, int current_turn)
{
	int damage = get_attack_damage(current_enemy, PLAYER_SQUARE);

	int center_x = prota.x;
	int center_y = prota.y;

	for (int i = 0; i < 7; i++)
	{
		if (play_area.x_min <= center_x - 3 + i && center_x - 3 + i < play_area.x_max && play_area.y_min <= center_y - 3 && center_y - 3 < play_area.y_max)
		{
			append_attack(tab, center_x - 3 + i, center_y - 3, current_turn + 4 + i, damage);
		}
		if (play_area.x_min <= center_x - 3 + i && center_x - 3 + i < play_area.x_max && play_area.y_min <= center_y + 3 && center_y + 3 < play_area.y_max)
		{
			append_attack(tab, center_x - 3 + i, center_y + 3, current_turn + 4 + i, damage);
		}

		if (play_area.x_min <= center_x - 3 && center_x - 3 < play_area.x_max && play_area.y_min <= center_y - 3 + i && center_y - 3 + i < play_area.y_max)
		{
			append_attack(tab, center_x - 3, center_y - 3 + i, current_turn + 4 + i, damage);
		}
		if (play_area.x_min <= center_x - 3 && center_x + 3 < play_area.x_max && play_area.y_min <= center_y + 3 + i && center_y + 3 + i < play_area.y_max)
		{
			append_attack(tab, center_x - 3, center_y + 3 - i, current_turn + 4 + i, damage);
		}

		if (play_area.x_min <= center_x + 3 - i && center_x - 3 + i < play_area.x_max && play_area.y_min <= center_y - 3 && center_y - 3 < play_area.y_max)
		{
			append_attack(tab, center_x + 3 - i, center_y - 3, current_turn + 4 + i, damage);
		}
		if (play_area.x_min <= center_x + 3 - i && center_x - 3 + i < play_area.x_max && play_area.y_min <= center_y + 3 && center_y + 3 < play_area.y_max)
		{
			append_attack(tab, center_x + 3 - i, center_y + 3, current_turn + 4 + i, damage);
		}

		if (play_area.x_min <= center_x + 3 && center_x - 3 < play_area.x_max && play_area.y_min <= center_y - 3 + i && center_y - 3 + i < play_area.y_max)
		{
			append_attack(tab, center_x + 3, center_y - 3 + i, current_turn + 4 + i, damage);
		}
		if (play_area.x_min <= center_x + 3 && center_x + 3 < play_area.x_max && play_area.y_min <= center_y + 3 + i && center_y + 3 + i < play_area.y_max)
		{
			append_attack(tab, center_x + 3, center_y + 3 - i, current_turn + 4 + i, damage);
		}
	}
}

void snake_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn)
{
	int damage = get_attack_damage(current_enemy, SNAKE);

	int x = rand() % play_area.width + play_area.x_min;
	int y = rand() % play_area.height + play_area.y_min;

	int stop_number = rand() % 5 + 10;

	int total_steps = 0;

	for (int stop = 0; stop < stop_number; stop++)
	{
		int x_direction;
		int y_direction;

		int direction_choice = rand() % 4;

		switch (direction_choice)
		{
		case 0:
			x_direction = -1;
			y_direction = 0;
			break;
		case 1:
			x_direction = 1;
			y_direction = 0;
			break;
		case 2:
			x_direction = 0;
			y_direction = -1;
			break;
		case 3:
			x_direction = 0;
			y_direction = 1;
			break;
		}

		int max_step_this_stop = rand() % 5 + 3;

		for (int step = 0; step < max_step_this_stop; step++)
		{
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max)
			{
				append_attack(tab, x, y, current_turn + 4 + total_steps, damage);
				total_steps++;
			}
			else
			{
				break;
			}

			x += x_direction;
			y += y_direction;
		}
	}
}
