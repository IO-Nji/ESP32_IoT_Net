// ...existing code...
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
#include "src/services/web_server.h"
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
  hal_wifi_init_ap_sta("EspNET", "esp32net!", "Home-WiFi", "homepass");
  // Start web server
  web_server_init();
  // Only use HAL print for display output
  // Show logo and startup text on both displays
  logoDisplay(display1, 14, 12);
  display1.setTextSize(1);
  display1.setTextColor(SSD1306_WHITE);
  display1.setCursor(60, 40);
  display1.println("INIT:");
  display1.setCursor(60, 50);
  display1.print("Display 1");
  display1.display();

  logoDisplay(display2, 14, 12);
  display2.setTextSize(1);
  display2.setTextColor(SSD1306_WHITE);
  display2.setCursor(60, 40);
  display2.println("INIT:");
  display2.setCursor(60, 50);
  display2.print("Display 2");
  display2.display();

  delay(5000);
  Serial.println("setup running");
  // // Create FreeRTOS tasks with increased stack size
  // xTaskCreate(uiTask, "UI Task", 8192, NULL, 1, NULL);
  // xTaskCreate(sensorTask, "Sensor Task", 8192, NULL, 1, NULL);
  // xTaskCreate(networkTask, "Network Task", 8192, NULL, 1, NULL);
}

void loop() {
  
  // Debug: print all button states to Serial
  Serial.print("Button states: ");
  for (int i = 0; i < 4; ++i) {
    Serial.print(hal_button_get_name((ButtonType)i));
    Serial.print("=");
    Serial.print(hal_button_is_pressed((ButtonType)i) ? "PRESSED" : "UP");
    Serial.print(" ");
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
  bool bme_ok = hal_bme280_read(&temp, &hum, &pres);
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

  // Network INFO for display2
  ui_network_screen_render(display2);

  // Handle web server requests
  web_server_loop();
  delay(2000); // Update every 2 seconds
}
