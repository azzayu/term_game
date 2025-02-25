#include <stdio.h>
#include <stdlib.h>

#define FULL_BLOCK "██"
#define THREE_QUART_BLOCK "▓▓"
#define HALF_BLOCK "▒▒"
#define QUART_BLOCK "░░"
#define VERT_WALL_LEFT "║ "
#define VERT_WALL_RIGHT " ║"
#define HORI_WALL "══"
#define TOP_LEFT_CORNER " ╔"
#define TOP_RIGHT_CORNER "╗ "
#define BOTTOM_LEFT_CORNER " ╚"
#define BOTTOM_RIGHT_CORNER "╝ "
#define RIGHT_JUNCTION " ╠"
#define LEFT_JUNCTION "╣ "
#define UP_RIGHT_JUNCTION "═╩"
#define UP_LEFT_JUNCTION "╩═"
#define DOWN_LEFT_JUNCTION "╦═"
#define DOWN_RIGHT_JUNCTION "═╦"


#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BRIGHT_BLACK "\033[0;90m"
#define BRIGHT_RED "\033[0;91m"
#define BRIGHT_GREEN "\033[0;92m"
#define BRIGHT_YELLOW "\033[0;93m"
#define BRIGHT_BLUE "\033[0;94m"
#define BRIGHT_MAGENTA "\033[0;95m"
#define BRIGHT_CYAN "\033[0;96m"
#define BRIGHT_WHITE "\033[0;97m"


typedef struct pixel_s {
	int layer[100];
} pixel;


typedef struct play_screen_s{
	int x_min;
	int y_min;
	int x_max;
	int y_max;

	int width;
	int height;
} play_screen;

pixel **init_screen(int width, int height, play_screen play_area){
	pixel **screen = malloc(sizeof(pixel*) * height);
	for (int y = 0; y < height; y++){
		screen[y] = malloc(sizeof(pixel) * width);
		for (int x = 0; x < width; x++){
			for (int layer = 0; layer < 100; layer ++){
				screen[y][x].layer[layer] = 0;
			}
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max){
				screen[y][x].layer[50] = 1;
			}
		}
	}

	for (int x = play_area.x_min; x < play_area.x_max; x++){
		screen[play_area.y_min - 1][x].layer[3] = 1;
		screen[play_area.y_max][x].layer[3] = 1;
	}

	for (int y = play_area.y_min; y < play_area.y_max; y++){
		screen[y][play_area.x_min - 1].layer[2] = 1;
		screen[y][play_area.x_max].layer[1] = 1;
	}

	for (int x = 1; x < width - 1; x++){
		screen[0][x].layer[3] = 1;
	}

	for (int y = 1; y < play_area.y_min - 1; y++){
		screen[y][play_area.x_min - 1].layer[2] = 1;
		screen[y][play_area.x_max].layer[1] = 1;
	}

	screen[0][0].layer[4] = 1;
	screen[0][width - 1].layer[5] = 1;
	screen[play_area.y_min - 1][play_area.x_min - 1].layer[12] = 1;
	screen[play_area.y_min - 1][play_area.x_max].layer[13] = 1;
	screen[play_area.y_max][play_area.x_min - 1].layer[6] = 1;
	screen[play_area.y_max][play_area.x_max].layer[7] = 1;
	return screen;
}


void default_test_screen(){
	system("clear");
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


void free_screen(pixel **pixel_mat, int width, int height){
	for (int y = 0; y < height; y++){
		free(pixel_mat[y]);
	}
	free(pixel_mat);
}


void print_screen(pixel **pixel_mat, int width, int height){
	/*
	each layer corresponds to something different with things closer to 0 more important to display (hence they get displayed)
	0 => player
	1 - 7 => border
	8 - 11 => attacks, with 8 being attacks currently happening
	12 - 17 => junctions for borders

	50 => background of play area
	none to 1 => general black background (normal terminal screen)
	*/
	system("clear");
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			if (pixel_mat[y][x].layer[0] == 1) {
				printf("%s%s", YELLOW, FULL_BLOCK);
			} else if (pixel_mat[y][x].layer[1] == 1) {
				printf("%s%s", WHITE, VERT_WALL_LEFT);
			} else if (pixel_mat[y][x].layer[2] == 1) {
				printf("%s%s", WHITE, VERT_WALL_RIGHT);
			} else if (pixel_mat[y][x].layer[3] == 1) {
				printf("%s%s", WHITE, HORI_WALL);
			} else if (pixel_mat[y][x].layer[4] == 1) {
				printf("%s%s", WHITE, TOP_LEFT_CORNER);
			} else if (pixel_mat[y][x].layer[5] == 1) {
				printf("%s%s", WHITE, TOP_RIGHT_CORNER);
			} else if (pixel_mat[y][x].layer[6] == 1) {
				printf("%s%s", WHITE, BOTTOM_LEFT_CORNER);
			} else if (pixel_mat[y][x].layer[7] == 1) {
				printf("%s%s", WHITE, BOTTOM_RIGHT_CORNER);
			} else if (pixel_mat[y][x].layer[8] == 1) {
				printf("%s%s", RED, FULL_BLOCK);
			} else if (pixel_mat[y][x].layer[9] == 1) {
				printf("%s%s", RED, THREE_QUART_BLOCK);
			} else if (pixel_mat[y][x].layer[10] == 1) {
				printf("%s%s", RED, HALF_BLOCK);
			} else if (pixel_mat[y][x].layer[11] == 1) {
				printf("%s%s", RED, QUART_BLOCK);
			} else if (pixel_mat[y][x].layer[12] == 1) {
				printf("%s%s", WHITE, RIGHT_JUNCTION);
			} else if (pixel_mat[y][x].layer[13] == 1) {
				printf("%s%s", WHITE, LEFT_JUNCTION);
			} else if (pixel_mat[y][x].layer[14] == 1) {
				printf("%s%s", WHITE, UP_RIGHT_JUNCTION);
			} else if (pixel_mat[y][x].layer[15] == 1) {
				printf("%s%s", WHITE, UP_LEFT_JUNCTION);
			} else if (pixel_mat[y][x].layer[16] == 1) {
				printf("%s%s", WHITE, DOWN_LEFT_JUNCTION);
			} else if (pixel_mat[y][x].layer[17] == 1) {
				printf("%s%s", WHITE, DOWN_RIGHT_JUNCTION);
			} else if (pixel_mat[y][x].layer[50] == 1) {
				printf("%s%s", BRIGHT_BLUE, FULL_BLOCK);
			} else {
				printf("%s%s", BLACK, FULL_BLOCK);
			}
		}
		printf("\n");
	}
	fflush(stdout);
}

