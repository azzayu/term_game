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

#define LAYER_PLAYER 0
#define LAYER_VERT_WALL_LEFT 1
#define LAYER_VERT_WALL_RIGHT 2
#define LAYER_HORI_WALL 3
#define LAYER_TOP_LEFT_CORNER 4
#define LAYER_TOP_RIGHT_CORNER 5
#define LAYER_BOTTOM_LEFT_CORNER 6
#define LAYER_BOTTOM_RIGHT_CORNER 7
#define LAYER_ATTACK_IN0 8
#define LAYER_ATTACK_IN1 9
#define LAYER_ATTACK_IN2 10
#define LAYER_ATTACK_IN3 11
#define LAYER_HEALTH_FULL 8
#define LAYER_HEALTH_THREE_QUART 9
#define LAYER_HEALTH_HALF 10
#define LAYER_HEALTH_QUART 11
#define LAYER_RIGHT_JUNCTION 12
#define LAYER_LEFT_JUNCTION 13
#define LAYER_UP_RIGHT_JUNCTION 14
#define LAYER_UP_LEFT_JUNCTION 15
#define LAYER_DOWN_LEFT_JUNCTION 16
#define LAYER_DOWN_RIGHT_JUNCTION 17
#define LAYER_STAMINA_FULL 18
#define LAYER_STAMINA_THREE_QUART 19
#define LAYER_STAMINA_HALF 20
#define LAYER_STAMINA_QUART 21
#define LAYER_DEFAULT 50


typedef struct pixel_s {
	int layer[100];
} pixel;


typedef struct screen_section_s{
	int x_min;
	int y_min;
	int x_max;
	int y_max;

	int width;
	int height;
} screen_section;


void init_health_bar(pixel **screen, int width, int height){

	//bottom line and junctions

	screen[4][width - 1].layer[LAYER_VERT_WALL_LEFT] = 0;
	screen[4][width - 1].layer[LAYER_LEFT_JUNCTION] = 1;

	for (int x = width - 2; x > width - 9; x--){
		screen[4][x].layer[LAYER_HORI_WALL] = 1;
	}

	//bottom left junction

	screen[4][width - 9].layer[LAYER_RIGHT_JUNCTION] = 1;

	//left wall and junctions

	screen[1][width - 9].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[2][width - 9].layer[LAYER_RIGHT_JUNCTION] = 1;
	screen[3][width - 9].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[2][width - 8].layer[LAYER_HORI_WALL] = 1;
	screen[0][width - 9].layer[LAYER_HORI_WALL] = 0;
	screen[0][width - 9].layer[LAYER_DOWN_RIGHT_JUNCTION] = 1;

	//seperation between text and bar

	screen[2][width - 1].layer[LAYER_VERT_WALL_LEFT] = 0;
	screen[2][width - 1].layer[LAYER_LEFT_JUNCTION] = 1;
	screen[2][width - 2].layer[LAYER_HORI_WALL] = 1;
}


void init_stamina_bar(pixel **screen, int width, int height){

	//bottom line and junctions

	screen[8][width - 1].layer[LAYER_VERT_WALL_LEFT] = 0;
	screen[8][width - 1].layer[LAYER_LEFT_JUNCTION] = 1;

	for (int x = width - 2; x > width - 9; x--){
		screen[8][x].layer[LAYER_HORI_WALL] = 1;
	}

	//bottom left corner

	screen[8][width - 9].layer[LAYER_BOTTOM_LEFT_CORNER] = 1;

	//left wall and junctions

	screen[5][width - 9].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[6][width - 9].layer[LAYER_RIGHT_JUNCTION] = 1;
	screen[7][width - 9].layer[LAYER_VERT_WALL_RIGHT] = 1;
	screen[6][width - 8].layer[LAYER_HORI_WALL] = 1;
	screen[4][width - 9].layer[LAYER_HORI_WALL] = 0;
	screen[4][width - 9].layer[LAYER_DOWN_RIGHT_JUNCTION] = 1;

	//seperation between text and bar

	screen[6][width - 1].layer[LAYER_VERT_WALL_LEFT] = 0;
	screen[6][width - 1].layer[LAYER_LEFT_JUNCTION] = 1;
	screen[6][width - 2].layer[LAYER_HORI_WALL] = 1;
}


