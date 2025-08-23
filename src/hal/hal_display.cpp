#include "hal_display.h"
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display1(128, 64, &Wire, -1);
Adafruit_SSD1306 display2(128, 64, &Wire, -1);

void hal_display_init() {
    display1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display2.begin(SSD1306_SWITCHCAPVCC, 0x3D);
}

void hal_display_clear() {
    display1.clearDisplay();
    display2.clearDisplay();
}

void hal_display_print(const char* msg, uint8_t line) {
    display1.setCursor(0, line * 8);
    display1.print(msg);
    display1.display();
}
