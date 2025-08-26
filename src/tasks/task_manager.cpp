#include "task_manager.h"
#include "config/config.h"
#include "src/hal/hal_display.h"
#include "src/hal/hal_button.h"
#include "src/ui/ui_logo.h"
#include "src/hal/hal_bme280.h"
#include "src/hal/hal_wifi.h"
#include "src/hal/hal_dipswitch.h"
#include "src/ui/ui_systemInfo_screen.h"
#include "src/ui/ui_network_screen.h"
#include "src/ui/ui_timeWeather_screen.h"
#include "src/services/web_server.h"
#include "src/services/internet_data_service.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display1;
extern Adafruit_SSD1306 display2;

TaskHandle_t uiTaskHandle = NULL;
TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t networkTaskHandle = NULL;
TaskHandle_t internetDataTaskHandle = NULL;

// UI Task
void uiTask(void* pvParameters) {
    // SystemState* state = (SystemState*)pvParameters; // Not used
    static int lastPressed = -1;
    static bool prevState[4] = {false, false, false, false};
    static unsigned long lastSwitch = 0;
    static bool showNetwork = true;
    for (;;) {
        // Button state debug
        if (SERIAL_DEBUG) {
            Serial.print(F("Button states: "));
            for (int i = 0; i < 4; ++i) {
                Serial.print(hal_button_get_name((ButtonType)i));
                Serial.print(F("="));
                Serial.print(hal_button_is_pressed((ButtonType)i) ? F("PRESSED") : F("UP"));
                Serial.print(F(" "));
            }
            Serial.println();
        }
        // Track last pressed button
        for (int i = 0; i < 4; ++i) {
            bool curr = hal_button_is_pressed((ButtonType)i);
            if (curr && !prevState[i]) {
                lastPressed = i;
            }
            prevState[i] = curr;
        }
        // System info for display1 with DIP switch state table
        float temp = 0, hum = 0, pres = 0;
        hal_bme280_read(&temp, &hum, &pres);
        size_t freeHeap = ESP.getFreeHeap();
        size_t totalHeap = ESP.getHeapSize();
        bool dipswitchStates[6];
        hal_dipswitch_read_states(dipswitchStates);
        ui_systemInfo_screen_render(
            display1,
            temp, hum, pres,
            freeHeap, totalHeap,
            lastPressed,
            lastPressed >= 0 ? hal_button_get_name((ButtonType)lastPressed) : nullptr,
            dipswitchStates,
            6
        );
        // Alternate display2 between network and time/weather screens every 5 seconds
        unsigned long now = millis();
        if (now - lastSwitch > 5000) {
            showNetwork = !showNetwork;
            lastSwitch = now;
        }
        if (showNetwork) {
            ui_network_screen_render(display2);
        } else {
            ui_timeWeather_screen_render(display2);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Sensor Task
void sensorTask(void* pvParameters) {
    // SystemState* state = (SystemState*)pvParameters; // Not used
    for (;;) {
        // ... Sensor logic updating state ...
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Network Task
void networkTask(void* pvParameters) {
    // SystemState* state = (SystemState*)pvParameters; // Not used
    for (;;) {
        web_server_loop();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Internet Data Task
void internetDataTask(void* pvParameters) {
    // SystemState* state = (SystemState*)pvParameters; // Not used
    for (;;) {
        internet_data_service_update();
        internet_data_service_print();
        vTaskDelay(pdMS_TO_TICKS(60000)); // Update every minute
    }
}

void createTasks(SystemState* state) {
    xTaskCreate(uiTask, "UI Task", 4096, state, 2, &uiTaskHandle);
    xTaskCreate(sensorTask, "Sensor Task", 2048, state, 1, &sensorTaskHandle);
    xTaskCreate(networkTask, "Network Task", 4096, state, 3, &networkTaskHandle);
    xTaskCreate(internetDataTask, "Internet Data Task", 4096, state, 2, &internetDataTaskHandle);
}
