#ifndef UI_SYSTEMINFO_SCREEN_H
#define UI_SYSTEMINFO_SCREEN_H
#include <Adafruit_SSD1306.h>
#include <stdint.h>

void ui_systemInfo_screen_render(Adafruit_SSD1306& display, float temp, float hum, float pres, size_t freeHeap, size_t totalHeap, int lastPressed, const char* lastPressedName, const bool dipswitchStates[], int dipswitchCount);

#endif // UI_SYSTEMINFO_SCREEN_H
