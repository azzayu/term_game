#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct pixel_s {
	int layer[100];
	int local_damage;
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


void print_screen(pixel **pixel_mat, int width, int height, text_section** all_text);


text_section *init_text(int x_min, int x_max, int y, char* text, int length);


screen_section init_screen_section(int x_min, int y_min, int x_max, int y_max);


#endif