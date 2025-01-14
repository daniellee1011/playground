#include <stdio.h>

char to_upper(char ch);
char to_lower(char ch);

int main() {
    char alpha = 'a';

    printf("before: %c\n", alpha);
    alpha = to_upper(alpha);
    printf("after: %c\n\n", alpha);

    printf("before: %c\n", alpha);
    alpha = to_lower(alpha);
    printf("after: %c\n", alpha);

    return 0;
}

char to_upper(char ch) {
    return ch & '_';
}

char to_lower(char ch) {
    return ch | ' ';
}