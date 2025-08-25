#ifndef HAL_BMS280_H
#define HAL_BMS280_H
#include <stdint.h>

// BMS280 Sensor HAL for ESP32 IoT Server System
void hal_bms280_init();
bool hal_bms280_read(float* temperature, float* humidity, float* pressure);

#endif // HAL_BMS280_H
