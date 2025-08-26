#include <Arduino.h>
#include "src/hal/hal_init.h"
#include "src/tasks/task_manager.h"

SystemState globalState;

void setup() {
  hal_init_all();
  createTasks(&globalState);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000)); // Idle loop, tasks do the work
}
