#include "../../h_files/header.h"


void format_input( char *input) {
    int index = strlen(input);

    if (input[index-1] == '\n')
        input[index-1] = '\0';
    delete_spaces(input);
}