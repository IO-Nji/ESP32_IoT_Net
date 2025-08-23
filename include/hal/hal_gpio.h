#pragma once

// GPIO HAL for ESP32 IoT Server System
void hal_gpio_init();
void hal_gpio_set(uint8_t pin, bool value);
bool hal_gpio_get(uint8_t pin);
