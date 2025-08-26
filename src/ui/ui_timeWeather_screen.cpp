
#include "ui_timeWeather_screen.h"
#include <Adafruit_SSD1306.h>
#include "src/services/internet_data_service.h"

// Getter functions to access time and weather info
extern "C" {
    const WeatherInfo* getWeatherInfo();
    const char* getFormattedTime();
}

void ui_timeWeather_screen_render(Adafruit_SSD1306& display) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(F("Time: "));
    // Parse HH:MM:SS from getFormattedTime()
    const char* timeStr = getFormattedTime();
    int hour = 0, min = 0, sec = 0;
    if (timeStr && strlen(timeStr) >= 8) {
        sscanf(timeStr, "%2d:%2d:%2d", &hour, &min, &sec);
        char buf[16];
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d", hour, min, sec);
        display.print(buf);
    } else {
        display.print("--:--:--");
    }
    const WeatherInfo* weather = getWeatherInfo();
    display.setCursor(0, 12);
    display.print(F("Weather: "));
    display.print(weather ? weather->description : "");
    display.setCursor(0, 24);
    display.print(F("Temp: "));
    display.print(weather ? weather->temperature : 0.0, 1);
    display.print(F("C"));
    display.setCursor(0, 36);
    display.print(F("Humidity: "));
    display.print(weather ? weather->humidity : 0.0, 1);
    // Center the "%" and "TIME / Weather" text horizontally
    const char* percentText = "%";
    const char* footerText = "TIME / Weather";

    // Calculate x position for centering
    int16_t x1, y1;
    uint16_t w, h;

    // Center "%" at y = 36
    display.getTextBounds(percentText, 0, 36, &x1, &y1, &w, &h);
    int16_t percentX = (display.width() - w) / 2;
    display.setCursor(percentX, 36);
    display.print(F("%"));

    // Center "Time / Weather" at y = 48
    display.getTextBounds(footerText, 0, 48, &x1, &y1, &w, &h);
    int16_t footerX = (display.width() - w) / 2;
    display.setCursor(footerX, 48);
    display.print(F("Time / Weather"));
    display.display();
}
