#include "../../h_files/header.h"


void init(t_x **tab, int size)  {
    for (int i = 0; i < size; i++) {
        t_x *elem = malloc(sizeof(t_x)); 
        if (elem == NULL)
            exit(EXIT_FAILURE);
        elem->easting_value = (long) i;
        elem->last = NULL;
        elem->first = NULL;
        tab[i] = elem;
    }
}

int push_back(t_x *l, t_building building) {
   t_y *nouv = malloc(sizeof(t_y));
   if(!nouv) exit(EXIT_FAILURE);
   nouv->prev = l->last;
   nouv->building = building;
   nouv->next = NULL;
   if(l->last)  {
       l->last->next = nouv;
       nouv->northing_value = l->last->northing_value + 1;
   }
   else {
       l->first = nouv;
       nouv->northing_value = 0;
   }
   l->last = nouv; 
   return nouv->northing_value;
}

int view(t_x *l)
{
    t_y *ptr = l->first;
    int counter = 0;
    while (ptr != NULL) {
        int x = l->easting_value;
        int y = ptr->northing_value;
        char *building_name = ptr->building.name;
        counter++;
        printf("Building at (%i,%i) is %s \n", x, y, building_name);
        ptr = ptr->next;
    }
    return counter;
}

int view_list(t_x **l, t_game_info *info) {
    int index = 0;
    int counter = 0;
    while (index < info->size_x)
        counter += view(l[index++]);
    return counter;
}

int count_items(t_x *l, char *to_search) {
    t_y *ptr = l->first;
    int counter = 0;
    while (ptr != NULL) {
        if (to_search == NULL || strcmp(ptr->building.name, to_search) == 0)
            counter++;
        ptr = ptr->next;
    } 
    return counter;
}

int count_items_list(t_x **l, char *to_search, t_game_info *info)  {
    int index = 0;
    int counter = 0;
    while (index < info->size_x) {
        printf("index = %i\n", index);
        counter += count_items(l[index++], to_search);
    }
    return counter;
}

int pop_back(t_x *l) {
   t_y *tmp = l->last;
   if(!tmp) return -1;
   l->last = tmp->prev;
   if(l->last) l->last->next = NULL;
   free(tmp);
   return 0;
}

int get_max_y(t_x *l) {
    t_y *ptr = l->first;
    int counter = 0;
    while (ptr != NULL) {
        counter++;
        ptr = ptr->next;
    } 
    return counter;
}

int get_max_y_list(t_x **l, t_game_info *info) {
    int index = 0;
    int max = 0;
    while (index < info->size_x) {
        int y = get_max_y(l[index++]);
        if (y > max)
            max = y;
    }
    info->max_y = max;
    return max;
}

t_building *get_building(t_x *l, int y)  {
    t_y *ptr = l->first;
    while (ptr != NULL) {
        if (ptr->northing_value == y)
            return &ptr->building;
        ptr = ptr->next;
    } 
    return  NULL;
}

char *draw_map(t_x **map, t_game_info *game_info) {
    int max_y = get_max_y_list(map, game_info) - 1;
    if (max_y == -1) {
        char *none_string = malloc(sizeof(char) * game_info->size_x + 1);
        for (int i = 0; i < game_info->size_x ; i++)
            none_string[i] = '.';
        none_string[game_info->size_x-1] = '\n';
        return none_string;
    }
    char *string = malloc(sizeof(char*) * max_y * (game_info->size_x + 1));
    while (max_y >= 0) {
        int index = 0;
        while (index < game_info->size_x) {
            t_building *area = get_building(map[index++], max_y);
            if (area != NULL)
                strncat(string,&area->draw,1);
            else
                strncat(string,".",1);
        }
        max_y--;
        strncat(string,"\n",1);
    }
    return string;
}