#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "display_cst.h"

void init_health_bar(pixel **screen, int width)
{

	// bottom line and junctions

	screen[4][width - 1].colour = VALUE_BRIGHT_WHITE;
	screen[4][width - 1].pixel_type = PIXEL_LEFT_JUNCTION;

	for (int x = width - 2; x > width - 9; x--)
	{
		screen[4][x].colour = VALUE_BRIGHT_WHITE;
		screen[4][x].pixel_type = PIXEL_HORI_WALL;
	}

	// bottom left junction

	screen[4][width - 9].colour = VALUE_BRIGHT_WHITE;
	screen[4][width - 9].pixel_type = PIXEL_RIGHT_CROSS_JUNCTION;

	// left wall and junctions

	screen[1][width - 9].colour = VALUE_BRIGHT_WHITE;
	screen[1][width - 9].pixel_type = PIXEL_VERT_WALL_RIGHT;

	screen[2][width - 9].colour = VALUE_BRIGHT_WHITE;
	screen[2][width - 9].pixel_type = PIXEL_RIGHT_CROSS_JUNCTION;

	screen[3][width - 9].colour = VALUE_BRIGHT_WHITE;
	screen[3][width - 9].pixel_type = PIXEL_VERT_WALL_RIGHT;

	screen[2][width - 8].colour = VALUE_BRIGHT_WHITE;
	screen[2][width - 8].pixel_type = PIXEL_HORI_WALL;

	screen[0][width - 9].colour = VALUE_BRIGHT_WHITE;
	screen[0][width - 9].pixel_type = PIXEL_DOWN_RIGHT_JUNCTION;

	// seperation between text and bar

	screen[2][width - 1].colour = VALUE_BRIGHT_WHITE;
	screen[2][width - 1].pixel_type = PIXEL_LEFT_JUNCTION;

	screen[2][width - 2].colour = VALUE_BRIGHT_WHITE;
	screen[2][width - 2].pixel_type = PIXEL_HORI_WALL;
}

void init_stamina_bar(pixel **screen, int width)
{

	// bottom line and junctions

	screen[8][width - 1].colour = VALUE_BRIGHT_WHITE;
	screen[8][width - 1].pixel_type = PIXEL_LEFT_JUNCTION;

	for (int x = width - 2; x > width - 9; x--)
	{
		screen[8][x].colour = VALUE_BRIGHT_WHITE;
		screen[8][x].pixel_type = PIXEL_HORI_WALL;
	}

	// bottom left corner

	screen[8][width - 9].colour = VALUE_BRIGHT_WHITE;
	screen[8][width - 9].pixel_type = PIXEL_BOTTOM_LEFT_CORNER;

	// left wall and junctions

	screen[5][width - 9].colour = VALUE_BRIGHT_WHITE;
	screen[5][width - 9].pixel_type = PIXEL_VERT_WALL_RIGHT;

	screen[6][width - 9].colour = VALUE_BRIGHT_WHITE;
	screen[6][width - 9].pixel_type = PIXEL_RIGHT_JUNCTION;

	screen[7][width - 9].colour = VALUE_BRIGHT_WHITE;
	screen[7][width - 9].pixel_type = PIXEL_VERT_WALL_RIGHT;

	screen[6][width - 8].colour = VALUE_BRIGHT_WHITE;
	screen[6][width - 8].pixel_type = PIXEL_HORI_WALL;

	// seperation between text and bar

	screen[6][width - 1].colour = VALUE_BRIGHT_WHITE;
	screen[6][width - 1].pixel_type = PIXEL_LEFT_JUNCTION;

	screen[6][width - 2].colour = VALUE_BRIGHT_WHITE;
	screen[6][width - 2].pixel_type = PIXEL_HORI_WALL;
}

