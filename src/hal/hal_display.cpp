#include "src/hal/hal_display.h"
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display1;
extern Adafruit_SSD1306 display2;

void hal_display_init() {
    Serial.println("hal_display_init: Initializing display1 (0x3C)");
    if (display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        display1.setRotation(2); // 180 degree rotation
        display1.clearDisplay();
        display1.setTextSize(1);
        display1.setTextColor(SSD1306_WHITE);
        display1.setCursor(20, 28);
        display1.print("Display 1");
        display1.display();
        Serial.println("hal_display_init: display1 initialized, rotated, and test message shown");
    } else {
        Serial.println("hal_display_init: display1 not found");
    }

    Serial.println("hal_display_init: Initializing display2 (0x3D)");
    if (display2.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
        display2.setRotation(2); // 180 degree rotation
        display2.clearDisplay();
        display2.setTextSize(1);
        display2.setTextColor(SSD1306_WHITE);
        display2.setCursor(20, 28);
        display2.print("Display 2");
        display2.display();
        Serial.println("hal_display_init: display2 initialized, rotated, and test message shown");
    } else {
        Serial.println("hal_display_init: display2 not found");
    }
}

void hal_display_clear(DisplayType display) {
    if (display == DISPLAY_1) display1.clearDisplay();
    else if (display == DISPLAY_2) display2.clearDisplay();
}

void hal_display_print(DisplayType display, const char* msg, uint8_t line) {
    if (display == DISPLAY_1) {
        Serial.print("hal_display_print: DISPLAY_1 line ");
        Serial.print(line);
        Serial.print(" msg: ");
        Serial.println(msg);
        display1.setTextSize(2); // Make text larger
        display1.setCursor(0, line * 16); // Adjust for larger text
        display1.print(msg);
        display1.display();
        Serial.println("hal_display_print: DISPLAY_1 display() called");
    } else if (display == DISPLAY_2) {
        Serial.print("hal_display_print: DISPLAY_2 line ");
        Serial.print(line);
        Serial.print(" msg: ");
        Serial.println(msg);
        display2.setTextSize(2);
        display2.setCursor(0, line * 16);
        display2.print(msg);
        display2.display();
        Serial.println("hal_display_print: DISPLAY_2 display() called");
    }
}
