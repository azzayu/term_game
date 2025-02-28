

typedef struct player_s{
	int x;
	int y;
	int max_health;
	int health;
} player;

int move_player(pixel **screen, player *prota, char input, int width, int height, screen_section play_area);

void update_health_bar(pixel **screen, player prota, screen_section health_bar);