void init_enemy_health(pixel **screen)
{
	// top line
	for (int x = 3; x < 27; x++)
	{
		screen[17][x].colour = VALUE_BRIGHT_WHITE;
		screen[17][x].pixel_type = PIXEL_HORI_WALL;
	}
	// corners and junctions

	screen[17][2].colour = VALUE_BRIGHT_WHITE;
	screen[17][2].pixel_type = PIXEL_TOP_LEFT_CORNER;

	screen[17][27].colour = VALUE_BRIGHT_WHITE;
	screen[17][27].pixel_type = PIXEL_TOP_RIGHT_CORNER;

	screen[19][2].colour = VALUE_BRIGHT_WHITE;
	screen[19][2].pixel_type = PIXEL_UP_RIGHT_JUNCTION;

	screen[19][27].colour = VALUE_BRIGHT_WHITE;
	screen[19][27].pixel_type = PIXEL_UP_LEFT_JUNCTION;

	// vert_wall
	screen[18][27].colour = VALUE_BRIGHT_WHITE;
	screen[18][27].pixel_type = PIXEL_VERT_WALL_LEFT;

	screen[18][2].colour = VALUE_BRIGHT_WHITE;
	screen[18][2].pixel_type = PIXEL_VERT_WALL_RIGHT;
}

void init_exp_bar(pixel **screen, int width)
{

	// bottom line

	for (int x = width - 10; x > width - 17; x--)
	{
		screen[4][x].colour = VALUE_BRIGHT_WHITE;
		screen[4][x].pixel_type = PIXEL_HORI_WALL;
	}

	// bottom left junction

	screen[4][width - 17].colour = VALUE_BRIGHT_WHITE;
	screen[4][width - 17].pixel_type = PIXEL_BOTTOM_LEFT_CORNER;

	// left wall and junctions

	screen[1][width - 17].colour = VALUE_BRIGHT_WHITE;
	screen[1][width - 17].pixel_type = PIXEL_VERT_WALL_LEFT;

	screen[2][width - 17].colour = VALUE_BRIGHT_WHITE;
	screen[2][width - 17].pixel_type = PIXEL_RIGHT_JUNCTION;

	screen[3][width - 17].colour = VALUE_BRIGHT_WHITE;
	screen[3][width - 17].pixel_type = PIXEL_VERT_WALL_LEFT;

	screen[2][width - 16].colour = VALUE_BRIGHT_WHITE;
	screen[2][width - 16].pixel_type = PIXEL_HORI_WALL;

	screen[0][width - 17].colour = VALUE_BRIGHT_WHITE;
	screen[0][width - 17].pixel_type = PIXEL_DOWN_RIGHT_JUNCTION;

	// seperation between text and bar

	screen[2][width - 10].colour = VALUE_BRIGHT_WHITE;
	screen[2][width - 10].pixel_type = PIXEL_HORI_WALL;
}

