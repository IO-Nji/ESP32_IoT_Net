#include "src/hal/hal_bme280.h"
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void hal_bme280_init() {
    bme.begin(0x76);
}

bool hal_bme280_read(float* temperature, float* humidity, float* pressure) {
    if (!bme.begin(0x76)) return false;
    *temperature = bme.readTemperature();
    *humidity = bme.readHumidity();
    *pressure = bme.readPressure();
    return true;
}
