#include "src/hal/hal_dipswitch.h"
#include <Arduino.h>

static const int DIPSWITCH_PINS[DIPSWITCH_COUNT] = {1, 2, 3, 4, 5, 6};

void hal_dipswitch_init() {
    for (int i = 0; i < DIPSWITCH_COUNT; ++i) {
        pinMode(DIPSWITCH_PINS[i], INPUT_PULLUP);
    }
}

void hal_dipswitch_read_states(bool states[DIPSWITCH_COUNT]) {
    for (int i = 0; i < DIPSWITCH_COUNT; ++i) {
        states[i] = (digitalRead(DIPSWITCH_PINS[i]) == LOW); // true if switch is down
    }
}
