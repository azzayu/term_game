#include "save_file.h"
#include "save_file_cst.h"
#include "structs.h"
#include "player.h"
#include "display_cst.h"
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

void check_with_player(game_state game)
{
    printf("loaded a save file with %i enemies defeated \n", game.enemies_defeated);
    printf("and with a protagonist with %i/%i health and %i/%i stamina \n", game.prota->health, game.prota->max_health, game.prota->stamina, game.prota->max_stamina);
    printf("that is level : %i and has %i exp \n", game.prota->level, game.prota->exp);

    printf("does that seem correct to you? enter y for YES or n for NO \n");

    char input = getchar();

    while (input != 'y')
    {
        if (input == 'n')
        {
            fprintf(stderr, "incorrect save file \n");
            exit(EXIT_FAILURE);
        }
        if (input == '\n')
        {
            input = getchar();
            continue;
        }
        printf("enter y for YES or n for NO \n");
        input = getchar();
    }
}

void tutorial()
{

    printf("it seems this play file is new do you wish to go through a tutorial? \n");
    printf("enter y for YES or n for NO \n");

    char input = getchar();

    while (input != 'y')
    {
        if (input == 'n')
        {
            return;
        }
        if (input == '\n')
        {
            input = getchar();
            continue;
        }
        printf("enter y for YES or n for NO \n");
        input = getchar();
    }

    input = getchar();

    printf("starting tutorial \n");

    printf("You will notice the screen is split in 2 halves, the top half is the heads up display where helpful information is available to you, \n");
    printf("the bottom half is the play area. The heads up display contains the enemy type on the top left, \n");
    printf("your current exp progress to the next level, your health bar and stamina bar, \n");
    printf("and finally the enemy health, location, and which area you are targetting. the enemy is displayed by the small double rectangle asciii art, \n");
    printf("while where you are aiming is indicated by the colour of the frame (you're aiming at the yellow frame), \n");
    printf("to attack the enemy aim at it using 'a' or 'e' to align the yellow frame with the enemy location then attack with 'r'. \n");

    printf("press ENTER to continue \n");

    input = getchar();

    while (input != '\n')
    {
        input = getchar();
    }

    printf("for the bottom part of the screen you are the yellow square \n");

    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, YELLOW, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);

    printf("%spressing 'z' then ENTER will make you go up \n", WHITE);

    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, YELLOW, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);

    printf("%s'd'\n", WHITE);

    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, YELLOW, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);

    printf("%s's'\n", WHITE);

    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, YELLOW, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);

    printf("%s'q'\n", WHITE);

    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, YELLOW, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);
    printf("%s%s%s%s%s%s\n", BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK);

    printf("%spress ENTER to continue\n", WHITE);

    input = getchar();

    while (input != '\n')
    {
        input = getchar();
    }

    printf("you have to use these controls in order to dodge attacks \n");
    printf("printf attacks are shown using : \n");
    printf("%s%s%s for an iminent attack this means staying on this tile will hurt you \n", RED, FULL_BLOCK, WHITE);
    printf("%s%s%s for an attack in 1 turn\n", RED, THREE_QUART_BLOCK, WHITE);
    printf("%s%s%s for an attack in 2 turn \n", RED, HALF_BLOCK, WHITE);
    printf("%s%s%s for an attack in 3 turn \n", RED, QUART_BLOCK, WHITE);

    printf("%spress ENTER to continue\n", WHITE);

    input = getchar();

    while (input != '\n')
    {
        input = getchar();
    }

    printf("finally you can use 'c' to heal (careful this costs 10 stamina and passes 3 turns)\n");
    printf("and if you find yourself in a tough position you can input 'f' to charge a dash then dash in which ever direction\n");

    printf("%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK);
    printf("%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK);
    printf("%s%s%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, YELLOW, FULL_BLOCK, RED, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK);
    printf("%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK);
    printf("%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK);

    printf("%s'fd'\n", WHITE);

    printf("%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK);
    printf("%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK);
    printf("%s%s%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, YELLOW, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK);
    printf("%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK);
    printf("%s%s%s%s%s%s%s%s%s%s\n", RED, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK, BRIGHT_BLUE, FULL_BLOCK, FULL_BLOCK, FULL_BLOCK);

    printf("%spress ENTER to continue\n", WHITE);

    input = getchar();

    while (input != '\n')
    {
        input = getchar();
    }

    printf("That is all you need to know to start playing\n ");
    printf("I suggest studying carefully each enemies different attack patterns and move chances in order to better eliminate them.\n");
    printf("That and to have tons of fun!\n");

    printf("%spress ENTER to finish this tutorial\n", WHITE);

    input = getchar();

    while (input != '\n')
    {
        input = getchar();
    }
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
        tutorial();
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

    if (game.prota->health > game.prota->max_health)
    {
        game.prota->health = game.prota->max_health;
    }

    if (game.prota->stamina > game.prota->max_stamina)
    {
        game.prota->stamina = game.prota->max_stamina;
    }

    if (game.prota->exp > game.prota->exp_to_next_level)
    {
        game.prota->exp = game.prota->exp_to_next_level;
    }

    if (game.enemies_defeated == 0)
    {
        tutorial();
    }

    check_with_player(game);

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
