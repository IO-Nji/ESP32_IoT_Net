#ifndef HAL_SENSOR_H
#define HAL_SENSOR_H
#include <stdint.h>

// Sensor HAL Interface
typedef struct {
    float temperature;
    float humidity;
    float pressure;
} SensorData;

void hal_sensor_init();
bool hal_sensor_read(SensorData* data);

#endif // HAL_SENSOR_H
