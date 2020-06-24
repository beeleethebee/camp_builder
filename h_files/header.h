#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <printf.h>

typedef struct s_game_info
{
    int size_x;
    int max_y;
    char *error;
    char *message;
} t_game_info;

typedef struct s_building
{
    char *name;
    char draw;
    int  price;
    int production;
    int prestige;
    int level;
}   t_building;

typedef struct s_y
{
    long northing_value;
    t_building building;
    struct s_y *prev;
    struct s_y *next;
}   t_y;

typedef struct s_x
{
    long easting_value;
    t_y *first;
    t_y *last;
}   t_x;

typedef struct s_params_operator
{
    char *input;
    int abs;
    t_building build;
    t_game_info *game_info;
    t_x **camp;
}   t_params_operator;

typedef struct s_action
{
    char *operator;
    int (*fct)(t_params_operator params);
}   t_action;

long get_option(int argc, char *argv[]);
void delete_spaces(char *to_purge);
void clear();
void draw_screen(t_x **my_camp, t_game_info *game_info);
void init_draw_screen(t_x **my_camp, t_game_info *game_info);
void tokenize_input(char *input, t_game_info *game_info, t_x **my_camp);
int detect_building(char *input, t_x **my_camp, t_game_info *game_info);

int basic_operation(t_params_operator params);
int x_operation(t_params_operator params);
int coma_operation(t_params_operator params);
int arrow_operation(t_params_operator params);

int validator_num(int value, char *input, t_game_info *game_info);
int validator_extract_num(char *input, t_game_info *game_info);
char *extract_num(char *input);
void format_input( char *input);

void init(t_x **tab, int size);
int push_back(t_x *l, t_building building);
int get_max_y(t_x *l);
t_building *get_building(t_x *l, int y);
int get_max_y_list(t_x **l, t_game_info *info);
char *draw_map(t_x **map, t_game_info *game_info);

#endif