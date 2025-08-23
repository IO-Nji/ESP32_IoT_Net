#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "hal_display.h"
#include "hal_sensor.h"
#include "hal_network.h"
#include "hal_button.h"

// Task handles
TaskHandle_t uiTaskHandle = NULL;
TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t networkTaskHandle = NULL;

// UI Task: Handles display updates and button navigation
void uiTask(void* pvParameters) {
	hal_display_init();
	hal_button_init();
	while (true) {
		hal_button_update();
		// Example: Show system info on display 1
		hal_display_clear(DISPLAY_1);
		hal_display_print(DISPLAY_1, "ESP32 IoT Server", 0);
		// ... add navigation and UI logic here ...
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

// Sensor Task: Polls sensors and updates data
void sensorTask(void* pvParameters) {
	hal_sensor_init();
	SensorData data;
	while (true) {
		if (hal_sensor_read(&data)) {
			// Example: Show sensor data on display 2
			char buf[32];
			snprintf(buf, sizeof(buf), "Temp: %.1fC", data.temperature);
			hal_display_clear(DISPLAY_2);
			hal_display_print(DISPLAY_2, buf, 0);
			// ... add more sensor info ...
		}
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

// Network Task: Manages network connection and info
void networkTask(void* pvParameters) {
	// Example credentials
	const char* ap_ssid = "ESP32_AP";
	const char* ap_pass = "password";
	const char* sta_ssid = "HomeWiFi";
	const char* sta_pass = "homepass";
	hal_network_init(ap_ssid, ap_pass, sta_ssid, sta_pass);
	while (true) {
		NetworkInfo info = hal_network_get_info();
		// ... handle network events, update status ...
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}

void setup() {
	// Create FreeRTOS tasks
	xTaskCreatePinnedToCore(uiTask, "UITask", 4096, NULL, 2, &uiTaskHandle, 0);
	xTaskCreatePinnedToCore(sensorTask, "SensorTask", 4096, NULL, 1, &sensorTaskHandle, 1);
	xTaskCreatePinnedToCore(networkTask, "NetworkTask", 4096, NULL, 1, &networkTaskHandle, 1);
}

void loop() {
	// Empty: All logic handled in FreeRTOS tasks
}