pixel **init_screen(int width, int height, screen_section play_area, screen_section enemy_locations[3])
{
	pixel **screen = malloc(sizeof(pixel *) * height);
	for (int y = 0; y < height; y++)
	{
		screen[y] = malloc(sizeof(pixel) * width);
		for (int x = 0; x < width; x++)
		{
			screen[y][x].colour = VALUE_BLACK;
			screen[y][x].pixel_type = PIXEL_FULL_BLOCK;
		}
	}

	for (int x = play_area.x_min; x < play_area.x_max; x++)
	{
		screen[play_area.y_min - 1][x].colour = VALUE_BRIGHT_WHITE;
		screen[play_area.y_min - 1][x].pixel_type = PIXEL_HORI_WALL;

		screen[play_area.y_max][x].colour = VALUE_BRIGHT_WHITE;
		screen[play_area.y_max][x].pixel_type = PIXEL_HORI_WALL;
	}

	for (int y = play_area.y_min; y < play_area.y_max; y++)
	{
		screen[y][play_area.x_min - 1].colour = VALUE_BRIGHT_WHITE;
		screen[y][play_area.x_min - 1].pixel_type = PIXEL_VERT_WALL_RIGHT;

		screen[y][play_area.x_max].colour = VALUE_BRIGHT_WHITE;
		screen[y][play_area.x_max].pixel_type = PIXEL_VERT_WALL_LEFT;
	}

	for (int x = 1; x < width - 1; x++)
	{
		screen[0][x].colour = VALUE_BRIGHT_WHITE;
		screen[0][x].pixel_type = PIXEL_HORI_WALL;
	}

	for (int y = 1; y < play_area.y_min - 1; y++)
	{
		screen[y][play_area.x_min - 1].colour = VALUE_BRIGHT_WHITE;
		screen[y][play_area.x_min - 1].pixel_type = PIXEL_VERT_WALL_RIGHT;

		screen[y][play_area.x_max].colour = VALUE_BRIGHT_WHITE;
		screen[y][play_area.x_max].pixel_type = PIXEL_VERT_WALL_LEFT;
	}

	screen[0][0].colour = VALUE_BRIGHT_WHITE;
	screen[0][0].pixel_type = PIXEL_TOP_LEFT_CORNER;

	screen[0][width - 1].colour = VALUE_BRIGHT_WHITE;
	screen[0][width - 1].pixel_type = PIXEL_TOP_RIGHT_CORNER;

	screen[play_area.y_min - 1][play_area.x_min - 1].colour = VALUE_BRIGHT_WHITE;
	screen[play_area.y_min - 1][play_area.x_min - 1].pixel_type = PIXEL_RIGHT_JUNCTION;

	screen[play_area.y_min - 1][play_area.x_max].colour = VALUE_BRIGHT_WHITE;
	screen[play_area.y_min - 1][play_area.x_max].pixel_type = PIXEL_LEFT_JUNCTION;

	screen[play_area.y_max][play_area.x_min - 1].colour = VALUE_BRIGHT_WHITE;
	screen[play_area.y_max][play_area.x_min - 1].pixel_type = PIXEL_BOTTOM_LEFT_CORNER;

	screen[play_area.y_max][play_area.x_max].colour = VALUE_BRIGHT_WHITE;
	screen[play_area.y_max][play_area.x_max].pixel_type = PIXEL_BOTTOM_RIGHT_CORNER;

	// health bar display :

	init_health_bar(screen, width);

	// stamina bar display :

	init_stamina_bar(screen, width);

	// exp bar display :

	init_exp_bar(screen, width);

	// init enemy location boxes

	for (int i = 0; i < 3; i++)
	{
		screen[enemy_locations[i].y_min][enemy_locations[i].x_min].colour = VALUE_BRIGHT_WHITE;
		screen[enemy_locations[i].y_min][enemy_locations[i].x_min].pixel_type = PIXEL_TOP_LEFT_CORNER;

		screen[enemy_locations[i].y_min][enemy_locations[i].x_max].colour = VALUE_BRIGHT_WHITE;
		screen[enemy_locations[i].y_min][enemy_locations[i].x_max].pixel_type = PIXEL_TOP_RIGHT_CORNER;

		screen[enemy_locations[i].y_max][enemy_locations[i].x_max].colour = VALUE_BRIGHT_WHITE;
		screen[enemy_locations[i].y_max][enemy_locations[i].x_max].pixel_type = PIXEL_BOTTOM_RIGHT_CORNER;

		screen[enemy_locations[i].y_max][enemy_locations[i].x_min].colour = VALUE_BRIGHT_WHITE;
		screen[enemy_locations[i].y_max][enemy_locations[i].x_min].pixel_type = PIXEL_BOTTOM_LEFT_CORNER;

		for (int j = 1; j < enemy_locations[i].width; j++)
		{
			screen[enemy_locations[i].y_min][enemy_locations[i].x_min + j].colour = VALUE_BRIGHT_WHITE;
			screen[enemy_locations[i].y_min][enemy_locations[i].x_min + j].pixel_type = PIXEL_HORI_WALL;

			screen[enemy_locations[i].y_max][enemy_locations[i].x_min + j].colour = VALUE_BRIGHT_WHITE;
			screen[enemy_locations[i].y_max][enemy_locations[i].x_min + j].pixel_type = PIXEL_HORI_WALL;
		}

		for (int j = 1; j < enemy_locations[i].height; j++)
		{
			screen[enemy_locations[i].y_min + j][enemy_locations[i].x_min].colour = VALUE_BRIGHT_WHITE;
			screen[enemy_locations[i].y_min + j][enemy_locations[i].x_min].pixel_type = PIXEL_VERT_WALL_RIGHT;

			screen[enemy_locations[i].y_min + j][enemy_locations[i].x_max].colour = VALUE_BRIGHT_WHITE;
			screen[enemy_locations[i].y_min + j][enemy_locations[i].x_max].pixel_type = PIXEL_VERT_WALL_LEFT;
		}
	}

	// init enemy health bar

	init_enemy_health(screen);

	return screen;
}

