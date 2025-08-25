#ifndef HAL_I2C_H
#define HAL_I2C_H
#include <stdint.h>
#include <stddef.h>

// I2C HAL for ESP32 IoT Server System
void hal_i2c_init();
bool hal_i2c_read(uint8_t addr, uint8_t *data, size_t len);
bool hal_i2c_write(uint8_t addr, const uint8_t *data, size_t len);

#endif // HAL_I2C_H
