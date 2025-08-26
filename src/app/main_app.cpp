#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "src/hal/hal_display.h"
#include "src/hal/hal_bme280.h"
#include "src/services/network_service.h"
#include "src/hal/hal_button.h"
#include "src/services/ui_state_machine.h"


// ...existing code...