void default_test_screen()
{
	printf("%s %s%s%s%s\n", STRING_BLACK, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_RED, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_GREEN, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_YELLOW, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_BLUE, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_MAGENTA, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_CYAN, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_WHITE, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_BRIGHT_BLACK, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_BRIGHT_RED, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_BRIGHT_GREEN, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_BRIGHT_YELLOW, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_BRIGHT_BLUE, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_BRIGHT_MAGENTA, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_BRIGHT_CYAN, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);
	printf("%s %s%s%s%s\n", STRING_BRIGHT_WHITE, STRING_FULL_BLOCK, STRING_THREE_QUART_BLOCK, STRING_HALF_BLOCK, STRING_QUART_BLOCK);

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
	printf("%s", STRING_BRIGHT_WHITE);
	for (int i = 0; i < text->length; i++)
	{
		printf("%c", text->text[i]);
	}
	for (int i = 0; i < 2 * text->width - text->length; i++)
	{
		printf("%s█", STRING_BLACK);
	}
}

void display_colour(display_colours pixel_to_display)
{
	switch (pixel_to_display)
	{
	case VALUE_NONE:
		break;
	case VALUE_BLACK:
		printf("%s", STRING_BLACK);
		break;
	case VALUE_RED:
		printf("%s", STRING_RED);
		break;
	case VALUE_GREEN:
		printf("%s", STRING_GREEN);
		break;
	case VALUE_YELLOW:
		printf("%s", STRING_YELLOW);
		break;
	case VALUE_BLUE:
		printf("%s", STRING_BLUE);
		break;
	case VALUE_MAGENTA:
		printf("%s", STRING_MAGENTA);
		break;
	case VALUE_CYAN:
		printf("%s", STRING_CYAN);
		break;
	case VALUE_WHITE:
		printf("%s", STRING_WHITE);
		break;
	case VALUE_BRIGHT_BLACK:
		printf("%s", STRING_BRIGHT_BLACK);
		break;
	case VALUE_BRIGHT_RED:
		printf("%s", STRING_BRIGHT_RED);
		break;
	case VALUE_BRIGHT_GREEN:
		printf("%s", STRING_BRIGHT_GREEN);
		break;
	case VALUE_BRIGHT_YELLOW:
		printf("%s", STRING_BRIGHT_YELLOW);
		break;
	case VALUE_BRIGHT_BLUE:
		printf("%s", STRING_BRIGHT_BLUE);
		break;
	case VALUE_BRIGHT_MAGENTA:
		printf("%s", STRING_BRIGHT_MAGENTA);
		break;
	case VALUE_BRIGHT_CYAN:
		printf("%s", STRING_BRIGHT_CYAN);
		break;
	case VALUE_BRIGHT_WHITE:
		printf("%s", STRING_BRIGHT_WHITE);
		break;
	}
}

