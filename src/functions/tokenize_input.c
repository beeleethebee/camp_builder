#include "../../h_files/header.h"


void tokenize_input(char *input, t_game_info *game_info, t_x **my_camp) {
    char *token = strtok(input, ";");

    while (token != NULL) {
        int code = detect_building(token, my_camp, game_info);
        switch (code) {
        case -1:
            printf("\"%s\"\t-> %s\n", token, game_info->error);
            break;
        case 0:
            printf("\"%s\"\t-> Not a known building\n", token);
            break;
        case 1:
            printf("\"%s\"\t-> %s\n", token, game_info->message);
            break;
        }
        token = strtok (NULL, ";");
    }
}