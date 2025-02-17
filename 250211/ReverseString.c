#include <stdio.h>
#include <string.h>

char* reverseString(char *str) {
    int len = strlen(str);
    printf("%s, length: %d\n", str, len);

    char* reversed;
    int l = 0;
    int r = len - 1;

    while (l < r) {
        char temp = str[l];
        str[l] = str[r];
        str[r] = temp;
        l++;
        r--;
    }

    printf("reversed: %s\n", str);

    return str;
}

int main() {
    // char* str = "abc ef 12 g"; // X String literal (read-only)
    char str[12] = "abc ef 12 g";
    char* reversed = reverseString(str);
    printf("main reversed: %s\n", reversed);

    return 0;
}
