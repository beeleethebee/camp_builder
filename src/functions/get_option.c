#include "../../h_files/header.h"


long get_option(int argc, char *argv[]) {
    char *endptr, *str;
    long val;
    errno = 0;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s int, we gonna take 10, by default value.\n", argv[0]);
        return(10);
    }
    str = argv[1];
    val = strtol(str, &endptr, 10);

    if (errno != 0 || endptr == str) {
        perror("strtol");
        return(10);
    }
    return (val);
}