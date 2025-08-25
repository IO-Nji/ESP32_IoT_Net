#ifndef UI_LOGO_H
#define UI_LOGO_H
#include <Adafruit_SSD1306.h>

struct LogoRect {
  int x, y, w, h;
};

void logoDisplay(Adafruit_SSD1306& display, int startX, int startY);

#endif // UI_LOGO_H
