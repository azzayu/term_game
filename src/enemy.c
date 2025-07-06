#include "enemy.h"
#include "display_cst.h"
#include "dyn_array.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int distance_2(int x1, int y1, int x2, int y2){
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}


int distance_man(int x1, int y1, int x2, int y2){
	return abs(x1 - x2) + abs(y1 - y2);
}


void update_attacks(pixel **screen, player *prota, screen_section play_area, dyn_array *tab, int current_turn){

	//resets the screen to remove all attacks
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		for (int x = play_area.x_min; x < play_area.x_max; x++){
			if (screen[y][x].layer[LAYER_ATTACK_IN0] != 0){
				/*
				if (prota->y == y && prota->x == x){
					prota->health -= screen[y][x].layer[LAYER_ATTACK_IN0];
				}
				*/
				screen[y][x].layer[LAYER_ATTACK_IN0] = 0;
			}
			if (screen[y][x].layer[LAYER_ATTACK_IN1] != 0){
				//screen[y][x].layer[LAYER_ATTACK_IN0] = screen[y][x].layer[LAYER_ATTACK_IN1];
				screen[y][x].layer[LAYER_ATTACK_IN1] = 0;
			}
			if (screen[y][x].layer[LAYER_ATTACK_IN2] != 0){
				//screen[y][x].layer[LAYER_ATTACK_IN1] = screen[y][x].layer[LAYER_ATTACK_IN2];
				screen[y][x].layer[LAYER_ATTACK_IN2] = 0;
			}
			if (screen[y][x].layer[LAYER_ATTACK_IN3] != 0){
				//screen[y][x].layer[LAYER_ATTACK_IN2] = screen[y][x].layer[LAYER_ATTACK_IN3];
				screen[y][x].layer[LAYER_ATTACK_IN3] = 0;
			}
		}
	}

	//print_dyn_array(tab);

	while (tab->attack_queue[tab->size - 1].turn == current_turn){
		attack current_damage = pop(tab);
		if (current_damage.x == prota->x && current_damage.y == prota->y){
			//printf("%i, %i \n", prota->health, current_damage.damage);
			//printf("x: %i y: %i turn: %i damage: %i\n", current_damage.x, current_damage.y, current_damage.turn, current_damage.damage);
			prota->health -= current_damage.damage;
		}
	}

	int i = tab->size - 1;

	while(tab->attack_queue[i].turn - current_turn < 5){
		screen[tab->attack_queue[i].y][tab->attack_queue[i].x].layer[LAYER_ATTACK_IN0 - 1 + tab->attack_queue[i].turn - current_turn] = 1;
		i--;
	}
}


void update_enemy_health_bar(pixel **screen, enemy monster, screen_section health_bar){
	double health_per_block = (double) monster.max_health / (double) health_bar.width;

	for (int j = 0 ; j < health_bar.width ; j++){
		screen[health_bar.y_min][health_bar.x_min + j].layer[LAYER_HEALTH_FULL] = 0;
		screen[health_bar.y_min][health_bar.x_min + j].layer[LAYER_HEALTH_THREE_QUART] = 0;
		screen[health_bar.y_min][health_bar.x_min + j].layer[LAYER_HEALTH_HALF] = 0;
		screen[health_bar.y_min][health_bar.x_min + j].layer[LAYER_HEALTH_QUART] = 0;
	}

	int i = 0;
	while ((i + 1) * health_per_block <= monster.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[LAYER_HEALTH_FULL] = 1;
		i++;
	}
	screen[health_bar.y_min][health_bar.x_min + i].layer[LAYER_HEALTH_FULL] = 1;

	if((i + 0.75) * health_per_block <= monster.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[LAYER_HEALTH_THREE_QUART] = 1;
	} else if((i + 0.5) * health_per_block <= monster.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[LAYER_HEALTH_HALF] = 1;
	} else if((i + 0.25) * health_per_block * 0.25 <= monster.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[LAYER_HEALTH_QUART] = 1;
	}
}


void copy(char *src, char* dest, int length){
	for (int i = 0; i < length ; i++){
		dest[i] = src[i];
	}
}


