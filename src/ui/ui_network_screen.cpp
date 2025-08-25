
#include "src/ui/ui_network_screen.h"
#include <Adafruit_SSD1306.h>
#include "src/services/network_service.h"

void ui_network_screen_render(Adafruit_SSD1306& display) {
    NetworkInfo info = network_service_get_info();
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
    display.print("AP SSID: ");
    display.print(info.ap_ssid);
    display.setCursor(0, 10);
    display.print("AP IP: ");
    display.print(info.ap_ip);
    display.setCursor(0, 20);
    display.print("STA SSID: ");
    display.print(info.ssid);
    display.setCursor(0, 30);
    display.print("STA IP: ");
    display.print(info.ip);
    display.setCursor(0, 40);
    display.print("Status: ");
    display.print(info.connected ? "Connected" : "Disconnected");
    display.display();
}
