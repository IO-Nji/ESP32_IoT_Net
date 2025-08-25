#include "src/hal/hal_sensor.h"

void hal_sensor_init() {
    // Initialize sensor
}

bool hal_sensor_read(SensorData* data) {
    // Read sensor data
    data->temperature = 25.0;
    data->humidity = 50.0;
    data->pressure = 1013.0;
    return true;
}
