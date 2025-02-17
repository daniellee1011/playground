#include <stdio.h>
#include <string.h>

// abc ef 12 g -> g 12 ef abc

void helper(char *str, int l, int r) {
    while (l < r) {
        char temp = str[l];
        str[l] = str[r];
        str[r] = temp;
        l++;
        r--;
    }
}

char* reverseString(char *str) {
    int len = strlen(str);

    printf("original: %s\n", str);
    helper(str, 0, len - 1);
    printf("mid str: %s\n", str);

    int l = 0;
    int r = l;
    while (r <= len) {
        if (str[r] == ' ' || str[r] == '\0') {
            helper(str, l, r - 1);
            l = r + 1;
        }
        r++;
    }

    printf("reverseString: %s\n", str);

    return str;
}

int main() {
    char str[] = "abc ef 12 g";
    char* reversed = reverseString(str);
    printf("main reversed: %s\n", reversed);

    return 0;
}
