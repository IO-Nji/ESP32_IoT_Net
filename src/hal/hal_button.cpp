
#include "src/hal/hal_button.h"
#include <Arduino.h>

const int BUTTON_PINS[4] = {10, 20, 21, 0};
const char* BUTTON_NAMES[4] = {"GR", "RL", "RR", "YW"};

void hal_button_init() {
    for (int i = 0; i < 4; ++i) {
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    }
}

bool hal_button_is_pressed(ButtonType button) {
    if (button < 0 || button > 3) return false;
    return digitalRead(BUTTON_PINS[(int)button]) == LOW;
}

void hal_button_update() {
    // Implement debouncing or state tracking if needed
}

const char* hal_button_get_name(ButtonType button) {
    if (button < 0 || button > 3) return "";
    return BUTTON_NAMES[(int)button];
}
