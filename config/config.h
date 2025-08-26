#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SERIAL_DEBUG true // Set to false to disable serial prints
#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
#define WIFI_AP_SSID      "EspNET"
#define WIFI_AP_PASSWORD  "esp32net!"
#define WIFI_STA_SSID     "nji.IO.mini"
#define WIFI_STA_PASSWORD "10203040"

// OpenWeather API
#define WEATHER_API_KEY   "6a3e4157f8bf64b750658b17a152910b"
#define WEATHER_CITY      "Berlin"
#define WEATHER_TZ_OFFSET 7200 // Berlin summer time (UTC+2)

// Display addresses
#define DISPLAY1_ADDR 0x3C
#define DISPLAY2_ADDR 0x3D

// Button pins
#define BUTTON1_PIN 10
#define BUTTON2_PIN 20
#define BUTTON3_PIN 21
#define BUTTON4_PIN 0

// Dip switch pins
#define DIPSWITCH_PINS {1,2,3,4,5,6}

// BME280 sensor address
#define BME280_ADDR 0x76

// WS2812 LED strip pin
#define WS2812_PIN 7

#endif // CONFIG_H
