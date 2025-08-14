#include "save_file.h"
#include "save_file_cst.h"
#include "structs.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

int size_string(char *string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        i++;
    }
    return i;
}

player initialise_new_player(screen_section play_area)
{
    int middle_play_area_x = (play_area.x_max - play_area.x_min) / 2 + play_area.x_min;
    int middle_play_area_y = (play_area.y_max - play_area.y_min) / 2 + play_area.y_min;
    int max_health = 20;
    int max_stamina = 100;

    player prota = init_player(middle_play_area_x, middle_play_area_y, max_health, max_stamina);

    return prota;
}

game_state load_from_file(char *save_file_name)
{
    game_state game;

    game.save_file_name = save_file_name;

    FILE *save_file = fopen(save_file_name, "r");

    game.enemies_defeated = 0;

    player *prota = malloc(sizeof(player));

    int width = 30;
    int height = 40;
    screen_section play_area = init_screen_section(1, height / 2, width - 1, height - 1);

    *prota = initialise_new_player(play_area);
    game.prota = prota;

    if (save_file == NULL)
    {
        printf("save file not found creating new save file \n");
        return game;
    }

    int index;
    int value;

    fscanf(save_file, "%i %i", &index, &value);
    while (!feof(save_file))
    {
        switch (index)
        {
        case SAVE_INDEX_ENEMIES_DEAD:
            game.enemies_defeated = value;
            break;
        case SAVE_INDEX_PLAYER_X:
            game.prota->x = value;
            break;
        case SAVE_INDEX_PLAYER_Y:
            game.prota->y = value;
            break;
        case SAVE_INDEX_PLAYER_HEALTH:
            game.prota->health = value;
            break;
        case SAVE_INDEX_PLAYER_MAX_HEALTH:
            game.prota->max_health = value;
            break;
        case SAVE_INDEX_PLAYER_STAMINA:
            game.prota->stamina = value;
            break;
        case SAVE_INDEX_PLAYER_MAX_STAMINA:
            game.prota->max_stamina = value;
            break;
        case SAVE_INDEX_PLAYER_EXP:
            game.prota->exp = value;
            break;
        case SAVE_INDEX_PLAYER_EXP_NEXT_LEVEL:
            game.prota->exp_to_next_level = value;
            break;
        case SAVE_INDEX_PLAYER_LEVEL:
            game.prota->level = value;
            break;
        case SAVE_INDEX_PLAYER_CHARGED:
            game.prota->charged = value;
            break;
        case SAVE_INDEX_PLAYER_AIM:
            game.prota->aiming = value;
            break;
        case SAVE_INDEX_PLAYER_ATTACK:
            game.prota->attack = value;
            break;
        }
        fscanf(save_file, "%i %i", &index, &value);
    }

    fclose(save_file);

    printf("loaded a save file with %i enemies defeated \n", game.enemies_defeated);
    printf("and with a protagonist with %i/%i health and %i/%i stamina \n", game.prota->health, game.prota->max_health, game.prota->stamina, game.prota->max_stamina);
    printf("that is level : %i and has %i exp \n", game.prota->level, game.prota->exp);

    return game;
}

void save_to_file(game_state game)
{
    FILE *save_file = fopen(game.save_file_name, "w");

    fprintf(save_file, "%i %i \n", SAVE_INDEX_ENEMIES_DEAD, game.enemies_defeated);

    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_X, game.prota->x);
    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_Y, game.prota->y);

    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_HEALTH, game.prota->health);
    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_MAX_HEALTH, game.prota->max_health);

    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_STAMINA, game.prota->stamina);
    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_MAX_STAMINA, game.prota->max_stamina);

    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_EXP, game.prota->exp);
    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_EXP_NEXT_LEVEL, game.prota->exp_to_next_level);
    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_LEVEL, game.prota->level);

    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_CHARGED, game.prota->charged);
    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_AIM, game.prota->aiming);

    fprintf(save_file, "%i %i \n", SAVE_INDEX_PLAYER_ATTACK, game.prota->attack);

    fclose(save_file);
}
