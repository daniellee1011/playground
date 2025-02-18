#include <stdio.h>

void display_bits(unsigned int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num & (1 << i)) ? 1 : 0);
        if (i % 4 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    unsigned int num = 29;
    printf("Original: ");
    display_bits(num);

    // Set bit at position 5
    num |= (1 << 5);
    printf("After setting bit 5: ");
    display_bits(num);

    // Clear bit at position 3
    num &= ~(1 << 3);
    printf("After clearing bit 3: ");
    display_bits(num);

    // Toggle bit at position 2
    num ^= (1 << 2);
    printf("After toggling bit 2: ");
    display_bits(num);

    printf("Bit at position 4 is : %s\n", (num & (1 << 4)) ? "SET" : "NOT SET");

    return 0;
}
