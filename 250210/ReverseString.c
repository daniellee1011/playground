#include <stdio.h>
#include <string.h>

void helper(char *str, int l, int r) {
    while (l < r) {
        char temp = str[l];  // ✅ Fix incorrect pointer usage
        str[l] = str[r];
        str[r] = temp;
        l++;
        r--;
    }
}

char* reverseString(char *str) {
    int len = strlen(str);
    int l = 0, r = len - 1;

    printf("original: %s\n", str);
    helper(str, l, r);  // ✅ Reverse entire string first
    printf("mid str: %s\n", str);

    r = 0;  // ✅ Fix infinite loop by starting at index 0
    while (r <= len) {  // ✅ Loop until the end
        if (str[r] == ' ' || str[r] == '\0') {  // ✅ Reverse each word separately
            helper(str, l, r - 1);
            l = r + 1;  // ✅ Move `l` past the space
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
