#include "hal_init.h"
#include "config/config.h"
#include "src/hal/hal_display.h"
#include "src/hal/hal_bme280.h"
#include "src/hal/hal_wifi.h"
#include "src/services/web_server.h"
#include "src/services/internet_data_service.h"
#include "src/ui/ui_logo.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void hal_init_all() {
    hal_display_init();
    hal_bme280_init();
    hal_wifi_init_ap_sta(WIFI_AP_SSID, WIFI_AP_PASSWORD, WIFI_STA_SSID, WIFI_STA_PASSWORD);
    web_server_init();
    internet_data_service_init(WEATHER_API_KEY, WEATHER_CITY);
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
    if (SERIAL_DEBUG) Serial.println(F("setup running"));
}
