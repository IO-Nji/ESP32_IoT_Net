#ifndef HAL_BME280_H
#define HAL_BME280_H
#include <stdint.h>

// BME280 Sensor HAL for ESP32 IoT Server System
void hal_bme280_init();
bool hal_bme280_read(float* temperature, float* humidity, float* pressure);

#endif // HAL_BME280_H
