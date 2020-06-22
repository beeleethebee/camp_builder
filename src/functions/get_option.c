#include "../../h_files/header.h"


long get_option(int argc, char *argv[]) {
    char *endptr, *str;
    long val;
    errno = 0;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s int.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    str = argv[1];
    val = strtol(str, &endptr, 10);

    if (errno != 0 || endptr == str) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }
    if (val <= 0) {
        fprintf(stderr, "You can't get a camp with a negative or null size.\n");
        exit(EXIT_FAILURE);
    }
    return (val);
}