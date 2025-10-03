#include "dyn_array.h"
#include "display_cst.h"
#include "enemy.h"
#include "save_file.h"
#include "enemy_types.h"
#include "attacks.h"
#include "display.h"
#include "player.h"
#include "structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

screen_section *create_enemy_locations()
{

    screen_section *enemy_locations = malloc(sizeof(screen_section) * 3);

    // initialises the enemy display boxes' location on the screen
    for (int i = 0; i < 3; i++)
    {
        int x_min = 3 + 8 * i;
        int y_min = 9;
        int x_max = 2 + 8 * (i + 1);
        int y_max = 16;
        enemy_locations[i] = init_screen_section(x_min, y_min, x_max, y_max);
    }

    return enemy_locations;
}

text_section **initialise_all_text(pixel **screen, int width)
{
    int health_text_x_min = width - 8;
    int health_text_x_max = width - 1;
    int health_text_y = 1;
    int health_text_length = 6;

    int stamina_text_x_min = width - 8;
    int stamina_text_x_max = width - 1;
    int stamina_text_y = 5;
    int stamina_text_length = 7;

    int enemy_name_x_min = 1;
    int enemy_name_x_max = 10;
    int enemy_name_y = 1;
    int enemy_name_length = 10;

    int exp_text_x_min = width - 16;
    int exp_text_x_max = width - 14;
    int exp_text_y = 1;
    int exp_text_length = 3;

    text_section *health = init_text(health_text_x_min, health_text_x_max, health_text_y, "HEALTH", health_text_length);
    text_section *stamina = init_text(stamina_text_x_min, stamina_text_x_max, stamina_text_y, "STAMINA", stamina_text_length);
    text_section *enemy_name = init_text(enemy_name_x_min, enemy_name_x_max, enemy_name_y, "enemy name", enemy_name_length);
    text_section *exp = init_text(exp_text_x_min, exp_text_x_max, exp_text_y, "EXP", exp_text_length);

    int nb_text_sections = 5;

    text_section **all_text = malloc(sizeof(text_section) * nb_text_sections);

    all_text[1] = health;
    all_text[2] = stamina;
    all_text[3] = enemy_name;
    all_text[4] = exp;

    for (int i = 1; i < nb_text_sections; i++)
	{
		screen[all_text[i]->y][all_text[i]->x_min].colour = i;
		screen[all_text[i]->y][all_text[i]->x_min].pixel_type = PIXEL_START_TEXT;
		for (int j = all_text[i]->x_min + 1; j < all_text[i]->x_max; j++)
		{
			screen[all_text[i]->y][all_text[i]->x_min].colour = VALUE_NONE;
			screen[all_text[i]->y][all_text[i]->x_min].pixel_type = PIXEL_TEXT;
		}
	}

    return all_text;
}

void play_out_attack(pixel **screen, player prota, screen_section play_area, dyn_array *tab)
{

    int turn = 0;
    int width = 30;
    int height = 40;

    prota.health = 99999;
    prota.max_health = 99999;

    text_section **all_text = initialise_all_text(screen, width);

    while (tab->size > 0)
    {

        char input = getchar();
        // scanf("%c",&input);
        int has_moved = 0;

        if (input == '\n')
        {
            has_moved++;
        }

        while (has_moved > 0)
        {
            turn += 1;
            // sort(tab);
            update_attacks(screen, &prota, play_area, tab, turn);
            print_screen(screen, width, height, all_text);
            // printf("turn : %i \n", turn);
            // print_dyn_array(*tab);
            has_moved--;
        }
    }
}

screen_section initialise_health_bar(int width)
{
    int health_bar_x_min = width - 8;
    int health_bar_y_min = 3;
    int health_bar_x_max = width - 1;
    int health_bar_y_max = 4;

    screen_section health_bar = init_screen_section(health_bar_x_min, health_bar_y_min, health_bar_x_max, health_bar_y_max);

    return health_bar;
}

screen_section initialise_stamina_bar(int width)
{
    int stamina_bar_x_min = width - 8;
    int stamina_bar_y_min = 7;
    int stamina_bar_x_max = width - 1;
    int stamina_bar_y_max = 8;

    screen_section stamina_bar = init_screen_section(stamina_bar_x_min, stamina_bar_y_min, stamina_bar_x_max, stamina_bar_y_max);

    return stamina_bar;
}

screen_section initialise_exp_bar(int width)
{
    int exp_bar_x_min = width - 16;
    int exp_bar_y_min = 3;
    int exp_bar_x_max = width - 8;
    int exp_bar_y_max = 4;

    screen_section stamina_bar = init_screen_section(exp_bar_x_min, exp_bar_y_min, exp_bar_x_max, exp_bar_y_max);

    return stamina_bar;
}

screen_section initialise_enemy_health_bar()
{
    int enemy_health_bar_x_min = 3;
    int enemy_health_bar_y_min = 18;
    int enemy_health_bar_x_max = 26;
    int enemy_health_bar_y_max = 19;

    screen_section enemy_health = init_screen_section(enemy_health_bar_x_min, enemy_health_bar_y_min, enemy_health_bar_x_max, enemy_health_bar_y_max);

    return enemy_health;
}

