#include "player.h"

#define NB_ENEMY_TYPES 4

enum enemy_types_names{
    DARK_KNIGHT = 0,
    POSSESSED_TREE = 1,
    DARK_MAGE = 2,
    DRAGON = 3
};

enum attack_types{
    SLASH = 0,
    SPIKES = 1,
    METEOR = 2,
    BOUNCY_BALL = 3,
    TWINKLES = 4,
    STAB = 5,
    TAIL_SLAP = 6,
    FIRE_BREATH = 7
};

typedef struct enemy_type_s{
    int different_attacks;

    enum attack_types attack_codes[10];
    int attack_weights[10];
    int attack_damages[10];

    enum enemy_types_names enemy_type_name;
} enemy_type;

typedef struct enemy_s{
	int location;

	int max_health;
	int health;

    enemy_type enemy_type;
} enemy;


void add_attack(pixel **screen, screen_section play_area);

void update_attacks(pixel **screen, int width, int height, player *prota, screen_section play_area);

enemy create_enemy();
