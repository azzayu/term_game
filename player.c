#include "display.h"


typedef struct player_s{
	int x;
	int y;
	int max_health;
	int health;
} player;


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


