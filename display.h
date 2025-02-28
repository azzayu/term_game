

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


pixel **init_screen(int width, int height, screen_section play_area);


void default_test_screen();


void free_screen(pixel **pixel_mat, int width, int height);


void print_screen(pixel **pixel_mat, int width, int height);
