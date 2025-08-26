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
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#include "src/ui/ui_logo.h"

// Global display objects
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Use task implementations from main_app.cpp
extern void uiTask(void* pvParameters);
// Removed FreeRTOS task implementations
void setup() {
  Serial.begin(115200);
  hal_display_init();
  hal_bme280_init();
  // Initialize WiFi in AP+STA mode
  hal_wifi_init_ap_sta("EspNET", "esp32net!", "nji.IO.mini", "10203040");
  // Start web server
  web_server_init();
  // Initialize internet data service (replace with your OpenWeather API key and city)
  internet_data_service_init("6a3e4157f8bf64b750658b17a152910b", "Berlin");
  // Only use HAL print for display output
  // Show logo and startup text on both displays
  logoDisplay(display1, 14, 12);
  display1.setTextSize(1);
  display1.setTextColor(SSD1306_WHITE);
  display1.setCursor(60, 40);
  display1.println(F("INIT:"));
  display1.setCursor(60, 50);
  display1.print(F("Display 1"));
  display1.display();

  logoDisplay(display2, 14, 12);
  display2.setTextSize(1);
  display2.setTextColor(SSD1306_WHITE);
  display2.setCursor(60, 40);
  display2.println(F("INIT:"));
  display2.setCursor(60, 50);
  display2.print(F("Display 2"));
  display2.display();

  delay(5000);
  Serial.println(F("setup running"));
  // // Create FreeRTOS tasks with increased stack size
  // xTaskCreate(uiTask, "UI Task", 8192, NULL, 1, NULL);
  // xTaskCreate(sensorTask, "Sensor Task", 8192, NULL, 1, NULL);
  // xTaskCreate(networkTask, "Network Task", 8192, NULL, 1, NULL);
}

void loop() {
  
  // Debug: print all button states to Serial
  Serial.print(F("Button states: "));
  for (int i = 0; i < 4; ++i) {
    Serial.print(hal_button_get_name((ButtonType)i));
  Serial.print(F("="));
  Serial.print(hal_button_is_pressed((ButtonType)i) ? F("PRESSED") : F("UP"));
  Serial.print(F(" "));
  }
  Serial.println();
  
  // Track last pressed button
  static int lastPressed = -1;
  static bool prevState[4] = {false, false, false, false};
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

  // Update and print internet time/weather info every minute
  internet_data_service_update();
  internet_data_service_print();

  // Handle web server requests
  web_server_loop();
  delay(2000); // Update every 2 seconds
}
