#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "display_cst.h"

void init_health_bar(pixel **screen, int width)
{

	// bottom line and junctions

	screen[4][width - 1].layer[LAYER_VERT_WALL_LEFT] = 0;
	screen[4][width - 1].layer[LAYER_LEFT_JUNCTION] = 1;

	for (int x = width - 2; x > width - 9; x--)
	{
		screen[4][x].layer[LAYER_HORI_WALL] = 1;
	}

	// bottom left junction

	screen[4][width - 9].layer[LAYER_RIGHT_CROSS_JUNCTION] = 1;

	// left wall and junctions

	screen[1][width - 9].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[2][width - 9].layer[LAYER_RIGHT_CROSS_JUNCTION] = 1;
	screen[3][width - 9].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[2][width - 8].layer[LAYER_HORI_WALL] = 1;
	screen[0][width - 9].layer[LAYER_HORI_WALL] = 0;
	screen[0][width - 9].layer[LAYER_DOWN_RIGHT_JUNCTION] = 1;

	// seperation between text and bar

	screen[2][width - 1].layer[LAYER_VERT_WALL_LEFT] = 0;
	screen[2][width - 1].layer[LAYER_LEFT_JUNCTION] = 1;
	screen[2][width - 2].layer[LAYER_HORI_WALL] = 1;
}

void init_stamina_bar(pixel **screen, int width)
{

	// bottom line and junctions

	screen[8][width - 1].layer[LAYER_VERT_WALL_LEFT] = 0;
	screen[8][width - 1].layer[LAYER_LEFT_JUNCTION] = 1;

	for (int x = width - 2; x > width - 9; x--)
	{
		screen[8][x].layer[LAYER_HORI_WALL] = 1;
	}

	// bottom left corner

	screen[8][width - 9].layer[LAYER_BOTTOM_LEFT_CORNER] = 1;

	// left wall and junctions

	screen[5][width - 9].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[6][width - 9].layer[LAYER_RIGHT_JUNCTION] = 1;
	screen[7][width - 9].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[6][width - 8].layer[LAYER_HORI_WALL] = 1;
	screen[4][width - 9].layer[LAYER_HORI_WALL] = 0;

	// seperation between text and bar

	screen[6][width - 1].layer[LAYER_VERT_WALL_LEFT] = 0;
	screen[6][width - 1].layer[LAYER_LEFT_JUNCTION] = 1;
	screen[6][width - 2].layer[LAYER_HORI_WALL] = 1;
}

void init_enemy_health(pixel **screen)
{
	// top line
	for (int x = 3; x < 27; x++)
	{
		screen[17][x].layer[LAYER_HORI_WALL] = 1;
	}
	// corners and junctions
	screen[17][2].layer[LAYER_TOP_LEFT_CORNER] = 1;
	screen[17][27].layer[LAYER_TOP_RIGHT_CORNER] = 1;

	screen[19][2].layer[LAYER_HORI_WALL] = 0;
	screen[19][2].layer[LAYER_UP_RIGHT_JUNCTION] = 1;

	screen[19][27].layer[LAYER_HORI_WALL] = 0;
	screen[19][27].layer[LAYER_UP_LEFT_JUNCTION] = 1;

	// vert_wall
	screen[18][27].layer[LAYER_VERT_WALL_LEFT] = 1;
	screen[18][2].layer[LAYER_VERT_WALL_RIGHT] = 1;
}

void init_exp_bar(pixel **screen, int width)
{

	// bottom line

	for (int x = width - 10; x > width - 17; x--)
	{
		screen[4][x].layer[LAYER_HORI_WALL] = 1;
	}

	// bottom left junction

	screen[4][width - 17].layer[LAYER_BOTTOM_LEFT_CORNER] = 1;

	// left wall and junctions

	screen[1][width - 17].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[2][width - 17].layer[LAYER_RIGHT_JUNCTION] = 1;
	screen[3][width - 17].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[2][width - 16].layer[LAYER_HORI_WALL] = 1;
	screen[0][width - 17].layer[LAYER_HORI_WALL] = 0;
	screen[0][width - 17].layer[LAYER_DOWN_RIGHT_JUNCTION] = 1;

	// seperation between text and bar

	screen[2][width - 10].layer[LAYER_VERT_WALL_LEFT] = 0;
	screen[2][width - 10].layer[LAYER_HORI_WALL] = 1;
}