pixel **init_screen(int width, int height, screen_section play_area){
	pixel **screen = malloc(sizeof(pixel*) * height);
	for (int y = 0; y < height; y++){
		screen[y] = malloc(sizeof(pixel) * width);
		for (int x = 0; x < width; x++){
			for (int layer = 0; layer < 100; layer ++){
				screen[y][x].layer[layer] = 0;
			}
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max){
				screen[y][x].layer[LAYER_DEFAULT] = 1;
			}
		}
	}

	for (int x = play_area.x_min; x < play_area.x_max; x++){
		screen[play_area.y_min - 1][x].layer[LAYER_HORI_WALL] = 1;
		screen[play_area.y_max][x].layer[LAYER_HORI_WALL] = 1;
	}

	for (int y = play_area.y_min; y < play_area.y_max; y++){
		screen[y][play_area.x_min - 1].layer[LAYER_VERT_WALL_RIGHT] = 1;
		screen[y][play_area.x_max].layer[LAYER_VERT_WALL_LEFT] = 1;
	}

	for (int x = 1; x < width - 1; x++){
		screen[0][x].layer[LAYER_HORI_WALL] = 1;
	}

	for (int y = 1; y < play_area.y_min - 1; y++){
		screen[y][play_area.x_min - 1].layer[LAYER_VERT_WALL_RIGHT] = 1;
		screen[y][play_area.x_max].layer[LAYER_VERT_WALL_LEFT] = 1;
	}

	screen[0][0].layer[LAYER_TOP_LEFT_CORNER] = 1;
	screen[0][width - 1].layer[LAYER_TOP_RIGHT_CORNER] = 1;
	screen[play_area.y_min - 1][play_area.x_min - 1].layer[LAYER_RIGHT_JUNCTION] = 1;
	screen[play_area.y_min - 1][play_area.x_max].layer[LAYER_LEFT_JUNCTION] = 1;
	screen[play_area.y_max][play_area.x_min - 1].layer[LAYER_BOTTOM_LEFT_CORNER] = 1;
	screen[play_area.y_max][play_area.x_max].layer[LAYER_BOTTOM_RIGHT_CORNER] = 1;

	//health bar display :

	init_health_bar(screen, width, height);

	//stamina bar display :

	init_stamina_bar(screen, width, height);

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
	8 - 11 => attacks, with 8 being attacks currently happening (these are redblock also used for health bar)  (layer 11 can be equal to more than 1 to show delayed attacks later)
	12 - 17 => junctions for borders
	18 - 21 => stamina bar (these big dark blue blocks)


	50 => background of play area
	none to 1 => general black background (normal terminal screen)
	*/
	system("clear");
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			if (pixel_mat[y][x].layer[LAYER_PLAYER] == 1) {
				printf("%s%s", YELLOW, FULL_BLOCK);
			} else if (pixel_mat[y][x].layer[LAYER_VERT_WALL_LEFT] == 1) {
				printf("%s%s", WHITE, VERT_WALL_LEFT);
			} else if (pixel_mat[y][x].layer[LAYER_VERT_WALL_RIGHT] == 1) {
				printf("%s%s", WHITE, VERT_WALL_RIGHT);
			} else if (pixel_mat[y][x].layer[LAYER_HORI_WALL] == 1) {
				printf("%s%s", WHITE, HORI_WALL);
			} else if (pixel_mat[y][x].layer[LAYER_TOP_LEFT_CORNER] == 1) {
				printf("%s%s", WHITE, TOP_LEFT_CORNER);
			} else if (pixel_mat[y][x].layer[LAYER_TOP_RIGHT_CORNER] == 1) {
				printf("%s%s", WHITE, TOP_RIGHT_CORNER);
			} else if (pixel_mat[y][x].layer[LAYER_BOTTOM_LEFT_CORNER] == 1) {
				printf("%s%s", WHITE, BOTTOM_LEFT_CORNER);
			} else if (pixel_mat[y][x].layer[LAYER_BOTTOM_RIGHT_CORNER] == 1) {
				printf("%s%s", WHITE, BOTTOM_RIGHT_CORNER);
			} else if (pixel_mat[y][x].layer[LAYER_ATTACK_IN0] == 1) {
				printf("%s%s", RED, FULL_BLOCK);
			} else if (pixel_mat[y][x].layer[LAYER_ATTACK_IN1] == 1) {
				printf("%s%s", RED, THREE_QUART_BLOCK);
			} else if (pixel_mat[y][x].layer[LAYER_ATTACK_IN2] == 1) {
				printf("%s%s", RED, HALF_BLOCK);
			} else if (pixel_mat[y][x].layer[LAYER_ATTACK_IN3] == 1) {
				printf("%s%s", RED, QUART_BLOCK);
			} else if (pixel_mat[y][x].layer[LAYER_RIGHT_JUNCTION] == 1) {
				printf("%s%s", WHITE, RIGHT_JUNCTION);
			} else if (pixel_mat[y][x].layer[LAYER_LEFT_JUNCTION] == 1) {
				printf("%s%s", WHITE, LEFT_JUNCTION);
			} else if (pixel_mat[y][x].layer[LAYER_UP_RIGHT_JUNCTION] == 1) {
				printf("%s%s", WHITE, UP_RIGHT_JUNCTION);
			} else if (pixel_mat[y][x].layer[LAYER_UP_LEFT_JUNCTION] == 1) {
				printf("%s%s", WHITE, UP_LEFT_JUNCTION);
			} else if (pixel_mat[y][x].layer[LAYER_DOWN_LEFT_JUNCTION] == 1) {
				printf("%s%s", WHITE, DOWN_LEFT_JUNCTION);
			} else if (pixel_mat[y][x].layer[LAYER_DOWN_RIGHT_JUNCTION] == 1) {
				printf("%s%s", WHITE, DOWN_RIGHT_JUNCTION);
			} else if (pixel_mat[y][x].layer[LAYER_STAMINA_FULL] == 1) {
				printf("%s%s", BLUE, FULL_BLOCK);
			} else if (pixel_mat[y][x].layer[LAYER_STAMINA_THREE_QUART] == 1) {
				printf("%s%s", BLUE, THREE_QUART_BLOCK);
			} else if (pixel_mat[y][x].layer[LAYER_STAMINA_HALF] == 1) {
				printf("%s%s", BLUE, HALF_BLOCK);
			} else if (pixel_mat[y][x].layer[LAYER_STAMINA_QUART] == 1) {
				printf("%s%s", BLUE, QUART_BLOCK);
			} else if (pixel_mat[y][x].layer[LAYER_DEFAULT] == 1) {
				printf("%s%s", BRIGHT_BLUE, FULL_BLOCK);
			} else {
				printf("%s%s", BLACK, FULL_BLOCK);
			}
		}
		printf("\n");
	}
	fflush(stdout);
}

