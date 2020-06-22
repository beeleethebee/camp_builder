#include "../h_files/header.h"
#include <stdio.h>
#include <stdlib.h>


t_building builds[] = {
    {"foundation", 'x', 120, 10, 10, 1},
    {"wall", 'w', 50, 0, 5, 1},
    {"roof", '-', 100, 0, 10, 1},
    {"gold_mine", 'g', 100, 20, 0, 1},
    {"statue", 's', 200, 0, 20, 1},
    {"stone_wall", 'W', 100, 0, 10, 1},
    {0,0,0,0,0,0}
};

t_action actions[] = {
    {"x", &x_operation},
    {"->", &arrow_operation},
    {",", &coma_operation},
    {"\0", &basic_operation},
    {0, 0}
};

int read_instruction(char *input, t_building build, t_x **camp ,t_game_info *game_info) {
    char testing[33];
    if(input[0] != ':') {
        sprintf(game_info->error, "Missing ':' after build name.");
        return -1;
    }
    input++;
    int abs = validator_extract_num(input, game_info);
    if (abs == -1)
        return -1;
    sprintf(testing, "%d", abs);
    input += strlen(testing);
    t_params_operator params = {input, abs, build, game_info, camp};
    for (int i = 0; actions[i].operator != 0 ; i++) {
        if(!strncmp(actions[i].operator, input, strlen(actions[i].operator)))
            return (*actions[i].fct)(params);
    }
    sprintf(game_info->error, "No number or your number is NaN");
    return -1;
}

int detect_building(char *input, t_x **my_camp, t_game_info *game_info) {
    short int isBuilding = 0;
    
    for (int i = 0; builds[i].name != 0; i++) {
        int building_size = strlen(builds[i].name);
        if (strncmp(input, builds[i].name, building_size ) == 0)
            return read_instruction(input +  building_size, builds[i], my_camp, game_info);
    }
    return isBuilding;
}

int main(int argc, char *argv[])  {
    t_game_info game_info = {0, 0, malloc(100), malloc(100)};
    game_info.size_x = get_option(argc, argv);
    t_x *my_camp[game_info.size_x];

    init(my_camp, game_info.size_x);
    printf("Your camp is create successfull, with a size of %d.\n\n", game_info.size_x );
    for (int timer = 1; timer < 100; timer++)  {
        char input[200];
        printf("(%i/100)Enter a command : ", timer);
        fgets(input, 200, stdin);
        format_input(input);
        tokenize_input(input, &game_info, my_camp);
        printf("%s", draw_map(my_camp, &game_info));
    }
}