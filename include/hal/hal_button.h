#pragma once
#include <stdint.h>

// Button HAL Interface

typedef enum {
    BUTTON_SELECT = 0,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_BACK,
    BUTTON_COUNT
} ButtonType;

void hal_button_init();
bool hal_button_is_pressed(ButtonType button);
void hal_button_update(); // For debouncing and event generation