void display_pixel(pixel pixel_to_display, text_section **all_text)
{
	if (pixel_to_display.pixel_type == PIXEL_START_TEXT)
	{
		print_text_section(all_text[pixel_to_display.colour]);
		return;
	}
	if (pixel_to_display.pixel_type == PIXEL_TEXT)
	{
		return;
	}

	display_colour(pixel_to_display.colour);
	switch (pixel_to_display.pixel_type)
	{
	case PIXEL_FULL_BLOCK:
		printf("%s", STRING_FULL_BLOCK);
		break;
	case PIXEL_THREE_QUART_BLOCK:
		printf("%s", STRING_THREE_QUART_BLOCK);
		break;
	case PIXEL_HALF_BLOCK:
		printf("%s", STRING_HALF_BLOCK);
		break;
	case PIXEL_QUART_BLOCK:
		printf("%s", STRING_QUART_BLOCK);
		break;
	case PIXEL_VERT_WALL_LEFT:
		printf("%s", STRING_VERT_WALL_LEFT);
		break;
	case PIXEL_VERT_WALL_RIGHT:
		printf("%s", STRING_VERT_WALL_RIGHT);
		break;
	case PIXEL_HORI_WALL:
		printf("%s", STRING_HORI_WALL);
		break;
	case PIXEL_TOP_LEFT_CORNER:
		printf("%s", STRING_TOP_LEFT_CORNER);
		break;
	case PIXEL_TOP_RIGHT_CORNER:
		printf("%s", STRING_TOP_RIGHT_CORNER);
		break;
	case PIXEL_BOTTOM_LEFT_CORNER:
		printf("%s", STRING_BOTTOM_LEFT_CORNER);
		break;
	case PIXEL_BOTTOM_RIGHT_CORNER:
		printf("%s", STRING_BOTTOM_RIGHT_CORNER);
		break;
	case PIXEL_RIGHT_JUNCTION:
		printf("%s", STRING_RIGHT_JUNCTION);
		break;
	case PIXEL_LEFT_JUNCTION:
		printf("%s", STRING_LEFT_JUNCTION);
		break;
	case PIXEL_UP_RIGHT_JUNCTION:
		printf("%s", STRING_UP_RIGHT_JUNCTION);
		break;
	case PIXEL_UP_LEFT_JUNCTION:
		printf("%s", STRING_UP_LEFT_JUNCTION);
		break;
	case PIXEL_DOWN_LEFT_JUNCTION:
		printf("%s", STRING_DOWN_LEFT_JUNCTION);
		break;
	case PIXEL_DOWN_RIGHT_JUNCTION:
		printf("%s", STRING_DOWN_RIGHT_JUNCTION);
		break;
	case PIXEL_LEFT_CROSS_JUNCTION:
		printf("%s", STRING_LEFT_CROSS_JUNCTION);
		break;
	case PIXEL_RIGHT_CROSS_JUNCTION:
		printf("%s", STRING_RIGHT_CROSS_JUNCTION);
		break;
	}
}

void print_screen(pixel **pixel_mat, int width, int height, text_section **all_text)
{
	/*
	each pixel has a pixel type and a colour to indicate what is meant to be displayed

	colours :

	NONE 0
	BLACK 1
	RED 2
	GREEN 3
	YELLOW 4
	BLUE 5
	MAGENTA 6
	CYAN 7
	WHITE 8
	BRIGHT_BLACK 9
	BRIGHT_RED 10
	BRIGHT_GREEN 11
	BRIGHT_YELLOW 12
	BRIGHT_BLUE 13
	BRIGHT_MAGENTA 14
	BRIGHT_CYAN 15
	BRIGHT_WHITE 16

	with NONE being not to display this layer

	the pairs of unicode and their values:

	*/
	system("clear");
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			display_pixel(pixel_mat[y][x], all_text);
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
