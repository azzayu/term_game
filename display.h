

typedef struct pixel_s {
	int layer[100];
} pixel;


typedef struct play_screen_s{
	int x_min;
	int y_min;
	int x_max;
	int y_max;

	int width;
	int height;
} play_screen;


pixel **init_screen(int width, int height, play_screen play_area);


void default_test_screen();


void free_screen(pixel **pixel_mat, int width, int height);


void print_screen(pixel **pixel_mat, int width, int height);
