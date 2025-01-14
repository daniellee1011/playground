#include <stdio.h>

int string_to_int(char *str) {
    int result = 0, sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str) {
        if (*str < '0' || *str > '9') return 0;
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}