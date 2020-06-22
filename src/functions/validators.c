#include "../../h_files/header.h"


int validator_num(int value, char *input, t_game_info *game_info) {
    if (value == 0 && input[0] != '0') {
        sprintf(game_info->error,"No times number or your it's NaN");
        return -1;
    } else if (value < 0) {
        sprintf(game_info->error,"The number of times is under 0");
        return -1;
    }
    return 0;
}

int validator_extract_num(char *input, t_game_info *game_info) {
    char *first_num = extract_num(input);
    int abs = strtol(first_num, NULL, 10);
    int validator = validator_num(abs, input, game_info);
    input += strlen(first_num);

    return validator == 0 ? abs : -1;
}