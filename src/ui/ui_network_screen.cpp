#include "src/ui/ui_network_screen.h"
#include <Adafruit_SSD1306.h>

void ui_network_screen_render(Adafruit_SSD1306& display, const char* homeSSID, const char* localSSID, const char* ip, const char* status) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds("NETWORK", 0, 0, &x1, &y1, &w, &h);
    display.setCursor((128 - w) / 2, 54);
    display.print("NETWORK");
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Home: ");
    display.print(homeSSID);
    display.setCursor(0, 10);
    display.print("IP: ");
    display.print(ip);
    display.setCursor(0, 20);
    display.print("Local: ");
    display.print(localSSID);
    display.setCursor(0, 30);
    display.print("IP: ");
    display.print(ip);
    display.setCursor(0, 40);
    display.print("Status: ");
    display.print(status);
    display.display();
}
