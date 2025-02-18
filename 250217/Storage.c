#include <stdio.h>

struct {
    unsigned int is_enabled : 1;
    unsigned int speed : 3; // 0-7
    unsigned int direction : 2; // 0-3
} motor;

int main() {
    motor.is_enabled = 1;
    motor.speed = 5;
    motor.direction = 2;

    printf("Motor Enabled: %d, Speed: %d, Direction: %d\n", motor.is_enabled, motor.speed, motor.direction);
    printf("Size of motor struct: %lu bytes\n", sizeof(motor));
    return 0;
}

