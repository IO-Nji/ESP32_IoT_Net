#include "src/hal/hal_gpio.h"
#include <Arduino.h>

void hal_gpio_init() {
    // Initialize GPIO pins for buttons and switches
}

void hal_gpio_set(uint8_t pin, bool value) {
    digitalWrite(pin, value);
}

bool hal_gpio_get(uint8_t pin) {
    return digitalRead(pin);
}
