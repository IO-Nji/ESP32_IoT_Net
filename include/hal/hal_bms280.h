#pragma once

// BMS280 Sensor HAL for ESP32 IoT Server System
void hal_bms280_init();
bool hal_bms280_read(float* temperature, float* humidity, float* pressure);
