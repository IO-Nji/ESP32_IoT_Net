#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "src/hal/hal_display.h"
#include "src/hal/hal_sensor.h"
#include "src/services/hal_network.h"
#include "src/hal/hal_button.h"
#include "src/services/ui_state_machine.h"

// Task handles
TaskHandle_t uiTaskHandle = NULL;
TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t networkTaskHandle = NULL;

// UI Task: Handles display updates and button navigation
void uiTask(void* pvParameters) {
	hal_display_init();
	hal_button_init();
	ui_state_machine_init();
	while (true) {
		Serial.println("uiTask running");
		hal_button_update();
		// Poll buttons and push events to queue
		if (hal_button_is_pressed(BUTTON_SELECT)) ui_event_queue_push(UI_EVENT_SELECT);
		if (hal_button_is_pressed(BUTTON_UP))     ui_event_queue_push(UI_EVENT_UP);
		if (hal_button_is_pressed(BUTTON_DOWN))   ui_event_queue_push(UI_EVENT_DOWN);
		if (hal_button_is_pressed(BUTTON_BACK))   ui_event_queue_push(UI_EVENT_BACK);

		// Process UI events
		UIEvent event = ui_event_queue_pop();
		if (event.type != UI_EVENT_NONE) {
			ui_state_machine_handle_event(&event);
		}

		// Show network status on display1
		NetworkInfo info = hal_network_get_info();
		hal_display_clear(DISPLAY_1);
		hal_display_print(DISPLAY_1, "WiFi SSID:", 0);
		hal_display_print(DISPLAY_1, info.ssid, 1);
		hal_display_print(DISPLAY_1, "IP:", 2);
		hal_display_print(DISPLAY_1, info.ip, 3);
		hal_display_print(DISPLAY_1, info.connected ? "Connected" : "Disconnected", 4);

		// Show system status on display2
		hal_display_clear(DISPLAY_2);
		hal_display_print(DISPLAY_2, "System Status", 0);
		// CPU and memory info (dummy values for now)
		char buf[32];
		snprintf(buf, sizeof(buf), "CPU: %d%%", 50); // Replace with actual CPU usage if available
		hal_display_print(DISPLAY_2, buf, 1);
		snprintf(buf, sizeof(buf), "Mem: %dKB", 128); // Replace with actual memory usage if available
		hal_display_print(DISPLAY_2, buf, 2);
		// BME280 sensor readings
		SensorData data;
		if (hal_sensor_read(&data)) {
			snprintf(buf, sizeof(buf), "T: %.1fC H: %.1f%%", data.temperature, data.humidity);
			hal_display_print(DISPLAY_2, buf, 3);
			snprintf(buf, sizeof(buf), "P: %.1fhPa", data.pressure);
			hal_display_print(DISPLAY_2, buf, 4);
		} else {
			hal_display_print(DISPLAY_2, "Sensor Error", 3);
		}
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

// Sensor Task: Polls sensors and updates data
void sensorTask(void* pvParameters) {
	hal_sensor_init();
	SensorData data;
	while (true) {
		hal_sensor_read(&data);
		// Sensor data is now only used by uiTask for display
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

// ...existing code...
