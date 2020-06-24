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


void draw_screen(t_x **my_camp, t_game_info *game_info) {
    char *none_string = malloc(sizeof(char) * game_info->size_x + 2);
    none_string[0] = '*';
    for (int i = 1; i < game_info->size_x + 1; i++)
        none_string[i] = '=';
    none_string[game_info->size_x + 1] = '*';
    printf("%s\n%s\n%s\n", none_string ,draw_map(my_camp, game_info), none_string);    
}

void init_draw_screen(t_x **my_camp, t_game_info *game_info) {
    clear();
    printf("Hey, here's your new camp, take a moment to watch it !\n\n");
    draw_screen(my_camp, game_info);
    getchar();
    printf("Okay, for now it's quit empty, you can fill it with some constructions in the list:\n");
    for (int i = 0; builds[i].name != 0; i++)
        printf("\t- %s (%c)\n", builds[i].name, builds[i].draw);
    printf("\nYou can find those constructions in README.md. Are you ready to start to fill your camp ? ");
    getchar();
    clear();
}

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
    init_draw_screen(my_camp, &game_info);
    for (int timer = 1; timer < 1000; timer++) {
        draw_screen(my_camp, &game_info);
        char input[200];
        printf("\n(%i) Tell us your instruction(s) according to the guide : ", timer);
        fgets(input, 200, stdin);
        format_input(input);
        printf("\n_____________\n\n");
        tokenize_input(input, &game_info, my_camp);
        printf("\n");
    }
}