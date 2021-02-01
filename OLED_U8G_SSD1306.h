#ifndef OLED_U8G_SSD1306
#define OLED_U8G_SSD1306

#include "U8glib.h"
#include<Arduino.h>

void oled_init();
void oled_draw(const char* inputMsg,int delayTime = 0);

#endif
