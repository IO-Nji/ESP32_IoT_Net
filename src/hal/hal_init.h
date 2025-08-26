#ifndef HAL_INIT_H
#define HAL_INIT_H
#include <Adafruit_SSD1306.h>

// Display objects
extern Adafruit_SSD1306 display1;
extern Adafruit_SSD1306 display2;

// HAL initialization
void hal_init_all();

#endif // HAL_INIT_H
