#pragma once

// Display HAL for ESP32 IoT Server System
void hal_display_init();
void hal_display_clear();
void hal_display_print(const char* msg, uint8_t line = 0);
