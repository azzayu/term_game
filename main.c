#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>


const char FULL_BLOCK[] = "██"; 
const char THREE_QUART_BLOCK[] = "▓▓";
const char HALF_BLOCK[] = "▒▒";
const char QUART_BLOCK[] = "░░";
const char VERT_WALL_LEFT[] = "║ ";
const char VERT_WALL_RIGHT[] = " ║";
const char HORI_WALL[] = "══";
const char TOP_LEFT_CORNER[] = " ╔";
const char TOP_RIGHT_CORNER[] = "╗ ";
const char BOTTOM_LEFT_CORNER[] = " ╚";
const char BOTTOM_RIGHT_CORNER[] = "╝ ";


const char BLACK[] = "\033[0;30m";
const char RED[] = "\033[0;31m";
const char GREEN[] = "\033[0;32m";
const char YELLOW[] = "\033[0;33m";
const char BLUE[] = "\033[0;34m";
const char MAGENTA[] = "\033[0;35m";
const char CYAN[] = "\033[0;36m";
const char WHITE[] = "\033[0;37m";
const char BRIGHT_BLACK[] = "\033[0;90m";
const char BRIGHT_RED[] = "\033[0;91m";
const char BRIGHT_GREEN[] = "\033[0;92m";
const char BRIGHT_YELLOW[] = "\033[0;93m";
const char BRIGHT_BLUE[] = "\033[0;94m";
const char BRIGHT_MAGENTA[] = "\033[0;95m";
const char BRIGHT_CYAN[] = "\033[0;96m";
const char BRIGHT_WHITE[] = "\033[0;97m";


typedef struct pixel_s {
	int layer[100];
} pixel;


typedef struct player_s{
	int x;
	int y;
	int max_health;
	int health;
} player;

void print_screen(pixel **pixel_mat, int width, int height){
	/*
	each layer corresponds to something different with things closer to 0 more important to display (hence they get displayed)
	0 => player
	1 - 7 => border
	8 - 11 => attacks, with 8 being attacks currently happening

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


void move_player(pixel **screen, player *prota, char input, int width, int height){
	if (input == 'z' && prota->y > 1){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->y -= 1;
		screen[prota->y][prota->x].layer[0] = 1;
	}else if (input == 's' && prota->y < height - 2){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->y += 1;
		screen[prota->y][prota->x].layer[0] = 1;
	}else if (input == 'd' && prota->x < width - 2){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->x += 1;
		screen[prota->y][prota->x].layer[0] = 1;
	}else if (input == 'q' && prota->x > 1){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->x -= 1;
		screen[prota->y][prota->x].layer[0] = 1;
	}
}


void update_attacks(pixel **screen, int width, int height, player *prota){
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			if (screen[y][x].layer[8] == 1){
				screen[y][x].layer[8] = 0;
				if (prota->y == y && prota->x == x){
					prota->health -=1;
				}
			}
			if (screen[y][x].layer[9] == 1){
				screen[y][x].layer[9] = 0;
				screen[y][x].layer[8] = 1;
			}
			if (screen[y][x].layer[10] == 1){
				screen[y][x].layer[10] = 0;
				screen[y][x].layer[9] = 1;
			}
			if (screen[y][x].layer[11] == 1){
				screen[y][x].layer[11] = 0;
				screen[y][x].layer[10] = 1;
			}
		}
	}
}


void add_attack(pixel **screen, int width, int height){
	int column = rand() % width;
	for (int y = 0; y < height; y++){
		screen[y][column].layer[11] = 1;
	}
}


int main(){
	
	srand(time(NULL));

	int width = 30;
	int height = 20;

	player prota;
	prota.x = 15;
	prota.y = 10;
	prota.max_health = 5;
	prota.health = prota.max_health;
 
	pixel **screen = init_screen(width, height);
	screen[prota.y][prota.x].layer[0] = 1;

	while (prota.health > 0){
		print_screen(screen, width, height);
		char input;
		scanf("%c",&input);
		if (input != '\n'){
			move_player(screen, &prota, input, width, height);
			update_attacks(screen, width, height, &prota);
			add_attack(screen, width, height);
		}
	}
	free_screen(screen, width, height);
	return EXIT_SUCCESS;
}