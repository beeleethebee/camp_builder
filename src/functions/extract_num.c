#include "../../h_files/header.h"
#include <ctype.h>

char *extract_num(char *input) {
    char *buf = malloc(sizeof(char) * strlen(input)+ 1);
    int index_buf = 0;

    for (int i = 0; input[i] && isdigit(input[i]); i++) {
        buf[index_buf++] = input[i];
    }
    buf[++index_buf] = '\0';
    return buf;
}