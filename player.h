
typedef struct player_s{
	int x;
	int y;
	int max_health;
	int health;
} player;

int move_player(pixel **screen, player *prota, char input, int width, int height, play_screen play_area);