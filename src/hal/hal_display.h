#ifndef HAL_DISPLAY_H
#define HAL_DISPLAY_H
#include <stdint.h>

// Display HAL for ESP32 IoT Server System
typedef enum {
    DISPLAY_1 = 0,
    DISPLAY_2,
    DISPLAY_COUNT
} DisplayType;

void hal_display_init();
void hal_display_clear(DisplayType display);
void hal_display_print(DisplayType display, const char* msg, uint8_t line);

#endif // HAL_DISPLAY_H
