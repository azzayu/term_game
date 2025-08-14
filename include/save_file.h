#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <stdio.h>
#include "structs.h"

game_state load_from_file(char *save_file_name);

void save_to_file(game_state game);

int size_string(char *string);

#endif
