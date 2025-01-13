#include <stdio.h>

#define WINDOW_SIZE 3

int calculate_moving_average(int new_value) {
    static int values[WINDOW_SIZE] = {0};
    static int index = 0;
    static int count = 0;

    values[index] = new_value;
    index = (index + 1) % WINDOW_SIZE;
    count++;

    int sum = 0;
    int effective_count = count < WINDOW_SIZE ? count : WINDOW_SIZE;
    for (int i = 0; i < effective_count; i++) {
        sum += values[i];
    }

    return sum / effective_count;
}