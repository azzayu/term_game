#include "enemy.h"
#include <stdlib.h>
#include <time.h>


int distance_2(int x1, int y1, int x2, int y2){
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}


int distance_man(int x1, int y1, int x2, int y2){
	return abs(x1 - x2) + abs(y1 - y2);
}


void update_attacks(pixel **screen, int width, int height, player *prota, screen_section play_area){
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		for (int x = play_area.x_min; x < play_area.x_max; x++){
			if (screen[y][x].layer[LAYER_ATTACK_IN0] == 1){
				screen[y][x].layer[LAYER_ATTACK_IN0] = 0;
				if (prota->y == y && prota->x == x){
					prota->health -=1;
				}
			}
			if (screen[y][x].layer[LAYER_ATTACK_IN1] == 1){
				screen[y][x].layer[LAYER_ATTACK_IN1] = 0;
				screen[y][x].layer[LAYER_ATTACK_IN0] = 1;
			}
			if (screen[y][x].layer[LAYER_ATTACK_IN2] == 1){
				screen[y][x].layer[LAYER_ATTACK_IN2] = 0;
				screen[y][x].layer[LAYER_ATTACK_IN1] = 1;
			}
			if (screen[y][x].layer[LAYER_ATTACK_IN3] == 1){
				screen[y][x].layer[LAYER_ATTACK_IN3] = 0;
				screen[y][x].layer[LAYER_ATTACK_IN2] = 1;
			}
			if (screen[y][x].layer[LAYER_ATTACK_IN3] > 1){
				screen[y][x].layer[LAYER_ATTACK_IN3]--;
			}
		}
	}
}


void column_attack(pixel **screen, screen_section play_area){
	int column = rand() % play_area.width;
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		screen[y][play_area.x_min + column].layer[LAYER_ATTACK_IN3] = 1;
	}
}


void line_attack(pixel **screen, screen_section play_area){
	int line = rand() % play_area.height;
	for (int x = play_area.x_min; x < play_area.x_max; x++){
		screen[line + play_area.y_min][x].layer[LAYER_ATTACK_IN3] = 1;
	}
}


void circle_attack(pixel **screen, screen_section play_area){
	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;
	int radius = rand() % 6;
	for (int x = center_x - radius + play_area.x_min; x < center_x + radius + play_area.x_min; x++){
		for (int y = center_y - radius + play_area.y_min; y < center_y + radius + play_area.y_min; y++){
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max){
				if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) < radius * radius) {
					screen[y][x].layer[LAYER_ATTACK_IN3] = 1;
				}
			}
		}
	}
}


void square_attack(pixel **screen, screen_section play_area){
	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;
	int size = rand() % 4;
	for (int x = center_x - size + play_area.x_min; x < center_x + size + play_area.x_min; x++){
		for (int y = center_y - size + play_area.y_min; y < center_y + size + play_area.y_min; y++){
			if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max){					
				screen[y][x].layer[LAYER_ATTACK_IN3] = 1;
			}
		}
	}
}


void add_attack(pixel **screen, screen_section play_area){
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


enemy create_enemy_dark_knight(){
	enemy dark_knight;

	dark_knight.location = 1;
	dark_knight.max_health = 15;
	dark_knight.health = dark_knight.max_health;

	enemy_type type_dark_knight;

	type_dark_knight.different_attacks = 2;

	type_dark_knight.attack_codes[0] = SLASH;
	type_dark_knight.attack_codes[1] = STAB;

	type_dark_knight.attack_weights[0] = 2;
	type_dark_knight.attack_weights[1] = 1;

	type_dark_knight.attack_damages[0] = 1;
	type_dark_knight.attack_damages[1] = 3;

	dark_knight.enemy_type = type_dark_knight;

	return dark_knight;
}


enemy create_enemy_dark_mage(){
	enemy dark_mage;

	dark_mage.location = 1;
	dark_mage.max_health = 25;
	dark_mage.health = dark_mage.max_health;

	enemy_type type_dark_mage;

	type_dark_mage.different_attacks = 3;

	type_dark_mage.attack_codes[0] = METEOR;
	type_dark_mage.attack_codes[1] = TWINKLES;
	type_dark_mage.attack_codes[2] = BOUNCY_BALL;

	type_dark_mage.attack_weights[0] = 2;
	type_dark_mage.attack_weights[1] = 4;
	type_dark_mage.attack_weights[2] = 1;

	type_dark_mage.attack_damages[0] = 4;
	type_dark_mage.attack_damages[1] = 2;
	type_dark_mage.attack_damages[1] = 1;

	dark_mage.enemy_type = type_dark_mage;

	return dark_mage;
}


enemy create_enemy_dragon(){
	enemy dragon;

	dragon.location = 1;
	dragon.max_health = 50;
	dragon.health = dragon.max_health;

	enemy_type type_dragon;

	type_dragon.different_attacks = 3;

	type_dragon.attack_codes[0] = FIRE_BREATH;
	type_dragon.attack_codes[1] = TAIL_SLAP;
	type_dragon.attack_codes[2] = TWINKLES;

	type_dragon.attack_weights[0] = 1;
	type_dragon.attack_weights[1] = 2;
	type_dragon.attack_weights[2] = 1;

	type_dragon.attack_damages[0] = 4;
	type_dragon.attack_damages[1] = 2;
	type_dragon.attack_damages[1] = 2;

	dragon.enemy_type = type_dragon;

	return dragon;
}


enemy create_enemy_possessed_tree(){
	enemy possessed_tree;

	possessed_tree.location = 1;
	possessed_tree.max_health = 30;
	possessed_tree.health = possessed_tree.max_health;

	enemy_type type_possessed_tree;

	type_possessed_tree.different_attacks = 3;

	type_possessed_tree.attack_codes[0] = SPIKES;
	type_possessed_tree.attack_codes[1] = METEOR;
	type_possessed_tree.attack_codes[2] = TWINKLES;

	type_possessed_tree.attack_weights[0] = 2;
	type_possessed_tree.attack_weights[1] = 1;
	type_possessed_tree.attack_weights[2] = 2;

	type_possessed_tree.attack_damages[0] = 2;
	type_possessed_tree.attack_damages[1] = 3;
	type_possessed_tree.attack_damages[1] = 2;

	possessed_tree.enemy_type = type_possessed_tree;

	return possessed_tree;
}


enemy create_enemy(){
	enum enemy_types_names new_enemy_type = rand() % NB_ENEMY_TYPES;
	switch (new_enemy_type){
		case DARK_KNIGHT:
			return create_enemy_dark_knight();
		case DARK_MAGE:
			return create_enemy_dark_mage();
		case DRAGON:
			return create_enemy_dragon();
		case POSSESSED_TREE:
			return create_enemy_possessed_tree();
	}
}