pixel **init_screen(int width, int height, screen_section play_area, screen_section enemy_locations[3])
{
	pixel **screen = malloc(sizeof(pixel *) * height);
	for (int y = 0; y < height; y++)
	{
		screen[y] = malloc(sizeof(pixel) * width);
		for (int x = 0; x < width; x++)
		{
			for (int layer = 0; layer < 100; layer++)
			{
				screen[y][x].layer[layer] = 0;
			}
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max)
			{
				screen[y][x].layer[LAYER_DEFAULT] = 1;
			}
			screen[y][x].local_damage = 0;
		}
	}

	for (int x = play_area.x_min; x < play_area.x_max; x++)
	{
		screen[play_area.y_min - 1][x].layer[LAYER_HORI_WALL] = 1;
		screen[play_area.y_max][x].layer[LAYER_HORI_WALL] = 1;
	}

	for (int y = play_area.y_min; y < play_area.y_max; y++)
	{
		screen[y][play_area.x_min - 1].layer[LAYER_VERT_WALL_RIGHT] = 1;
		screen[y][play_area.x_max].layer[LAYER_VERT_WALL_LEFT] = 1;
	}

	for (int x = 1; x < width - 1; x++)
	{
		screen[0][x].layer[LAYER_HORI_WALL] = 1;
	}

	for (int y = 1; y < play_area.y_min - 1; y++)
	{
		screen[y][play_area.x_min - 1].layer[LAYER_VERT_WALL_RIGHT] = 1;
		screen[y][play_area.x_max].layer[LAYER_VERT_WALL_LEFT] = 1;
	}

	screen[0][0].layer[LAYER_TOP_LEFT_CORNER] = 1;
	screen[0][width - 1].layer[LAYER_TOP_RIGHT_CORNER] = 1;
	screen[play_area.y_min - 1][play_area.x_min - 1].layer[LAYER_RIGHT_JUNCTION] = 1;
	screen[play_area.y_min - 1][play_area.x_max].layer[LAYER_LEFT_JUNCTION] = 1;
	screen[play_area.y_max][play_area.x_min - 1].layer[LAYER_BOTTOM_LEFT_CORNER] = 1;
	screen[play_area.y_max][play_area.x_max].layer[LAYER_BOTTOM_RIGHT_CORNER] = 1;

	// health bar display :

	init_health_bar(screen, width);

	// stamina bar display :

	init_stamina_bar(screen, width);

	// exp bar display :

	init_exp_bar(screen, width);

	// init enemy location boxes

	for (int i = 0; i < 3; i++)
	{
		screen[enemy_locations[i].y_min][enemy_locations[i].x_min].layer[LAYER_TOP_LEFT_CORNER] = 1;
		screen[enemy_locations[i].y_min][enemy_locations[i].x_max].layer[LAYER_TOP_RIGHT_CORNER] = 1;
		screen[enemy_locations[i].y_max][enemy_locations[i].x_max].layer[LAYER_BOTTOM_RIGHT_CORNER] = 1;
		screen[enemy_locations[i].y_max][enemy_locations[i].x_min].layer[LAYER_BOTTOM_LEFT_CORNER] = 1;

		for (int j = 1; j < enemy_locations[i].width; j++)
		{
			screen[enemy_locations[i].y_min][enemy_locations[i].x_min + j].layer[LAYER_HORI_WALL] = 1;
			screen[enemy_locations[i].y_max][enemy_locations[i].x_min + j].layer[LAYER_HORI_WALL] = 1;
		}

		for (int j = 1; j < enemy_locations[i].height; j++)
		{
			screen[enemy_locations[i].y_min + j][enemy_locations[i].x_min].layer[LAYER_VERT_WALL_RIGHT] = 1;
			screen[enemy_locations[i].y_min + j][enemy_locations[i].x_max].layer[LAYER_VERT_WALL_LEFT] = 1;
		}
	}

	// init enemy health bar

	init_enemy_health(screen);

	return screen;
}

