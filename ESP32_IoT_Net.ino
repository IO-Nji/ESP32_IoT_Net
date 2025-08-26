#include <Arduino.h>
#include <Wire.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
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
#include "config/config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "src/tasks/task_manager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Global display objects
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Use task implementations from main_app.cpp
extern void uiTask(void* pvParameters);

SystemState globalState;

void setup() {
  if (SERIAL_DEBUG) Serial.begin(115200);
  hal_display_init();
  hal_bme280_init();
  // Initialize WiFi in AP+STA mode
  hal_wifi_init_ap_sta(WIFI_AP_SSID, WIFI_AP_PASSWORD, WIFI_STA_SSID, WIFI_STA_PASSWORD);
  // Start web server
  web_server_init();
  // Initialize internet data service (replace with your OpenWeather API key and city)
  internet_data_service_init(WEATHER_API_KEY, WEATHER_CITY);
  // Only use HAL print for display output
  // Show logo and startup text on both displays
  logoDisplay(display1, 14, 12);
  display1.setTextSize(1);
  display1.setTextColor(SSD1306_WHITE);
  display1.setCursor(60, 40);
  display1.println(F("INIT:"));
  display1.setCursor(60, 50);
  display1.print(F("Display "));
  display1.setTextSize(2);
  display1.print(F("1"));
  display1.display();

  logoDisplay(display2, 14, 12);
  display2.setTextSize(1);
  display2.setTextColor(SSD1306_WHITE);
  display2.setCursor(60, 40);
  display2.println(F("INIT:"));
  display2.setCursor(60, 50);
  display2.print(F("Display "));
  display2.setTextSize(2);
  display2.print(F("2"));
  display2.display();

  delay(5000);
  if (SERIAL_DEBUG) Serial.println(F("setup running"));
  createTasks(&globalState);
}

// UI responsibility
void uiLoop() {
  static int lastPressed = -1;
  static bool prevState[4] = {false, false, false, false};
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
  for (int i = 0; i < 4; ++i) {
    bool curr = hal_button_is_pressed((ButtonType)i);
    if (curr && !prevState[i]) {
      lastPressed = i;
    }
    prevState[i] = curr;
  }
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
  static unsigned long lastSwitch = 0;
  static bool showNetwork = true;
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
}

// Sensor responsibility
void sensorLoop() {
  // Currently handled in uiLoop for demo, can be separated for periodic sensor reads
}

// Network responsibility
void networkLoop() {
  web_server_loop();
}

// Internet data responsibility
void internetDataLoop() {
  internet_data_service_update();
  internet_data_service_print();
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000)); // Idle loop, tasks do the work
}
