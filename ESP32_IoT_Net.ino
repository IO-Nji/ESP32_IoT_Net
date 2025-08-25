// ...existing code...
#include <Arduino.h>
#include <Wire.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "src/hal/hal_display.h"
#include "src/ui/ui_logo.h"
#include "src/hal/hal_bms280.h"

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
  Wire.begin(8, 9); // SDA = 8, SCL = 9 for ESP32-C3 Supermini
  hal_display_init();
  hal_bms280_init();
  // Only use HAL print for display output
  // Show logo and startup text on both displays
  logoDisplay(display1, 14, 12);
  display1.setTextSize(1);
  display1.setTextColor(SSD1306_WHITE);
  display1.setCursor(60, 40);
  display1.print("Display 1");
  display1.display();

  logoDisplay(display2, 14, 12);
  display2.setTextSize(1);
  display2.setTextColor(SSD1306_WHITE);
  display2.setCursor(60, 40);
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
  // System info for display1 with DIP switch state table
  float temp = 0, hum = 0, pres = 0;
  bool bme_ok = hal_bms280_read(&temp, &hum, &pres);
  hal_display_clear(DISPLAY_1);
  display1.setTextSize(1);
  display1.setTextColor(SSD1306_WHITE);
  int16_t x1, y1;
  uint16_t w, h;
  display1.getTextBounds("SYSTEM", 0, 0, &x1, &y1, &w, &h);
  display1.setCursor((SCREEN_WIDTH - w) / 2, 0);
  display1.print("SYSTEM");
  display1.setTextSize(1);
  display1.setCursor(0, 12);
  display1.print("RAM: ");
  size_t freeHeap = ESP.getFreeHeap();
  size_t totalHeap = ESP.getHeapSize();
  int ramPercent = (int)((freeHeap * 100) / totalHeap);
  display1.print(ramPercent);
  display1.print("%");
  display1.setCursor(0, 24);
  if (bme_ok) {
    display1.print("T: ");
    display1.print(temp, 1);
    display1.print("C");
    display1.setCursor(0, 36);
    display1.print("H: ");
    display1.print(hum, 1);
    display1.print("%");
    display1.setCursor(0, 48);
    display1.print("P: ");
    display1.print(pres / 100.0, 1);
    display1.print("hPa");
  } else {
    display1.print("BME280 Error");
  }

  // DIP switch state table (right side)
  int dipPins[6] = {1, 2, 3, 4, 5, 6};
  int dipStates[6];
  for (int i = 0; i < 6; ++i) {
    pinMode(dipPins[i], INPUT_PULLUP);
    dipStates[i] = digitalRead(dipPins[i]); // HIGH = up, LOW = down
  }
    int colX[2] = {84, 104};
    int rowY[3] = {12, 29, 46};
    for (int row = 0; row < 3; ++row) {
      for (int col = 0; col < 2; ++col) {
        int idx = row * 2 + col; // row pairs: (1,2), (3,4), (5,6)
        int x = colX[col];
        int y = rowY[row];
        if (dipStates[idx] == LOW) {
          display1.drawRect(x - 2, y - 2, 14, 14, SSD1306_WHITE);
        }
        display1.setCursor(x + 2, y + 1);
        display1.print(dipPins[idx]);
      }
    }
  display1.display();

  // Network info for display2
  hal_display_clear(DISPLAY_2);
  display2.setTextSize(1);
  display2.setTextColor(SSD1306_WHITE);
  display2.getTextBounds("NETWORK", 0, 0, &x1, &y1, &w, &h);
  display2.setCursor((SCREEN_WIDTH - w) / 2, 0);
  display2.print("NETWORK");
  display2.setTextSize(1);
  display2.setCursor(0, 12);
  display2.print("Home SSID: HomeWiFi"); // Replace with actual SSID
  display2.setCursor(0, 24);
  display2.print("Local SSID: ESP32Net"); // Replace with actual SSID
  display2.setCursor(0, 36);
  display2.print("IP: 192.168.1.100");    // Replace with actual IP
  display2.setCursor(0, 48);
  display2.print("Status: Connected");    // Replace with actual status
  display2.display();

  delay(2000); // Update every 2 seconds
}
