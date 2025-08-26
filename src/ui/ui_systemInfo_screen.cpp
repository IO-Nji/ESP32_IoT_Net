#include "src/ui/ui_systemInfo_screen.h"
#include <Adafruit_SSD1306.h>

void ui_systemInfo_screen_render(Adafruit_SSD1306& display, float temp, float hum, float pres, size_t freeHeap, size_t totalHeap, int lastPressed, const char* lastPressedName, const bool dipswitchStates[], int dipswitchCount) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds("SYSTEM", 0, 0, &x1, &y1, &w, &h);
    display.setCursor((128 - w) / 2, 0);
    display.print("SYSTEM");
    display.setCursor(0, 10);
    display.print("RAM: ");
    int ramPercent = (int)((freeHeap * 100) / totalHeap);
    display.print(ramPercent);
    display.print("%");
    display.setCursor(0, 20);
    display.print("MEM: ");
    int usedPercent = (int)(((totalHeap - freeHeap) * 100) / totalHeap);
    display.print(usedPercent);
    display.print("%");
    display.setCursor(0, 32);
    display.print("T: ");
    display.print(temp, 1);
    display.print("C ");
    display.setCursor(0, 42);
    display.print("H: ");
    display.print(hum, 1);
    display.print("%");
    display.setCursor(0, 52);
    display.print("P: ");
    display.print(pres / 100.0, 1);
    display.print("hPa");

    // Show last pressed button name
    if (lastPressed >= 0 && lastPressedName) {
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(58, 20);
        display.print(lastPressedName);
        display.setTextSize(1);
    }

    // DIP switch state table (right side)
    int colX[2] = {96, 112};
    int rowY[3] = {12, 29, 46};
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 2; ++col) {
            int idx = row * 2 + col;
            if (idx >= dipswitchCount) continue;
            int x = colX[col];
            int y = rowY[row];
            if (dipswitchStates[idx]) {
                display.drawRect(x - 2, y - 2, 14, 14, SSD1306_WHITE);
            }
            display.setCursor(x + 2, y + 1);
            display.print(idx + 1);
        }
    }
    display.display();
}
