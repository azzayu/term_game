#include "enemy.h"
#include "display_cst.h"
#include "dyn_array.h"
#include "player.h"
#include "structs.h"
#include "attacks.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void update_attacks(pixel **screen, player *prota, screen_section play_area, dyn_array *tab, int current_turn){

	//resets the screen to remove all attacks
	for (int y = play_area.y_min; y < play_area.y_max; y++){
		for (int x = play_area.x_min; x < play_area.x_max; x++){
			screen[y][x].layer[LAYER_ATTACK_IN0] = 0;
			screen[y][x].layer[LAYER_ATTACK_IN1] = 0;
			screen[y][x].layer[LAYER_ATTACK_IN2] = 0;
			screen[y][x].layer[LAYER_ATTACK_IN3] = 0;

		}
	}

	//print_dyn_array(*tab);

	if (tab->size == 0){
		return;
	}

	//print_dyn_array(*tab);

	while (tab->attack_queue[tab->size - 1].turn == current_turn){
		attack current_damage = pop(tab);
		if (current_damage.x == prota->x && current_damage.y == prota->y){
			//printf("%i, %i \n", prota->health, current_damage.damage);
			//printf("x: %i y: %i turn: %i damage: %i\n", current_damage.x, current_damage.y, current_damage.turn, current_damage.damage);
			prota->health -= current_damage.damage;
		}
	}

	//print_dyn_array(*tab);

	if (tab->size == 0){
		return;
	}

	int i = tab->size - 1;

	while(tab->attack_queue[i].turn - current_turn < 5 && i > 0){
		screen[tab->attack_queue[i].y][tab->attack_queue[i].x].layer[LAYER_ATTACK_IN0 - 1 + tab->attack_queue[i].turn - current_turn] = 1;
		i--;
	}
}


