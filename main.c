#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



char FULL_BLOCK[] = "██"; 
char THREE_QUART_BLOCK[] = "▓▓";
char HALF_BLOCK[] = "▒▒";
char QUART_BLOCK[] = "░░";
char VERT_WALL_LEFT[] = "║ ";
char VERT_WALL_RIGHT[] = " ║";
char HORI_WALL[] = "══";
char TOP_LEFT_CORNER[] = " ╔";
char TOP_RIGHT_CORNER[] = "╗ ";
char BOTTOM_LEFT_CORNER[] = " ╚";
char BOTTOM_RIGHT_CORNER[] = "╝ ";


char BLACK[] = "\033[0;30m";
char RED[] = "\033[0;31m";
char GREEN[] = "\033[0;32m";
char YELLOW[] = "\033[0;33m";
char BLUE[] = "\033[0;34m";
char MAGENTA[] = "\033[0;35m";
char CYAN[] = "\033[0;36m";
char WHITE[] = "\033[0;37m";
char BRIGHT_BLACK[] = "\033[0;90m";
char BRIGHT_RED[] = "\033[0;91m";
char BRIGHT_GREEN[] = "\033[0;92m";
char BRIGHT_YELLOW[] = "\033[0;93m";
char BRIGHT_BLUE[] = "\033[0;94m";
char BRIGHT_MAGENTA[] = "\033[0;95m";
char BRIGHT_CYAN[] = "\033[0;96m";
char BRIGHT_WHITE[] = "\033[0;97m";


typedef struct pixel_s {
	int layer[100];
} pixel;


void print_screen(pixel **pixel_mat, int width, int height){
	/*
	each layer corresponds to something different with things closer to 0 more important to display (hence they get displayed)
	0 => player
	1 - 7 => border


	50 => background of play area
	none to 1 => general black background (normal terminal screen)
	*/
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


pixel **init_screen(int width, int height){
	pixel **screen = malloc(sizeof(pixel*) * height);
	for (int y = 0; y < height; y++){
		screen[y] = malloc(sizeof(pixel) * width);
		for (int x = 0; x < width; x++){
			for (int layer = 0; layer < 100; layer ++){
				screen[y][x].layer[layer] = 0;
			}
			screen[y][x].layer[50] = 1;
		}
	}
	for (int x = 1; x < width - 1; x++){
		screen[0][x].layer[3] = 1;
		screen[height - 1][x].layer[3] = 1;
	}
	for (int y = 1; y < height - 1; y++){
		screen[y][0].layer[2] = 1;
		screen[y][width - 1].layer[1] = 1;
	}
	screen[0][0].layer[4] = 1;
	screen[0][width - 1].layer[5] = 1;
	screen[height - 1][0].layer[6] = 1;
	screen[height - 1][width - 1].layer[7] = 1;
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


int main(){

	int width = 50;
	int height = 30;
 
	pixel **screen = init_screen(width, height);
	screen[10][15].layer[0] = 1;
	print_screen(screen, width, height);

	free_screen(screen, width, height);
	return EXIT_SUCCESS;
}