void update_enemy_name(text_section *name_place, enemy monster){
	switch(monster.enemy_type.enemy_type_name){
		case DARK_MAGE:
			copy("Dark Mage", name_place->text, 9);
			name_place->length = 9;
			break;
		case DARK_KNIGHT:
			copy("Dark Knight", name_place->text, 11);
			name_place->length = 11;
			break;
		case DRAGON:
			copy("Dragon", name_place->text, 6);
			name_place->length = 6;
			break;
		case POSSESSED_TREE:
			copy("Possessed Tree", name_place->text, 14);
			name_place->length = 14;
			break;
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


void append_attack(dyn_array *tab, int x, int y, int turn, int damage){
	attack new_attack;
	new_attack.x = x;
	new_attack.y = y;
	new_attack.turn = turn;
	new_attack.damage = damage;
	append(tab, new_attack);
}


void slash_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn){
	int damage = get_attack_damage(current_enemy, SLASH);

	int line = rand() % play_area.height;
	int left_right = rand() % 2;
	for (int x = play_area.x_min; x <= play_area.x_max; x++){
		if (left_right){
			append_attack(tab, x, line + play_area.y_min, current_turn + 4 + ((x - play_area.x_min) / 2), damage);
		} else {
			append_attack(tab, play_area.x_max - x + play_area.x_min - 1, line + play_area.y_min, current_turn + 4 + (x - play_area.x_min) / 2, damage);
		}
	}
}


void spike_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn){
	int damage = get_attack_damage(current_enemy, SPIKES);

	int column = rand() % play_area.width;
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		append_attack(tab, play_area.x_min + column, play_area.y_max - y + play_area.y_min - 1, current_turn + 4 + y - play_area.y_min, damage);
	}
}


void meteor_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn){
	int damage = get_attack_damage(current_enemy, METEOR);

	int column = rand() % play_area.width;
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		append_attack(tab, play_area.x_min + column, y, current_turn + 4 + y - play_area.y_min, damage);
	}
}


void bouncy_ball(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn){
	int damage = get_attack_damage(current_enemy, BOUNCY_BALL);

	int x = rand() % play_area.width + play_area.x_min;
	int y = rand() % play_area.height + play_area.y_min;
	int x_dir = (rand() % 2) * 2 - 1;
	int y_dir = (rand() % 2) * 2 - 1;

	for (int i = 0; i < 200; i++){
		for (int x_off_set = 0; x_off_set < 2; x_off_set++){
			for (int y_off_set = 0; y_off_set < 2; y_off_set++){
				if (play_area.x_min <= x + x_off_set && x + x_off_set < play_area.x_max && play_area.y_min <= y + y_off_set && y + y_off_set < play_area.y_max){
					append_attack(tab, x + x_off_set, y + y_off_set, current_turn + i + 4, damage);
				}
			}
		}
		
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


void twinkles_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn){
	int damage = get_attack_damage(current_enemy, TWINKLES);


	for (int i = 0; i < 5; i++){

		int x_center = rand() % play_area.width + play_area.x_min;
		int y_center = rand() % play_area.height + play_area.y_min;

		for (int x = -1; x < 2; x++){
			for (int y = -1; y < 2; y++){
				if (play_area.x_min <= x + x_center && x + x_center < play_area.x_max && play_area.y_min <= y + y_center && y + y_center < play_area.y_max ){
					append_attack(tab, x + x_center, y + y_center, current_turn + 5, damage);
				}
			}
		}
		append_attack(tab, x_center, y_center, current_turn + 4, damage);
	}
}


void stab_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn){
	int damage = get_attack_damage(current_enemy, STAB);

	int x_center = rand() % play_area.width + play_area.x_min;
	int y_center = rand() % play_area.height + play_area.y_min;

	for (int x = -1; x < 2; x++){
		if (play_area.x_min <= x + x_center && x + x_center < play_area.x_max){
			append_attack(tab, x_center + x, y_center, current_turn + 5, damage);
		}	
	}
	for (int y = -1; y < 2; y++){
		if (play_area.y_min <= y + y_center && y + y_center < play_area.y_max ){
			append_attack(tab, x_center, y_center + y, current_turn + 5, damage);
		}
	}

	append_attack(tab, x_center, y_center, current_turn + 4, damage);
}


void tail_slap_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn){
	int damage = get_attack_damage(current_enemy, TAIL_SLAP);

	int line = rand() % play_area.height;
	int left_right = rand() % 2;
	for (int y = -1; y < 2; y++){
		if (0 <= y + line && y + line < play_area.height){
			for (int x = play_area.x_min; x <= play_area.x_max; x++){
				if (left_right){
					append_attack(tab, x, line + play_area.y_min + y, current_turn + 4 + (x - play_area.x_min) / 2, damage);
				} else {
					append_attack(tab, play_area.x_max - x + play_area.x_min, line + play_area.y_min + y, current_turn + 4 + (x - play_area.x_min) / 2, damage);
				}
			}
		}
	}
}