void default_test_screen()
{
	printf("%s %s%s%s%s\n", BLACK, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", RED, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", GREEN, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", YELLOW, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", BLUE, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", MAGENTA, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", CYAN, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", WHITE, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", BRIGHT_BLACK, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", BRIGHT_RED, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", BRIGHT_GREEN, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", BRIGHT_YELLOW, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", BRIGHT_MAGENTA, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", BRIGHT_CYAN, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);
	printf("%s %s%s%s%s\n", BRIGHT_WHITE, FULL_BLOCK, THREE_QUART_BLOCK, HALF_BLOCK, QUART_BLOCK);

	fflush(stdout);
}

void free_screen(pixel **pixel_mat, int height)
{
	for (int y = 0; y < height; y++)
	{
		free(pixel_mat[y]);
	}
	free(pixel_mat);
}

void print_text_section(text_section *text)
{
	printf("%s", WHITE);
	for (int i = 0; i < text->length; i++)
	{
		printf("%c", text->text[i]);
	}
	for (int i = 0; i < 2 * text->width - text->length; i++)
	{
		printf("%s█", BLACK);
	}
}

void print_screen(pixel **pixel_mat, int width, int height, text_section **all_text)
{
	/*
	each layer corresponds to something different with things closer to 0 more important to display (hence they get displayed)
	0 => player
	1 - 7 => border 1 for white, 2 for yellow
	8 - 11 => attacks, with 8 being attacks currently happening (these are redblock also used for health bar)  (layer 11 can be equal to more than 1 to show delayed attacks later)
	12 - 17 => junctions for borders
	18 - 21 => stamina bar (these big dark blue blocks)
	22 => for text display, an array of text sections is passed in args and the value in the layer corresponds to the text section to print, text starts at 1, the 0 spot is kept empty
	23 => this space is handled by a text section

	50 => background of play area
	none to 1 => general black background (normal terminal screen)
	*/
	//system("clear");
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixel_mat[y][x].layer[LAYER_PLAYER] == 1)
			{
				printf("%s%s", YELLOW, FULL_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_VERT_WALL_LEFT] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_VERT_WALL_LEFT] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", VERT_WALL_LEFT);
			}
			else if (pixel_mat[y][x].layer[LAYER_VERT_WALL_RIGHT] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_VERT_WALL_RIGHT] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", VERT_WALL_RIGHT);
			}
			else if (pixel_mat[y][x].layer[LAYER_HORI_WALL] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_HORI_WALL] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", HORI_WALL);
			}
			else if (pixel_mat[y][x].layer[LAYER_TOP_LEFT_CORNER] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_TOP_LEFT_CORNER] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", TOP_LEFT_CORNER);
			}
			else if (pixel_mat[y][x].layer[LAYER_TOP_RIGHT_CORNER] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_TOP_RIGHT_CORNER] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", TOP_RIGHT_CORNER);
			}
			else if (pixel_mat[y][x].layer[LAYER_BOTTOM_LEFT_CORNER] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_BOTTOM_LEFT_CORNER] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", BOTTOM_LEFT_CORNER);
			}
			else if (pixel_mat[y][x].layer[LAYER_BOTTOM_RIGHT_CORNER] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_BOTTOM_RIGHT_CORNER] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", BOTTOM_RIGHT_CORNER);
			}
			else if (pixel_mat[y][x].layer[LAYER_ATTACK_IN0] >= 1)
			{
				printf("%s%s", RED, FULL_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_ATTACK_IN1] >= 1)
			{
				printf("%s%s", RED, THREE_QUART_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_ATTACK_IN2] >= 1)
			{
				printf("%s%s", RED, HALF_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_ATTACK_IN3] >= 1)
			{
				printf("%s%s", RED, QUART_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_RIGHT_JUNCTION] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_RIGHT_JUNCTION] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", RIGHT_JUNCTION);
			}
			else if (pixel_mat[y][x].layer[LAYER_LEFT_JUNCTION] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_LEFT_JUNCTION] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", LEFT_JUNCTION);
			}
			else if (pixel_mat[y][x].layer[LAYER_UP_RIGHT_JUNCTION] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_UP_RIGHT_JUNCTION] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", UP_RIGHT_JUNCTION);
			}
			else if (pixel_mat[y][x].layer[LAYER_UP_LEFT_JUNCTION] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_UP_LEFT_JUNCTION] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", UP_LEFT_JUNCTION);
			}
			else if (pixel_mat[y][x].layer[LAYER_DOWN_LEFT_JUNCTION] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_DOWN_LEFT_JUNCTION] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", DOWN_LEFT_JUNCTION);
			}
			else if (pixel_mat[y][x].layer[LAYER_DOWN_RIGHT_JUNCTION] >= 1)
			{
				if (pixel_mat[y][x].layer[LAYER_DOWN_RIGHT_JUNCTION] == 1)
				{
					printf("%s", WHITE);
				}
				else
				{
					printf("%s", YELLOW);
				}
				printf("%s", DOWN_RIGHT_JUNCTION);
			}
			else if (pixel_mat[y][x].layer[LAYER_STAMINA_FULL] == 1)
			{
				printf("%s%s", BLUE, FULL_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_STAMINA_THREE_QUART] == 1)
			{
				printf("%s%s", BLUE, THREE_QUART_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_STAMINA_HALF] == 1)
			{
				printf("%s%s", BLUE, HALF_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_STAMINA_QUART] == 1)
			{
				printf("%s%s", BLUE, QUART_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_TEXT] > 0)
			{
				print_text_section(all_text[pixel_mat[y][x].layer[LAYER_TEXT]]);
			}
			else if (pixel_mat[y][x].layer[LAYER_TEXT_BEFORE] > 0)
			{
				continue;
			}
			else if (pixel_mat[y][x].layer[LAYER_LEFT_CROSS_JUNCTION] == 1)
			{
				printf("%s%s", WHITE, LEFT_CROSS_JUNCTION);
			}
			else if (pixel_mat[y][x].layer[LAYER_RIGHT_CROSS_JUNCTION] == 1)
			{
				printf("%s%s", WHITE, RIGHT_CROSS_JUNCTION);
			}
			else if (pixel_mat[y][x].layer[LAYER_EXP_FULL] == 1)
			{
				printf("%s%s", BRIGHT_YELLOW, FULL_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_EXP_THREE_QUART] == 1)
			{
				printf("%s%s", BRIGHT_YELLOW, THREE_QUART_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_EXP_HALF] == 1)
			{
				printf("%s%s", BRIGHT_YELLOW, HALF_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_EXP_QUART] == 1)
			{
				printf("%s%s", BRIGHT_YELLOW, QUART_BLOCK);
			}
			else if (pixel_mat[y][x].layer[LAYER_DEFAULT] == 1)
			{
				printf("%s%s", BRIGHT_BLUE, FULL_BLOCK);
			}
			else
			{
				printf("%s%s", BLACK, FULL_BLOCK);
			}
		}
		printf("\n");
	}
	fflush(stdout);
}

text_section *init_text(int x_min, int x_max, int y, char *text, int length)
{
	text_section *sect = malloc(sizeof(text_section));
	sect->x_min = x_min;
	sect->x_max = x_max;
	sect->y = y;

	sect->width = x_max - x_min;

	sect->length = length;

	for (int i = 0; i < length; i++)
	{
		sect->text[i] = text[i];
	}

	return sect;
}

screen_section init_screen_section(int x_min, int y_min, int x_max, int y_max)
{
	screen_section sect;
	sect.x_min = x_min;
	sect.x_max = x_max;
	sect.y_min = y_min;
	sect.y_max = y_max;

	sect.width = x_max - x_min;
	sect.height = y_max - y_min;

	return sect;
}
