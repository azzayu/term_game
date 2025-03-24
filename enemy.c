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


enum attack_types choose_attack(enemy_type type){
	int total_weight = 1;

	for (int i = 0; i < type.different_attacks; i++){
		total_weight += type.attack_weights[i];
	}

	int choice = rand() % total_weight;

	for (int i = 0; i < type.different_attacks; i++){
		choice -= type.attack_weights[i];
		if (choice <= 0){
			return type.attack_codes[i];
		}
	}

	return type.attack_codes[type.different_attacks - 1];
}


int get_attack_damage(enemy current_enemy, enum attack_types attack){
	for (int i = 0; i < current_enemy.enemy_type.different_attacks; i++){
		if (current_enemy.enemy_type.attack_codes[i] == attack){
			return current_enemy.enemy_type.attack_damages[i];
		}
	}
	return 1;
}


void slash_attack(pixel **screen, screen_section play_area, enemy current_enemy){
	int damage = get_attack_damage(current_enemy, SLASH);

	int line = rand() % play_area.height;
	int left_right = rand() % 2;
	for (int x = play_area.x_min; x <= play_area.x_max; x++){
		if (left_right){
			screen[line + play_area.y_min][x].layer[LAYER_ATTACK_IN3] = 1 + (x - play_area.x_min) / 2;
		} else {
			screen[line + play_area.y_min][play_area.x_max - x + play_area.x_min - 1].layer[LAYER_ATTACK_IN3] = 1 + (x - play_area.x_min) / 2;
		}
		screen[line + play_area.y_min][x].local_damage = damage;
	}
}


void spike_attack(pixel **screen, screen_section play_area, enemy current_enemy){
	int damage = get_attack_damage(current_enemy, SPIKES);

	int column = rand() % play_area.width;
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		screen[play_area.y_max - y + play_area.y_min - 1][play_area.y_min + column].layer[LAYER_ATTACK_IN3] = 1 + (y - play_area.y_min);
		screen[y][play_area.x_min + column].local_damage = damage;
	}
}


void meteor_attack(pixel **screen, screen_section play_area, enemy current_enemy){
	int damage = get_attack_damage(current_enemy, METEOR);

	int column = rand() % play_area.width;
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		screen[y][play_area.x_min + column].layer[LAYER_ATTACK_IN3] = 1 + y - play_area.y_min;
		screen[y][play_area.x_min + column].local_damage = damage;
	}
}


void bouncy_ball(pixel **screen, screen_section play_area, enemy current_enemy){
	int damage = get_attack_damage(current_enemy, BOUNCY_BALL);

	int x = rand() % play_area.width + play_area.x_min;
	int y = rand() % play_area.height + play_area.y_min;
	int x_dir = (rand() % 2) * 2 - 1;
	int y_dir = (rand() % 2) * 2 - 1;

	for (int i = 0; i < 200; i++){
		screen[y][x].layer[LAYER_ATTACK_IN3] = i + 1;
		screen[y][x].local_damage = damage;
		
		x += x_dir;
		y += y_dir;

		if (x < play_area.x_min || x > play_area.x_max){
			x -= 2 * x_dir;
			y -= 2 * y_dir;
			x_dir *= -1;
			y_dir *= -1;
		}
		if (y < play_area.y_min || y > play_area.y_max){
			x -= 2 * x_dir;
			y -= 2 * y_dir;
			x_dir *= -1;
			y_dir *= -1;
		}
	}
}


void twinkles_attack(pixel **screen, screen_section play_area, enemy current_enemy){
	int damage = get_attack_damage(current_enemy, TWINKLES);


	for (int i = 0; i < 5; i++){

		int x_center = rand() % play_area.width + play_area.x_min;
		int y_center = rand() % play_area.height + play_area.y_min;

		for (int x = -1; x < 2; x++){
			for (int y = -1; y < 2; y++){
				if (play_area.x_min <= x + x_center && x + x_center < play_area.x_max && play_area.y_min <= y + y_center && y + y_center < play_area.y_max ){
					screen[y_center + y][x_center + x].layer[LAYER_ATTACK_IN3] = 2;
					screen[y_center + y][x_center + x].local_damage = damage;
				}
			}
		}

		screen[y_center][x_center].layer[LAYER_ATTACK_IN3] = 1;
	}
}


void stab_attack(pixel **screen, screen_section play_area, enemy current_enemy){
	int damage = get_attack_damage(current_enemy, STAB);

	int x_center = rand() % play_area.width + play_area.x_min;
	int y_center = rand() % play_area.height + play_area.y_min;

	for (int x = -1; x < 2; x++){
		if (play_area.x_min <= x + x_center && x + x_center < play_area.x_max){
			screen[y_center][x_center + x].layer[LAYER_ATTACK_IN3] = 2;
			screen[y_center][x_center + x].local_damage = damage;
		}	
	}
	for (int y = -1; y < 2; y++){
		if (play_area.y_min <= y + y_center && y + y_center < play_area.y_max ){
			screen[y_center + y][x_center].layer[LAYER_ATTACK_IN3] = 2;
			screen[y_center + y][x_center].local_damage = damage;
		}
	}

	screen[y_center][x_center].layer[LAYER_ATTACK_IN3] = 1;
}


void tail_slap_attack(pixel **screen, screen_section play_area, enemy current_enemy){
	int damage = get_attack_damage(current_enemy, TAIL_SLAP);

	int line = rand() % play_area.height;
	int left_right = rand() % 2;
	for (int y = -1; y < 2; y++){
		if (0 <= y + line && y + line < play_area.height){
			for (int x = play_area.x_min; x <= play_area.x_max; x++){
				if (left_right){
					screen[line + play_area.y_min + y][x].layer[LAYER_ATTACK_IN3] = 1 + (x - play_area.x_min) / 2;
				} else {
					screen[line + play_area.y_min + y][play_area.x_max - x + play_area.x_min].layer[LAYER_ATTACK_IN3] = 1 + (x - play_area.x_min) / 2;
				}
				screen[line + play_area.y_min][x].local_damage = damage;
			}
		}
	}
}


void fire_breath_attack(pixel **screen, screen_section play_area, enemy current_enemy){
	int damage = get_attack_damage(current_enemy, FIRE_BREATH);

	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;

	for (int radius = 6; radius > 0 ; radius--){
		for (int x = center_x - radius + play_area.x_min; x < center_x + radius + play_area.x_min; x++){
			for (int y = center_y - radius + play_area.y_min; y < center_y + radius + play_area.y_min; y++){
				if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max){
					if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) < radius * radius) {
						screen[y][x].layer[LAYER_ATTACK_IN3] = radius;
					}
				}
			}
		}
	}
}


void add_attack(pixel **screen, screen_section play_area, enemy current_enemy){
	enum attack_types chosen_attack = choose_attack(current_enemy.enemy_type);
	switch (chosen_attack){
		case SLASH:
			slash_attack(screen, play_area, current_enemy);
			break;
		case SPIKES:
			spike_attack(screen, play_area, current_enemy);
			break;
		case METEOR:
			meteor_attack(screen, play_area, current_enemy);
			break;
		case BOUNCY_BALL:
			bouncy_ball(screen, play_area, current_enemy);
			break;
		case TWINKLES:
			twinkles_attack(screen, play_area, current_enemy);
			break;
		case STAB:
			stab_attack(screen, play_area, current_enemy);
			break;
		case TAIL_SLAP:
			tail_slap_attack(screen, play_area, current_enemy);
			break;
		case FIRE_BREATH: 
			fire_breath_attack(screen, play_area, current_enemy);
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