#include <stdio.h>
#include <limits.h>

int myAtoiChar(char c) {
    if (c < '0' || c > '9') {
        printf("Invalid input: %c\n", c);
        return -1;
    }
    return c - '0';
}

int myAtoi(const char *str) {
    int result = 0, sign = 1, i = 0;

    while (str[i] == ' ') i++;
    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i++] == '+') ? 1 : -1;
    }

    while ('0' <= str[i] && str[i] <= '9') {
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && str[i] - '0' > 7)) {
            return (sign == 1) ? INT_MAX : INT_MIN; // Handle overflow
        }
        result = result * 10 + (str[i++] - '0');
    }

    return result * sign;
}

int main() {
    printf("%d\n", myAtoiChar('c'));
    printf("%d\n", myAtoiChar('5'));
    printf("%d\n", myAtoi("   -12345"));
    printf("%d\n", myAtoi("4193 with text"));
    printf("%d\n", myAtoi("2147483648"));
    return 0;
}
