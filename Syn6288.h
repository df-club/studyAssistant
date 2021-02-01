#ifndef _SYN6288_TTS_H_
#define _SYN6288_TTS_H_

#include<Arduino.h>
#include <SoftwareSerial.h>

void setVol(int vol);
void syn6288_play(uint8_t *text,uint8_t TEXTLEN);
void syn6288_init();

#endif
