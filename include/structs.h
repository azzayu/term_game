#ifndef STRUCT_H
#define STRUCT_H

typedef struct pixel_s
{
    int layer[100];
    int local_damage;
} pixel;

typedef struct screen_section_s
{
    int x_min;
    int y_min;
    int x_max;
    int y_max;

    int width;
    int height;
} screen_section;

typedef struct text_section_s
{
    int x_min;
    int x_max;
    int y;

    char text[100];
    int length;

    int width;
} text_section;

typedef struct player_s
{
    int x;
    int y;

    int max_health;
    int health;

    int max_stamina;
    int stamina;

    int level;
    int exp;
    int exp_to_next_level;

    int charged;
    int aiming;

    int attack;
} player;

enum enemy_types_names
{
    DARK_KNIGHT = 0,
    POSSESSED_TREE = 1,
    DARK_MAGE = 2,
    DRAGON = 3,
    GOLEM = 4,
    SEA_SERPENT = 5,
    MYSTERY = 6,
    ARCH_MAGE = 7,
    SHAMAN = 8
};

enum attack_types
{
    SLASH = 0,          // dark_knight,
    SPIKES = 1,         // possessed_tree, golem
    METEOR = 2,         // dark_mage, possessed_tree, golem
    BOUNCY_BALL = 3,    // dark_mage, arch_mage
    TWINKLES = 4,       // dark_mage, dragon, possessed_tree
    STAB = 5,           // dark_knight,
    TAIL_SLAP = 6,      // dragon, shaman
    FIRE_BREATH = 7,    // dragon
    SMALL_SMASH = 8,    // golem
    BIG_SMASH = 9,      // golem
    SIMPLE_SPIRAL = 10, // sea_serpent
    DOUBLE_SPIRAL = 11, // sea_serpent
    WAVE = 12,          // sea_serpent, shaman
    DIRECT_SLASH = 13,  // dark_knight,
    CLOSE_IN = 14,      // arch_mage
    CRUMBLE = 15,       // golem
    SHATTER = 16,       // arch_mage
    MIST = 17,          // sea_serpent, mystery
    EXPLOSION = 18,     // arch_mage
    TETRIS_FALL = 19,   // mystery
    PLAYER_CIRCLE = 20, // arch_mage
    PLAYER_SQUARE = 21, // shaman
    SNAKE = 22          // shaman
};

typedef struct enemy_type_s
{
    int different_attacks;

    enum attack_types attack_codes[10];
    int attack_weights[10];
    int attack_damages[10];

    int enemy_move_chance; // as a percentage chance

    int base_exp_reward;

    enum enemy_types_names enemy_type_name;
} enemy_type;

typedef struct attack_s
{
    int x;
    int y;
    int damage;
    int turn;
} attack;

typedef struct dyn_array_s
{
    int mem_size;
    int size;
    attack *attack_queue;
} dyn_array;

typedef struct enemy_s
{
    int location;

    int max_health;
    int health;

    int level;

    enemy_type enemy_type;
} enemy;

typedef struct game_state_s
{
    player *prota;

    int enemies_defeated;

    char *save_file_name;
} game_state;

#endif
