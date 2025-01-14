#include <stdio.h>
#include <stdbool.h>

typedef enum {
    STATE_IDLE,
    STATE_PRESSED,
    STATE_RELEASED
} ButtonState;

ButtonState handle_button_irq(bool is_pressed);

int main() {
    handle_button_irq(false);
    handle_button_irq(true);
    handle_button_irq(true);
    handle_button_irq(false);
    handle_button_irq(false);
}

ButtonState handle_button_irq(bool is_pressed) {
    static ButtonState current_state = STATE_IDLE;

    printf("Current State: %d, Button Input: %s\n", current_state, is_pressed ? "Pressed" : "Not Pressed");

    switch (current_state) {
        case STATE_IDLE:
            if (is_pressed) {
                current_state = STATE_PRESSED;
                printf("Transition to STATE_PRESSED\n");
            }
            break;
        case STATE_PRESSED:
            if (!is_pressed) {
                current_state = STATE_RELEASED;
                printf("Transition to STATE_RELEASED\n");
            }
            break;
        case STATE_RELEASED:
            if (!is_pressed) {
                current_state = STATE_IDLE;
                printf("Transition to STATE_IDLE\n");
            }
            break;
        default:
            current_state = STATE_IDLE;
            printf("Unexpected state. Reset to STATE_IDLE\n");
            break;
    }

    return current_state;
}