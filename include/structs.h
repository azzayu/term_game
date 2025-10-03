#ifndef STRUCT_H
#define STRUCT_H

typedef enum display_colours_s
{
    VALUE_NONE = 0,
    VALUE_BLACK = 1,
    VALUE_RED = 2,
    VALUE_GREEN = 3,
    VALUE_YELLOW = 4,
    VALUE_BLUE = 5,
    VALUE_MAGENTA = 6,
    VALUE_CYAN = 7,
    VALUE_WHITE = 8,
    VALUE_BRIGHT_BLACK = 9,
    VALUE_BRIGHT_RED = 10,
    VALUE_BRIGHT_GREEN = 11,
    VALUE_BRIGHT_YELLOW = 12,
    VALUE_BRIGHT_BLUE = 13,
    VALUE_BRIGHT_MAGENTA = 14,
    VALUE_BRIGHT_CYAN = 15,
    VALUE_BRIGHT_WHITE = 16,
    VALUE_TEXT_ID = 17
} display_colours;

typedef enum display_pixel_types_s
{
    PIXEL_FULL_BLOCK = 0,  
    PIXEL_THREE_QUART_BLOCK = 1,        
    PIXEL_HALF_BLOCK = 2,
    PIXEL_QUART_BLOCK = 3,    
    PIXEL_VERT_WALL_LEFT = 4,       
    PIXEL_VERT_WALL_RIGHT = 5,
    PIXEL_HORI_WALL = 6,
    PIXEL_TOP_LEFT_CORNER = 7,
    PIXEL_TOP_RIGHT_CORNER = 8,
    PIXEL_BOTTOM_LEFT_CORNER = 9,
    PIXEL_BOTTOM_RIGHT_CORNER = 10,
    PIXEL_RIGHT_JUNCTION = 11,
    PIXEL_LEFT_JUNCTION = 12,
    PIXEL_UP_RIGHT_JUNCTION = 13,
    PIXEL_UP_LEFT_JUNCTION = 14,
    PIXEL_DOWN_LEFT_JUNCTION = 15,
    PIXEL_DOWN_RIGHT_JUNCTION = 16,
    PIXEL_LEFT_CROSS_JUNCTION = 17,
    PIXEL_RIGHT_CROSS_JUNCTION = 18,
    PIXEL_START_TEXT = 19,
    PIXEL_TEXT = 20
} display_pixel_types;

typedef struct pixel_s
{
    display_colours colour;
    display_pixel_types pixel_type;
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

typedef enum enemy_types_names_s
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
} enemy_types_names;

typedef enum attack_types_s
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
} attack_types;

typedef struct enemy_type_s
{
    int different_attacks;

    attack_types attack_codes[10];
    int attack_weights[10];
    int attack_damages[10];

    int enemy_move_chance; // as a percentage chance

    int base_exp_reward;

    enemy_types_names enemy_type_name;
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
