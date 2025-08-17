#include "enemy_types.h"
#include "enemy.h"
#include "structs.h"

enemy create_enemy_dark_knight(int enemies_defeated)
{
	enemy dark_knight;

	dark_knight.level = enemies_defeated / 5 + 1;

	dark_knight.location = 1;
	dark_knight.max_health = 15 * (1 + (double)dark_knight.level / 3.0);
	dark_knight.health = dark_knight.max_health;

	enemy_type type_dark_knight;

	type_dark_knight.enemy_type_name = DARK_KNIGHT;

	type_dark_knight.different_attacks = 2;

	type_dark_knight.attack_codes[0] = SLASH;
	type_dark_knight.attack_codes[1] = STAB;

	type_dark_knight.attack_weights[0] = 2;
	type_dark_knight.attack_weights[1] = 1;

	type_dark_knight.attack_damages[0] = 1 * (1 + (double)dark_knight.level / 3.0);
	type_dark_knight.attack_damages[1] = 3 * (1 + (double)dark_knight.level / 3.0);

	type_dark_knight.enemy_move_chance = 40;

	type_dark_knight.base_exp_reward = 1 * (1 + (double)dark_knight.level / 2.0);

	dark_knight.enemy_type = type_dark_knight;

	return dark_knight;
}

enemy create_enemy_dark_mage(int enemies_defeated)
{
	enemy dark_mage;

	dark_mage.level = enemies_defeated / 5 + 1;

	dark_mage.location = 1;
	dark_mage.max_health = 25 * (1 + (double)dark_mage.level / 3.0);
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

	type_dark_mage.attack_damages[0] = 4 * (1 + (double)dark_mage.level / 3.0);
	type_dark_mage.attack_damages[1] = 2 * (1 + (double)dark_mage.level / 3.0);
	type_dark_mage.attack_damages[2] = 1 * (1 + (double)dark_mage.level / 3.0);

	type_dark_mage.enemy_move_chance = 5;

	type_dark_mage.base_exp_reward = 3 * (1 + (double)dark_mage.level / 2.0);

	dark_mage.enemy_type = type_dark_mage;

	return dark_mage;
}

enemy create_enemy_dragon(int enemies_defeated)
{
	enemy dragon;

	dragon.level = enemies_defeated / 5 + 1;

	dragon.location = 1;
	dragon.max_health = 50 * (1 + (double)dragon.level / 3.0);
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

	type_dragon.attack_damages[0] = 4 * (1 + (double)dragon.level / 3.0);
	type_dragon.attack_damages[1] = 2 * (1 + (double)dragon.level / 3.0);
	type_dragon.attack_damages[2] = 2 * (1 + (double)dragon.level / 3.0);

	type_dragon.enemy_move_chance = 30;

	type_dragon.base_exp_reward = 5 * (1 + (double)dragon.level / 2.0);

	dragon.enemy_type = type_dragon;

	return dragon;
}

enemy create_enemy_possessed_tree(int enemies_defeated)
{
	enemy possessed_tree;

	possessed_tree.level = enemies_defeated / 5 + 1;

	possessed_tree.location = 1;
	possessed_tree.max_health = 30 * (1 + (double)possessed_tree.level / 3.0);
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

	type_possessed_tree.attack_damages[0] = 2 * (1 + (double)possessed_tree.level / 3.0);
	type_possessed_tree.attack_damages[1] = 3 * (1 + (double)possessed_tree.level / 3.0);
	type_possessed_tree.attack_damages[2] = 2 * (1 + (double)possessed_tree.level / 3.0);

	type_possessed_tree.enemy_move_chance = 1;

	type_possessed_tree.base_exp_reward = 2 * (1 + (double)possessed_tree.level / 2.0);

	possessed_tree.enemy_type = type_possessed_tree;

	return possessed_tree;
}
