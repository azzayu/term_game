#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "display.h"


typedef struct player_s{
	int x;
	int y;
	int max_health;
	int health;
} player;


int distance_2(int x1, int y1, int x2, int y2){
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}


int distance_man(int x1, int y1, int x2, int y2){
	return abs(x1 - x2) + abs(y1 - y2);
}


int move_player(pixel **screen, player *prota, char input, int width, int height, play_screen play_area){
	/*
		returns 1 if move succesfull 
		0 if not
	*/
	
	if (input == 'z' && prota->y > play_area.y_min){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->y -= 1;
		screen[prota->y][prota->x].layer[0] = 1;
		return 1;
	}
	if (input == 's' && prota->y < play_area.y_max - 1){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->y += 1;
		screen[prota->y][prota->x].layer[0] = 1;
		return 1;
	}
	if (input == 'd' && prota->x < play_area.x_max - 1){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->x += 1;
		screen[prota->y][prota->x].layer[0] = 1;
		return 1;
	}
	if (input == 'q' && prota->x > play_area.x_min){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->x -= 1;
		screen[prota->y][prota->x].layer[0] = 1;
		return 1;
	}
	if (input == 'p'){
		//counts as passing
		return 1;
	}
	return 0;
}


void update_attacks(pixel **screen, int width, int height, player *prota, play_screen play_area){
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		for (int x = play_area.x_min; x < play_area.x_max; x++){
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


void column_attack(pixel **screen, play_screen play_area){
	int column = rand() % play_area.width;
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		screen[y][play_area.x_min + column].layer[11] = 1;
	}
}


void line_attack(pixel **screen, play_screen play_area){
	int line = rand() % play_area.height;
	for (int x = play_area.x_min; x < play_area.x_max; x++){
		screen[line + play_area.y_min][x].layer[11] = 1;
	}
}


void circle_attack(pixel **screen, play_screen play_area){
	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;
	int radius = rand() % 6;
	for (int x = center_x - radius + play_area.x_min; x < center_x + radius + play_area.x_min; x++){
		for (int y = center_y - radius + play_area.y_min; y < center_y + radius + play_area.y_min; y++){
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max){
				if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) < radius * radius) {
					screen[y][x].layer[11] = 1;
				}
			}
		}
	}
}


void square_attack(pixel **screen, play_screen play_area){
	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;
	int size = rand() % 4;
	for (int x = center_x - size + play_area.x_min; x < center_x + size + play_area.x_min; x++){
		for (int y = center_y - size + play_area.y_min; y < center_y + size + play_area.y_min; y++){
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max){					
				screen[y][x].layer[11] = 1;
			}
		}
	}
}


void add_attack(pixel **screen, play_screen play_area){
	int attack_type = rand() % 4;
	switch (attack_type){
		case 0:
			column_attack(screen, play_area);
			break;
		case 1:
			line_attack(screen, play_area);
			break;
		case 2:
			circle_attack(screen, play_area);
			break;
		case 3:
			square_attack(screen, play_area);
			break;
	}
}


int main(){
	
	srand(time(NULL));

	int width = 30;
	int height = 40;

	play_screen play_area;

	play_area.x_min = 1;
	play_area.x_max = width - 1;
	play_area.y_min = height / 2 + 1;
	play_area.y_max = height - 1;
	play_area.width = play_area.x_max - play_area.x_min;
	play_area.height = play_area.y_max - play_area.y_min;

	player prota;
	prota.x = (play_area.x_max - play_area.x_min) / 2 + play_area.x_min;
	prota.y = (play_area.y_max - play_area.y_min) / 2 + play_area.y_min;
	prota.max_health = 5;
	prota.health = prota.max_health;
 
	pixel **screen = init_screen(width, height, play_area);
	screen[prota.y][prota.x].layer[0] = 1;

	while (prota.health > 0) {
		print_screen(screen, width, height);
		char input;
		scanf("%c",&input);
		int has_moved = move_player(screen, &prota, input, width, height, play_area);
		if (has_moved) {
			update_attacks(screen, width, height, &prota, play_area);
			add_attack(screen, play_area);
		}
	}
	free_screen(screen, width, height);
	return EXIT_SUCCESS;
}