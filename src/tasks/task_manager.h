#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Shared state structs (expand as needed)
typedef struct {
    float temp, hum, pres;
    size_t freeHeap, totalHeap;
    int lastPressed;
    bool dipswitchStates[6];
} SystemState;

// Task handles
extern TaskHandle_t uiTaskHandle;
extern TaskHandle_t sensorTaskHandle;
extern TaskHandle_t networkTaskHandle;
extern TaskHandle_t internetDataTaskHandle;

// Task creation function
void createTasks(SystemState* state);

#endif // TASK_MANAGER_H
