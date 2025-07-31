#include "attacks.h"
#include "structs.h"
#include "structs.h"
#include "enemy.h"
#include <stdlib.h>

int distance_2(int x1, int y1, int x2, int y2){
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}


int distance_man(int x1, int y1, int x2, int y2){
	return abs(x1 - x2) + abs(y1 - y2);
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
			//y_dir *= -1;
		}
		if (y < play_area.y_min || y > play_area.y_max){
			x -= 2 * x_dir;
			y -= 2 * y_dir;
			//x_dir *= -1;
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