void update_enemy_health_bar(pixel **screen, enemy monster, screen_section health_bar){
	double health_per_block = (double) monster.max_health / (double) (health_bar.width + 1);

	//resets the bar to empty
	for (int j = 0 ; j <= health_bar.width ; j++){
		screen[health_bar.y_min][health_bar.x_min + j].layer[LAYER_HEALTH_FULL] = 0;
		screen[health_bar.y_min][health_bar.x_min + j].layer[LAYER_HEALTH_THREE_QUART] = 0;
		screen[health_bar.y_min][health_bar.x_min + j].layer[LAYER_HEALTH_HALF] = 0;
		screen[health_bar.y_min][health_bar.x_min + j].layer[LAYER_HEALTH_QUART] = 0;
	}


	//displays the full blocks
	int i = 0;
	while ((i + 1) * health_per_block <= monster.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[LAYER_HEALTH_FULL] = 1;
		i++;
	}

	//displays the last partial bar
	if((i + 0.75) * health_per_block <= monster.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[LAYER_HEALTH_THREE_QUART] = 1;
	} else if((i + 0.5) * health_per_block <= monster.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[LAYER_HEALTH_HALF] = 1;
	} else if((i + 0.25) * health_per_block <= monster.health){
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

	type_dark_knight.enemy_move_chance = 40;

	type_dark_knight.base_exp_reward = 1;

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

	type_dark_mage.enemy_move_chance = 5;

	type_dark_mage.base_exp_reward = 3;

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
	type_dragon.attack_weights[1] = 4;
	type_dragon.attack_weights[2] = 2;

	type_dragon.attack_damages[0] = 4;
	type_dragon.attack_damages[1] = 2;
	type_dragon.attack_damages[2] = 2;

	type_dragon.enemy_move_chance = 30;

	type_dragon.base_exp_reward = 5;

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

	type_possessed_tree.enemy_move_chance = 1;

	type_possessed_tree.base_exp_reward = 2;

	possessed_tree.enemy_type = type_possessed_tree;

	return possessed_tree;
}


void reset_enemy_location(pixel **screen, screen_section *enemy_location){

	for (int x = enemy_location->x_min + 1; x < enemy_location->x_max; x++){
		for (int y = enemy_location->y_min + 1; y < enemy_location->y_max; y++){
			screen[y][x].layer[LAYER_HORI_WALL] = 0;
			screen[y][x].layer[LAYER_VERT_WALL_LEFT] = 0;
			screen[y][x].layer[LAYER_VERT_WALL_RIGHT] = 0;
			screen[y][x].layer[LAYER_TOP_LEFT_CORNER] = 0;
			screen[y][x].layer[LAYER_TOP_RIGHT_CORNER] = 0;
			screen[y][x].layer[LAYER_BOTTOM_LEFT_CORNER] = 0;
			screen[y][x].layer[LAYER_BOTTOM_RIGHT_CORNER] = 0;
			screen[y][x].layer[LAYER_UP_LEFT_JUNCTION] = 0;
			screen[y][x].layer[LAYER_UP_RIGHT_JUNCTION] = 0;
			screen[y][x].layer[LAYER_DOWN_LEFT_JUNCTION] = 0;
			screen[y][x].layer[LAYER_DOWN_RIGHT_JUNCTION] = 0;
			screen[y][x].layer[LAYER_LEFT_JUNCTION] = 0;
			screen[y][x].layer[LAYER_RIGHT_JUNCTION] = 0;
		}
	}

}


enemy create_enemy(pixel** screen, screen_section enemy_locations[3]){
	enum enemy_types_names new_enemy_type = rand() % NB_ENEMY_TYPES;

	for (int i = 0; i < 3; i++){
		reset_enemy_location(screen, &(enemy_locations[i]));
	}

	//drawing the enemy

	int center_x = (enemy_locations[1].x_min + enemy_locations[1].x_max) / 2;
	int center_y = (enemy_locations[1].y_min + enemy_locations[1].y_max) / 2;

	screen[center_y][center_x].layer[LAYER_HORI_WALL] = 1;
	screen[center_y - 1][center_x].layer[LAYER_HORI_WALL] = 1;
	screen[center_y + 1][center_x].layer[LAYER_HORI_WALL] = 1;
	screen[center_y][center_x + 1].layer[LAYER_HORI_WALL] = 1;
	screen[center_y - 1][center_x + 1].layer[LAYER_HORI_WALL] = 1;
	screen[center_y + 1][center_x + 1].layer[LAYER_HORI_WALL] = 1;
	screen[center_y][center_x + 2].layer[LAYER_LEFT_JUNCTION] = 1;
	screen[center_y][center_x - 1].layer[LAYER_RIGHT_JUNCTION] = 1;
	screen[center_y - 1][center_x - 1].layer[LAYER_TOP_LEFT_CORNER] = 1;
	screen[center_y - 1][center_x + 2].layer[LAYER_TOP_RIGHT_CORNER] = 1;
	screen[center_y + 1][center_x - 1].layer[LAYER_BOTTOM_LEFT_CORNER] = 1;
	screen[center_y + 1][center_x + 2].layer[LAYER_BOTTOM_RIGHT_CORNER] = 1;
	
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


void update_enemy_location(pixel **screen, enemy *current_enemy, screen_section enemy_locations[3]){
	int random_selection = rand() % 100;

	if (random_selection < current_enemy->enemy_type.enemy_move_chance){

		int enemy_location = current_enemy->location;

		reset_enemy_location(screen, &(enemy_locations[enemy_location]));

		if (enemy_location == 0) {
			current_enemy->location = 1;
			enemy_location = 1;
		} else if (enemy_location == 2) {
			current_enemy->location = 1;
			enemy_location = 1;	
		} else {
			if (random_selection % 2 == 0) {
				current_enemy->location = 0;
				enemy_location = 0;
			} else {
				current_enemy->location = 2;
				enemy_location = 2;
			}
		}

		int center_x = (enemy_locations[enemy_location].x_min + enemy_locations[enemy_location].x_max) / 2;
		int center_y = (enemy_locations[enemy_location].y_min + enemy_locations[enemy_location].y_max) / 2;

		screen[center_y][center_x].layer[LAYER_HORI_WALL] = 1;
		screen[center_y - 1][center_x].layer[LAYER_HORI_WALL] = 1;
		screen[center_y + 1][center_x].layer[LAYER_HORI_WALL] = 1;
		screen[center_y][center_x + 1].layer[LAYER_HORI_WALL] = 1;
		screen[center_y - 1][center_x + 1].layer[LAYER_HORI_WALL] = 1;
		screen[center_y + 1][center_x + 1].layer[LAYER_HORI_WALL] = 1;
		screen[center_y][center_x + 2].layer[LAYER_LEFT_JUNCTION] = 1;
		screen[center_y][center_x - 1].layer[LAYER_RIGHT_JUNCTION] = 1;
		screen[center_y - 1][center_x - 1].layer[LAYER_TOP_LEFT_CORNER] = 1;
		screen[center_y - 1][center_x + 2].layer[LAYER_TOP_RIGHT_CORNER] = 1;
		screen[center_y + 1][center_x - 1].layer[LAYER_BOTTOM_LEFT_CORNER] = 1;
		screen[center_y + 1][center_x + 2].layer[LAYER_BOTTOM_RIGHT_CORNER] = 1;

	}

}


void clear_attacks(pixel **screen, screen_section play_area, dyn_array *tab){
	while (tab->size > 0){
		pop(tab);
	}

	for (int x = play_area.x_min; x < play_area.x_max; x++){
		for (int y = play_area.y_min; y < play_area.y_max; y++){
			screen[y][x].layer[LAYER_ATTACK_IN0] = 0;
			screen[y][x].layer[LAYER_ATTACK_IN1] = 0;
			screen[y][x].layer[LAYER_ATTACK_IN2] = 0;
			screen[y][x].layer[LAYER_ATTACK_IN3] = 0;
		}
	}
}
