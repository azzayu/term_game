#include "player.h"


int move_player(pixel **screen, player *prota, char input, int width, int height, screen_section play_area){
	/*
		returns 1 if move succesfull 
		0 if not
	*/
	
	if (input == 'z' && prota->y > play_area.y_min && prota->stamina > 0){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->y -= 1;
		screen[prota->y][prota->x].layer[0] = 1;
		prota->stamina--;
		return 1;
	}
	if (input == 's' && prota->y < play_area.y_max - 1 && prota->stamina > 0){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->y += 1;
		screen[prota->y][prota->x].layer[0] = 1;
		prota->stamina--;
		return 1;
	}
	if (input == 'd' && prota->x < play_area.x_max - 1 && prota->stamina > 0){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->x += 1;
		screen[prota->y][prota->x].layer[0] = 1;
		prota->stamina--;
		return 1;
	}
	if (input == 'q' && prota->x > play_area.x_min && prota->stamina > 0){
		screen[prota->y][prota->x].layer[0] = 0;
		prota->x -= 1;
		screen[prota->y][prota->x].layer[0] = 1;
		prota->stamina--;
		return 1;
	}
	if (input == 'w'){
		//counts as resting
		prota->stamina += 3;
		if (prota->stamina > prota->max_stamina){
			prota->stamina = prota->max_stamina;
		}
		return 1;
	}
	return 0;
}


void update_health_bar(pixel **screen, player prota, screen_section health_bar){
	double health_per_block = (double) prota.max_health / (double) health_bar.width;

	for (int j = 0 ; j < health_bar.width ; j++){
		screen[health_bar.y_min][health_bar.x_min + j].layer[8] = 0;
		screen[health_bar.y_min][health_bar.x_min + j].layer[9] = 0;
		screen[health_bar.y_min][health_bar.x_min + j].layer[10] = 0;
		screen[health_bar.y_min][health_bar.x_min + j].layer[11] = 0;
	}

	int i = 0;
	while ((i + 1) * health_per_block <= prota.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[8] = 1;
		i++;
	}

	if((i + 0.75) * health_per_block <= prota.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[9] = 1;
	} else if((i + 0.5) * health_per_block <= prota.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[10] = 1;
	} else if((i + 0.25) * health_per_block * 0.25 <= prota.health){
		screen[health_bar.y_min][health_bar.x_min + i].layer[11] = 1;
	}
}


void update_stamina_bar(pixel **screen, player prota, screen_section stamina_bar){
	double stamina_per_block = (double) prota.max_stamina / (double) stamina_bar.width;

	for (int j = 0 ; j < stamina_bar.width ; j++){
		screen[stamina_bar.y_min][stamina_bar.x_min + j].layer[18] = 0;
		screen[stamina_bar.y_min][stamina_bar.x_min + j].layer[19] = 0;
		screen[stamina_bar.y_min][stamina_bar.x_min + j].layer[20] = 0;
		screen[stamina_bar.y_min][stamina_bar.x_min + j].layer[21] = 0;
	}

	int i = 0;
	while ((i + 1) * stamina_per_block <= prota.stamina){
		screen[stamina_bar.y_min][stamina_bar.x_min + i].layer[18] = 1;
		i++;
	}

	if((i + 0.75) * stamina_per_block <= prota.stamina){
		screen[stamina_bar.y_min][stamina_bar.x_min + i].layer[19] = 1;
	} else if((i + 0.5) * stamina_per_block <= prota.stamina){
		screen[stamina_bar.y_min][stamina_bar.x_min + i].layer[20] = 1;
	} else if((i + 0.25) * stamina_per_block * 0.25 <= prota.stamina){
		screen[stamina_bar.y_min][stamina_bar.x_min + i].layer[21] = 1;
	}
}


player init_player(int x, int y, int max_health, int max_stamina){
	player prota;

	prota.x = x;
	prota.y = y;
	prota.max_health = max_health;
	prota.max_stamina = max_stamina;

	prota.health = max_health;
	prota.stamina = max_stamina;

	return prota;
}
