#include "Syn6288.h"

SoftwareSerial TTS_Reader(A1, A2); // RX, TX

uint8_t v0[] = {0x5b, 0x76, 0x30, 0x5d};
uint8_t v1[] = {0x5b, 0x76, 0x31, 0x5d};
uint8_t v2[] = {0x5b, 0x76, 0x32, 0x5d};
uint8_t v3[] = {0x5b, 0x76, 0x33, 0x5d};
uint8_t v4[] = {0x5b, 0x76, 0x34, 0x5d};
uint8_t v5[] = {0x5b, 0x76, 0x35, 0x5d};
uint8_t v6[] = {0x5b, 0x76, 0x36, 0x5d};
uint8_t v7[] = {0x5b, 0x76, 0x37, 0x5d};
uint8_t v8[] = {0x5b, 0x76, 0x38, 0x5d};
uint8_t v9[] = {0x5b, 0x76, 0x39, 0x5d};
uint8_t v10[] = {0x5b, 0x76, 0x31, 0x30, 0x5d};
uint8_t v11[] = {0x5b, 0x76, 0x31, 0x31, 0x5d};
uint8_t v12[] = {0x5b, 0x76, 0x31, 0x32, 0x5d};
uint8_t v13[] = {0x5b, 0x76, 0x31, 0x33, 0x5d};
uint8_t v14[] = {0x5b, 0x76, 0x31, 0x34, 0x5d};
uint8_t v15[] = {0x5b, 0x76, 0x31, 0x35, 0x5d};
uint8_t v16[] = {0x5b, 0x76, 0x31, 0x36, 0x5d};

uint8_t t5[] = {0x5b, 0x74, 0x35, 0x5d};

void syn6288_init() {
  TTS_Reader.begin(9600);
  syn6288_play(t5, sizeof(t5));
  setVol(10);
}

void setVol(int vol) {
  switch (vol) {
    case 0:
      syn6288_play(v0, sizeof(v0));
      break;
    case 1:
      syn6288_play(v1, sizeof(v1));
      break;
    case 2:
      syn6288_play(v2, sizeof(v2));
      break;
    case 3:
      syn6288_play(v3, sizeof(v3));
      break;
    case 4:
      syn6288_play(v4, sizeof(v4));
      break;
    case 5:
      syn6288_play(v5, sizeof(v5));
      break;
    case 6:
      syn6288_play(v6, sizeof(v6));
      break;
    case 7:
      syn6288_play(v7, sizeof(v7));
      break;
    case 8:
      syn6288_play(v8, sizeof(v8));
      break;
    case 9:
      syn6288_play(v9, sizeof(v9));
      break;
    case 10:
      syn6288_play(v10, sizeof(v10));
      break;
    case 11:
      syn6288_play(v11, sizeof(v11));
      break;
    case 12:
      syn6288_play(v12, sizeof(v12));
      break;
    case 13:
      syn6288_play(v13, sizeof(v13));
      break;
    case 14:
      syn6288_play(v14, sizeof(v14));
      break;
    case 15:
      syn6288_play(v15, sizeof(v15));
      break;
    case 16:
      syn6288_play(v16, sizeof(v16));
      break;
    default:
      syn6288_play(v10, sizeof(v16));
      break;
  }
}
void syn6288_play(uint8_t *text, uint8_t TEXTLEN)
{
  uint8_t head[5] = {0xfd, 0x00, 0x00, 0x01, 0x01};
  uint8_t pi = 0;
  delay(100);
  head[2] = TEXTLEN + 3;
  for (int i = 0; i < 5; i++)
  {
    pi ^= head[i];
    TTS_Reader.write(head[i]);
    delay(2);
  }
  for (int j = 0; j < TEXTLEN; j++)
  {
    pi ^= text[j];
    TTS_Reader.write(text[j]);
    delay(2);
  }
  TTS_Reader.write(pi);
  delay(300 * TEXTLEN);
}
