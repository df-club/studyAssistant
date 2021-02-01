#include "OLED_U8G_SSD1306.h"


U8GLIB_SSD1306_128X64 u8g_OLED(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI

void oled_init() {
  if ( u8g_OLED.getMode() == U8G_MODE_R3G3B2 )
  {
    u8g_OLED.setColorIndex(255);     // white
  }
  else if ( u8g_OLED.getMode( ) == U8G_MODE_GRAY2BIT )
  {
    u8g_OLED.setColorIndex(3);         // max intensity
  }
  else if ( u8g_OLED.getMode() == U8G_MODE_BW )
  {
    u8g_OLED.setColorIndex(1);         // pixel on
  }
  else if ( u8g_OLED.getMode() == U8G_MODE_HICOLOR )
  {
    u8g_OLED.setHiColorByRGB(255, 255, 255);
  }
}

void oled_draw(const char* inputMsg, int delayTime = 0) {
  int len = strlen(inputMsg);
  u8g_OLED.firstPage();
  int i = 0;
  do
  {
    u8g_OLED.setFont(u8g_font_unifont);
    for (i=0; i<len; i++) {
      u8g_OLED.drawStr((i % 16) * 8, 12 * ((i - i % 16) / 16 + 1), &inputMsg[i]);
    }
  } while ( u8g_OLED.nextPage());
  delay(delayTime);
}
