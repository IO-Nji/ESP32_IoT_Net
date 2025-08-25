#ifndef HAL_DIPSWITCH_H
#define HAL_DIPSWITCH_H
#include <stdint.h>

#define DIPSWITCH_COUNT 6

void hal_dipswitch_init();
void hal_dipswitch_read_states(bool states[DIPSWITCH_COUNT]);

#endif // HAL_DIPSWITCH_H
