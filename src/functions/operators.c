#include "../../h_files/header.h"


int basic_operation(t_params_operator params) {
    t_game_info *game_info = params.game_info;
    int abs = params.abs;
    t_x **camp = params.camp;
    t_building build = params.build;

    if (params.input[0] != '\0') {
        sprintf(game_info->error, "Unknown operator \"%s\"", params.input);
        return -1;
    }

    if (abs >= game_info->size_x) {
        sprintf(game_info->error, "It's impossible to build over %i", game_info->size_x - 1);
        return -1;
    }
    push_back(camp[abs], build);
    sprintf(game_info->message, "a \"%s\" was successful built at (%i,%i).",
        build.name, abs, get_max_y(camp[abs]) - 1);
    return 1;
}

int x_operation(t_params_operator params) {
    t_game_info *game_info = params.game_info;
    int abs = params.abs;
    t_x **camp = params.camp;
    t_building build = params.build;
    char *input = params.input;

    int times = strtol(++input,NULL,10);
    if (validator_num(times, input, game_info) == -1) {
        return -1;
    }
    for (int i = 0; i < times; i++)
        push_back(camp[abs], build);
    sprintf(game_info->message, "Exactly %i \"%ss\" were builts", times, build.name);
    return 1;
}

int coma_operation(t_params_operator params) {    
    t_x **camp = params.camp;
    char *input = params.input;
    int counter = 1;
    int index = 0;

    push_back(camp[params.abs], params.build);
    while (input[index] && input[index] == ',') {
        input++;
        int actual_num = validator_extract_num(input, params.game_info);
        if (actual_num == -1)
            continue;
        char testing[33];
        sprintf(testing, "%d" ,actual_num);
        input += strlen(testing);
        if (actual_num >= params.game_info->size_x)
            continue;
        push_back(camp[actual_num], params.build);
        counter++;
    }
    sprintf(params.game_info->message, "Exactly %i \"%ss\" were built", counter, params.build.name);
    return 1;
}

int arrow_operation(t_params_operator params) {
    t_game_info *game_info = params.game_info;
    int abs = params.abs;
    t_building build = params.build;
    char *input = params.input;
    input += 2;
    int going_to = strtol(input, NULL, 10);
    if (validator_num(going_to, input, game_info) == -1)
        return -1;
    if (going_to < abs) {
        int tmp = abs;
        abs = going_to;
        going_to = tmp;
    }
    int sucess = abs;
    for (; sucess <= going_to; sucess++) {
        if (sucess >= game_info->size_x)
            break;
        push_back(params.camp[sucess], build);
    }
    sprintf(game_info->message, "Exactly %i \"%ss\" were builts", sucess-abs, build.name);
    return 1;
}