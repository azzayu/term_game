
#define FULL_BLOCK "██"
#define THREE_QUART_BLOCK "▓▓"
#define HALF_BLOCK "▒▒"
#define QUART_BLOCK "░░"
#define VERT_WALL_LEFT "║ "
#define VERT_WALL_RIGHT " ║"
#define HORI_WALL "══"
#define TOP_LEFT_CORNER " ╔"
#define TOP_RIGHT_CORNER "╗ "
#define BOTTOM_LEFT_CORNER " ╚"
#define BOTTOM_RIGHT_CORNER "╝ "
#define RIGHT_JUNCTION " ╠"
#define LEFT_JUNCTION "╣ "
#define UP_RIGHT_JUNCTION "═╩"
#define UP_LEFT_JUNCTION "╩═"
#define DOWN_LEFT_JUNCTION "╦═"
#define DOWN_RIGHT_JUNCTION "═╦"


#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BRIGHT_BLACK "\033[0;90m"
#define BRIGHT_RED "\033[0;91m"
#define BRIGHT_GREEN "\033[0;92m"
#define BRIGHT_YELLOW "\033[0;93m"
#define BRIGHT_BLUE "\033[0;94m"
#define BRIGHT_MAGENTA "\033[0;95m"
#define BRIGHT_CYAN "\033[0;96m"
#define BRIGHT_WHITE "\033[0;97m"

#define LAYER_PLAYER 0
#define LAYER_VERT_WALL_LEFT 1
#define LAYER_VERT_WALL_RIGHT 2
#define LAYER_HORI_WALL 3
#define LAYER_TOP_LEFT_CORNER 4
#define LAYER_TOP_RIGHT_CORNER 5
#define LAYER_BOTTOM_LEFT_CORNER 6
#define LAYER_BOTTOM_RIGHT_CORNER 7
#define LAYER_ATTACK_IN0 8
#define LAYER_ATTACK_IN1 9
#define LAYER_ATTACK_IN2 10
#define LAYER_ATTACK_IN3 11
#define LAYER_HEALTH_FULL 8
#define LAYER_HEALTH_THREE_QUART 9
#define LAYER_HEALTH_HALF 10
#define LAYER_HEALTH_QUART 11
#define LAYER_RIGHT_JUNCTION 12
#define LAYER_LEFT_JUNCTION 13
#define LAYER_UP_RIGHT_JUNCTION 14
#define LAYER_UP_LEFT_JUNCTION 15
#define LAYER_DOWN_LEFT_JUNCTION 16
#define LAYER_DOWN_RIGHT_JUNCTION 17
#define LAYER_STAMINA_FULL 18
#define LAYER_STAMINA_THREE_QUART 19
#define LAYER_STAMINA_HALF 20
#define LAYER_STAMINA_QUART 21
#define LAYER_TEXT 22
#define LAYER_TEXT_BEFORE 23
#define LAYER_DEFAULT 50

typedef struct pixel_s {
	int layer[100];
} pixel;


typedef struct screen_section_s{
	int x_min;
	int y_min;
	int x_max;
	int y_max;

	int width;
	int height;
} screen_section;


typedef struct text_section_s{
	int x_min;
	int x_max;
	int y;

	char text[100];
	int length;

	int width;
} text_section;


pixel **init_screen(int width, int height, screen_section play_area, screen_section enemy_locations[3]);


void default_test_screen();


void free_screen(pixel **pixel_mat, int width, int height);


void print_screen(pixel **pixel_mat, int width, int height, text_section* all_text);


text_section init_text(int x_min, int x_max, int y, char* text, int length);


screen_section init_screen_section(int x_min, int y_min, int x_max, int y_max);
