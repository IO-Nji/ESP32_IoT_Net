#include "hal_bms280.h"
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void hal_bms280_init() {
    bme.begin(0x68);
}

bool hal_bms280_read(float* temperature, float* humidity, float* pressure) {
    if (!bme.begin(0x68)) return false;
    *temperature = bme.readTemperature();
    *humidity = bme.readHumidity();
    *pressure = bme.readPressure();
    return true;
}
