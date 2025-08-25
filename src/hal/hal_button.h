#ifndef HAL_BUTTON_H
#define HAL_BUTTON_H
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
void hal_button_update();

#endif // HAL_BUTTON_H
