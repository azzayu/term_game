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

	type_dark_knight.different_attacks = 3;

	type_dark_knight.attack_codes[0] = SLASH;
	type_dark_knight.attack_codes[1] = STAB;
	type_dark_knight.attack_codes[2] = DIRECT_SLASH;

	type_dark_knight.attack_weights[0] = 2;
	type_dark_knight.attack_weights[1] = 1;
	type_dark_knight.attack_weights[2] = 1;

	type_dark_knight.attack_damages[0] = 1 * (1 + (double)dark_knight.level / 3.0);
	type_dark_knight.attack_damages[1] = 3 * (1 + (double)dark_knight.level / 3.0);
	type_dark_knight.attack_damages[2] = 2 * (1 + (double)dark_knight.level / 3.0);

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

enemy create_enemy_golem(int enemies_defeated)
{
	enemy golem;

	golem.level = enemies_defeated / 5 + 1;

	golem.location = 1;
	golem.max_health = 70 * (1 + (double)golem.level / 3.0);
	golem.health = golem.max_health;

	enemy_type type_golem;

	type_golem.enemy_type_name = GOLEM;

	type_golem.different_attacks = 5;

	type_golem.attack_codes[0] = SMALL_SMASH;
	type_golem.attack_codes[1] = BIG_SMASH;
	type_golem.attack_codes[2] = METEOR;
	type_golem.attack_codes[3] = CRUMBLE;
	type_golem.attack_codes[4] = SPIKES;

	type_golem.attack_weights[0] = 4;
	type_golem.attack_weights[1] = 1;
	type_golem.attack_weights[2] = 5;
	type_golem.attack_weights[3] = 2;
	type_golem.attack_weights[4] = 3;

	type_golem.attack_damages[0] = 3 * (1 + (double)golem.level / 3.0);
	type_golem.attack_damages[1] = 1 * (1 + (double)golem.level / 3.0);
	type_golem.attack_damages[2] = 2 * (1 + (double)golem.level / 3.0);
	type_golem.attack_damages[3] = 2 * (1 + (double)golem.level / 3.0);
	type_golem.attack_damages[4] = 2 * (1 + (double)golem.level / 3.0);

	type_golem.enemy_move_chance = 7;

	type_golem.base_exp_reward = 4 * (1 + (double)golem.level / 2.0);

	golem.enemy_type = type_golem;

	return golem;
}

enemy create_enemy_sea_serpent(int enemies_defeated)
{
	enemy sea_serpent;

	sea_serpent.level = enemies_defeated / 5 + 1;

	sea_serpent.location = 1;
	sea_serpent.max_health = 30 * (1 + (double)sea_serpent.level / 3.0);
	sea_serpent.health = sea_serpent.max_health;

	enemy_type type_sea_serpent;

	type_sea_serpent.enemy_type_name = SEA_SERPENT;

	type_sea_serpent.different_attacks = 4;

	type_sea_serpent.attack_codes[0] = SIMPLE_SPIRAL;
	type_sea_serpent.attack_codes[1] = DOUBLE_SPIRAL;
	type_sea_serpent.attack_codes[2] = MIST;
	type_sea_serpent.attack_codes[3] = WAVE;

	type_sea_serpent.attack_weights[0] = 4;
	type_sea_serpent.attack_weights[1] = 3;
	type_sea_serpent.attack_weights[2] = 1;
	type_sea_serpent.attack_weights[3] = 4;

	type_sea_serpent.attack_damages[0] = 1 * (1 + (double)sea_serpent.level / 3.0);
	type_sea_serpent.attack_damages[1] = 2 * (1 + (double)sea_serpent.level / 3.0);
	type_sea_serpent.attack_damages[2] = 0 * (1 + (double)sea_serpent.level / 3.0);
	type_sea_serpent.attack_damages[3] = 2 * (1 + (double)sea_serpent.level / 3.0);

	type_sea_serpent.enemy_move_chance = 35;

	type_sea_serpent.base_exp_reward = 4 * (1 + (double)sea_serpent.level / 2.0);

	sea_serpent.enemy_type = type_sea_serpent;

	return sea_serpent;
}

