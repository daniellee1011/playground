#include <stdbool.h>
#include <stdint.h>

#define DEBOUNCE_DELAY_MS 50

bool is_button_pressed(uint8_t current_state, uint8_t *last_state, uint32_t *last_time, uint32_t current_time) {
    if (*last_state != current_state && current_time - *last_time > DEBOUNCE_DELAY_MS) {
        *last_state = current_state;
        *last_time = current_time;
        return current_state == 1; // Button is pressed
    }

    return false; // No valid button press detected
}