void see_all_attacks(char **argv)
{

    game_state game = load_from_file(argv[1]);

    int width = 30;
    int height = 40;
    int turn = 0;

    srand(time(NULL));

    screen_section *enemy_locations = create_enemy_locations();

    screen_section play_area = init_screen_section(1, height / 2, width - 1, height - 1);

    player *prota;

    prota = game.prota;

    pixel **screen = init_screen(width, height, play_area, enemy_locations);
    screen[prota->y][prota->x].colour = VALUE_YELLOW;
    screen[prota->y][prota->x].pixel_type = PIXEL_FULL_BLOCK;

    screen_section health_bar = initialise_health_bar(width);
    screen_section stamina_bar = initialise_stamina_bar(width);
    screen_section exp_bar = initialise_exp_bar(width);

    update_health_bar(screen, *prota, health_bar);
    update_stamina_bar(screen, *prota, stamina_bar);
    update_exp_bar(screen, *prota, exp_bar);

    text_section **all_text = initialise_all_text(screen, width);

    change_aim(screen, prota, enemy_locations, 0);

    enemy current_enemy = create_enemy(screen, enemy_locations, game.enemies_defeated);

    screen_section enemy_health = initialise_enemy_health_bar();

    update_enemy_health_bar(screen, current_enemy, enemy_health);

    update_enemy_name(all_text[3], current_enemy);

    dyn_array tab = create_empty_dyn_array();

    print_screen(screen, width, height, all_text);

    printf("test slash_attack \n");
    current_enemy = create_enemy_dark_knight(0);
    slash_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test spike_attack \n");
    current_enemy = create_enemy_possessed_tree(0);
    spike_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test meteor_attack \n");
    current_enemy = create_enemy_dark_mage(0);
    meteor_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test bouncy_ball \n");
    current_enemy = create_enemy_dark_mage(0);
    bouncy_ball(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test twinkles_attack \n");
    current_enemy = create_enemy_dark_mage(0);
    twinkles_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test stab_attack \n");
    current_enemy = create_enemy_dark_knight(0);
    stab_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test tail_slap_attack \n");
    current_enemy = create_enemy_dragon(0);
    tail_slap_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test fire_breath_attack \n");
    current_enemy = create_enemy_dragon(0);
    fire_breath_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test small_smash attack \n");
    current_enemy = create_enemy_golem(0);
    small_smash_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test big_smash attack \n");
    current_enemy = create_enemy_golem(0);
    big_smash_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test simple_spiral attack \n");
    current_enemy = create_enemy_sea_serpent(0);
    simple_spiral_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test double_spiral attack \n");
    current_enemy = create_enemy_sea_serpent(0);
    double_spiral_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test wave attack \n");
    current_enemy = create_enemy_sea_serpent(0);
    wave_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test direct_slash attack \n");
    current_enemy = create_enemy_dark_knight(0);
    direct_slash_attack(play_area, current_enemy, &tab, *prota, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test close_in attack \n");
    current_enemy = create_enemy_arch_mage(0);
    close_in_attack(play_area, current_enemy, &tab, *prota, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test crumble attack \n");
    current_enemy = create_enemy_golem(0);
    crumble_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test shatter attack \n");
    current_enemy = create_enemy_arch_mage(0);
    shatter_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test mist attack \n");
    current_enemy = create_enemy_sea_serpent(0);
    mist_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test explosion attack \n");
    current_enemy = create_enemy_arch_mage(0);
    explosion_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test tetris_fall attack \n");
    current_enemy = create_enemy_mystery(0);
    tetris_fall_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test player_circle attack \n");
    current_enemy = create_enemy_arch_mage(0);
    player_circle_attack(play_area, current_enemy, &tab, *prota, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test square_circle attack \n");
    current_enemy = create_enemy_arch_mage(0);
    player_square_attack(play_area, current_enemy, &tab, *prota, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);

    printf("test snake attack \n");
    current_enemy = create_enemy_shaman(0);
    snake_attack(play_area, current_enemy, &tab, turn);
    sort(&tab);
    play_out_attack(screen, *prota, play_area, &tab);
}

int main(int argc, char **argv)
{

    if (argc == 2)
    {
        see_all_attacks(argv);
        return EXIT_SUCCESS;
    }

    dyn_array tab = create_empty_dyn_array();
    print_dyn_array(tab);
    for (int i = 0; i < 21; i++)
    {
        attack data;
        data.x = 0;
        data.y = 0;
        data.damage = 0;
        data.turn = (i * 21) % 4;
        append(&tab, data);
        print_dyn_array(tab);
    }

    sort(&tab);
    print_dyn_array(tab);

    for (int i = 0; i < 21; i++)
    {
        pop(&tab);
        print_dyn_array(tab);
    }

    free_dyn_array(tab);

    default_test_screen();

    return EXIT_SUCCESS;
}
