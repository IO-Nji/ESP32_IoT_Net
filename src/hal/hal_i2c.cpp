#include "hal_i2c.h"
#include <Wire.h>

void hal_i2c_init() {
    Wire.begin(8, 9); // SDA, SCL
}

bool hal_i2c_read(uint8_t addr, uint8_t *data, size_t len) {
    Wire.beginTransmission(addr);
    Wire.requestFrom(addr, len);
    for (size_t i = 0; i < len && Wire.available(); ++i) {
        data[i] = Wire.read();
    }
    Wire.endTransmission();
    return true;
}

bool hal_i2c_write(uint8_t addr, const uint8_t *data, size_t len) {
    Wire.beginTransmission(addr);
    Wire.write(data, len);
    Wire.endTransmission();
    return true;
}
