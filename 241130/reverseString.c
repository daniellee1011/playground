#include <stdio.h>
#include <string.h>

void reverse(char* str, int start, int end) {
    if (!str) return;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void rearrangeString(char* str) {
    int len = strlen(str);
    reverse(str, 0, len - 1);
    
    int start = 0;
    for (int i = 0; i <= len; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            reverse(str, start, i - 1);
            start = i + 1;
        }
    }
}

int main() {
    char myString[] = "abc   ef  12 g"; // should use [] instead *
    printf("%s\n", myString);
    rearrangeString(myString);
    printf("%s", myString);
    return 0;
}