void fire_breath_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn){
	int damage = get_attack_damage(current_enemy, FIRE_BREATH);

	int center_x = rand() % play_area.width;
	int center_y = rand() % play_area.height;

	for (int radius = 6; radius > 0 ; radius--){
		for (int x = center_x - radius + play_area.x_min; x < center_x + radius + play_area.x_min; x++){
			for (int y = center_y - radius + play_area.y_min; y < center_y + radius + play_area.y_min; y++){
				if (play_area.x_min <= x && x < play_area.x_max && play_area.y_min <= y && y < play_area.y_max){
					if (distance_2(x, y, center_x + play_area.x_min, center_y + play_area.y_min) < radius * radius) {
						append_attack(tab, x, y, current_turn + radius + 4, damage);
					}
				}
			}
		}
	}
}


void add_attack(screen_section play_area, enemy current_enemy, dyn_array *tab, int current_turn){
	enum attack_types chosen_attack = choose_attack(current_enemy.enemy_type);
	switch (chosen_attack){
		case SLASH:
			slash_attack(play_area, current_enemy, tab, current_turn);
			break;
		case SPIKES:
			spike_attack(play_area, current_enemy, tab, current_turn);
			break;
		case METEOR:
			meteor_attack(play_area, current_enemy, tab, current_turn);
			break;
		case BOUNCY_BALL:
			bouncy_ball(play_area, current_enemy, tab, current_turn);
			break;
		case TWINKLES:
			twinkles_attack(play_area, current_enemy, tab, current_turn);
			break;
		case STAB:
			stab_attack(play_area, current_enemy, tab, current_turn);
			break;
		case TAIL_SLAP:
			tail_slap_attack(play_area, current_enemy, tab, current_turn);
			break;
		case FIRE_BREATH: 
			fire_breath_attack(play_area, current_enemy, tab, current_turn);
			break;
	}
	sort(tab);
}


enemy create_enemy_dark_knight(){
	enemy dark_knight;

	dark_knight.location = 1;
	dark_knight.max_health = 15;
	dark_knight.health = dark_knight.max_health;

	enemy_type type_dark_knight;

	type_dark_knight.enemy_type_name = DARK_KNIGHT;

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

	type_dark_mage.enemy_type_name = DARK_MAGE;

	type_dark_mage.different_attacks = 3;

	type_dark_mage.attack_codes[0] = METEOR;
	type_dark_mage.attack_codes[1] = TWINKLES;
	type_dark_mage.attack_codes[2] = BOUNCY_BALL;

	type_dark_mage.attack_weights[0] = 2;
	type_dark_mage.attack_weights[1] = 4;
	type_dark_mage.attack_weights[2] = 1;

	type_dark_mage.attack_damages[0] = 4;
	type_dark_mage.attack_damages[1] = 2;
	type_dark_mage.attack_damages[2] = 1;

	dark_mage.enemy_type = type_dark_mage;

	return dark_mage;
}


enemy create_enemy_dragon(){
	enemy dragon;

	dragon.location = 1;
	dragon.max_health = 50;
	dragon.health = dragon.max_health;

	enemy_type type_dragon;

	type_dragon.enemy_type_name = DRAGON;

	type_dragon.different_attacks = 3;

	type_dragon.attack_codes[0] = FIRE_BREATH;
	type_dragon.attack_codes[1] = TAIL_SLAP;
	type_dragon.attack_codes[2] = TWINKLES;

	type_dragon.attack_weights[0] = 1;
	type_dragon.attack_weights[1] = 2;
	type_dragon.attack_weights[2] = 1;

	type_dragon.attack_damages[0] = 4;
	type_dragon.attack_damages[1] = 2;
	type_dragon.attack_damages[2] = 2;

	dragon.enemy_type = type_dragon;

	return dragon;
}


enemy create_enemy_possessed_tree(){
	enemy possessed_tree;

	possessed_tree.location = 1;
	possessed_tree.max_health = 30;
	possessed_tree.health = possessed_tree.max_health;

	enemy_type type_possessed_tree;

	type_possessed_tree.enemy_type_name = POSSESSED_TREE;

	type_possessed_tree.different_attacks = 3;

	type_possessed_tree.attack_codes[0] = SPIKES;
	type_possessed_tree.attack_codes[1] = METEOR;
	type_possessed_tree.attack_codes[2] = TWINKLES;

	type_possessed_tree.attack_weights[0] = 2;
	type_possessed_tree.attack_weights[1] = 1;
	type_possessed_tree.attack_weights[2] = 2;

	type_possessed_tree.attack_damages[0] = 2;
	type_possessed_tree.attack_damages[1] = 3;
	type_possessed_tree.attack_damages[2] = 2;

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
		default:
			return create_enemy_dark_knight();
	}
}