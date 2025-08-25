#ifndef HAL_GPIO_H
#define HAL_GPIO_H
#include <stdint.h>
#include <stdbool.h>

// GPIO HAL for ESP32 IoT Server System
void hal_gpio_init();
void hal_gpio_set(uint8_t pin, bool value);
bool hal_gpio_get(uint8_t pin);

#endif // HAL_GPIO_H