enemy create_enemy_mystery(int enemies_defeated)
{
	enemy mystery;

	mystery.level = enemies_defeated / 5 + 1;

	mystery.location = 1;
	mystery.max_health = 15 * (1 + (double)mystery.level / 3.0);
	mystery.health = mystery.max_health;

	enemy_type type_mystery;

	type_mystery.enemy_type_name = MYSTERY;

	type_mystery.different_attacks = 2;

	type_mystery.attack_codes[0] = TETRIS_FALL;
	type_mystery.attack_codes[1] = MIST;

	type_mystery.attack_weights[0] = 15;
	type_mystery.attack_weights[1] = 1;

	type_mystery.attack_damages[0] = 2 * (1 + (double)mystery.level / 3.0);
	type_mystery.attack_damages[1] = 0 * (1 + (double)mystery.level / 3.0);

	type_mystery.enemy_move_chance = 20;

	type_mystery.base_exp_reward = 2 * (1 + (double)mystery.level / 2.0);

	mystery.enemy_type = type_mystery;

	return mystery;
}

enemy create_enemy_arch_mage(int enemies_defeated)
{
	enemy arch_mage;

	arch_mage.level = enemies_defeated / 5 + 1;

	arch_mage.location = 1;
	arch_mage.max_health = 10 * (1 + (double)arch_mage.level / 3.0);
	arch_mage.health = arch_mage.max_health;

	enemy_type type_arch_mage;

	type_arch_mage.enemy_type_name = ARCH_MAGE;

	type_arch_mage.different_attacks = 5;

	type_arch_mage.attack_codes[0] = CLOSE_IN;
	type_arch_mage.attack_codes[1] = SHATTER;
	type_arch_mage.attack_codes[2] = EXPLOSION;
	type_arch_mage.attack_codes[3] = PLAYER_CIRCLE; // replace with a heal
	type_arch_mage.attack_codes[4] = BOUNCY_BALL;

	type_arch_mage.attack_weights[0] = 1;
	type_arch_mage.attack_weights[1] = 3;
	type_arch_mage.attack_weights[2] = 2;
	type_arch_mage.attack_weights[3] = 1;
	type_arch_mage.attack_weights[4] = 3;

	type_arch_mage.attack_damages[0] = 3 * (1 + (double)arch_mage.level / 3.0);
	type_arch_mage.attack_damages[1] = 3 * (1 + (double)arch_mage.level / 3.0);
	type_arch_mage.attack_damages[2] = 4 * (1 + (double)arch_mage.level / 3.0);
	type_arch_mage.attack_damages[3] = 2 * (1 + (double)arch_mage.level / 3.0);
	type_arch_mage.attack_damages[4] = 2 * (1 + (double)arch_mage.level / 3.0);

	type_arch_mage.enemy_move_chance = 5;

	type_arch_mage.base_exp_reward = 3 * (1 + (double)arch_mage.level / 2.0);

	arch_mage.enemy_type = type_arch_mage;

	return arch_mage;
}

enemy create_enemy_shaman(int enemies_defeated)
{
	enemy shaman;

	shaman.level = enemies_defeated / 5 + 1;

	shaman.location = 1;
	shaman.max_health = 25 * (1 + (double)shaman.level / 3.0);
	shaman.health = shaman.max_health;

	enemy_type type_shaman;

	type_shaman.enemy_type_name = SHAMAN;

	type_shaman.different_attacks = 4;

	type_shaman.attack_codes[0] = TAIL_SLAP;
	type_shaman.attack_codes[1] = PLAYER_SQUARE;
	type_shaman.attack_codes[2] = SNAKE;
	type_shaman.attack_codes[3] = WAVE;

	type_shaman.attack_weights[0] = 3;
	type_shaman.attack_weights[1] = 1;
	type_shaman.attack_weights[2] = 2;
	type_shaman.attack_weights[3] = 3;

	type_shaman.attack_damages[0] = 2 * (1 + (double)shaman.level / 3.0);
	type_shaman.attack_damages[1] = 1 * (1 + (double)shaman.level / 3.0);
	type_shaman.attack_damages[2] = 2 * (1 + (double)shaman.level / 3.0);
	type_shaman.attack_damages[3] = 1 * (1 + (double)shaman.level / 3.0);

	type_shaman.enemy_move_chance = 30;

	type_shaman.base_exp_reward = 2 * (1 + (double)shaman.level / 2.0);

	shaman.enemy_type = type_shaman;

	return shaman;
}
