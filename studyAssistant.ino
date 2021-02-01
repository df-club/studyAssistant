#include "HC_SR04.h"
#include "OLED_U8G_SSD1306.h"
#include "Syn6288.h"
// PIN

const int ut_trigPin = 10;
const int ut_echoPin = 9;

const int bottomServoPin = 5; // PWM
const int topServoPin = 6;    // PWM

const int ledPin = 4;

const int potentiometerPin = A0;

// Object for HC_SR04

HC_SR04 ut_hc_sr04(ut_trigPin, ut_echoPin);

uint8_t tips[] = {0xc7, 0xeb, 0xb5, 0xf7, 0xd5, 0xfb, 0xd7, 0xf8, 0xd7, 0xcb, 0xa3, 0xac, 0xd7, 0xbc, 0xb1, 0xb8, 0xbf, 0xaa, 0xca, 0xbc, 0xb6, 0xa8, 0xce, 0xbb, 0x00};

uint8_t adjustUp[] = {0xc4, 0xfa, 0xb5, 0xc4, 0xcd, 0xb7, 0xb9, 0xfd, 0xb5, 0xcd, 0xa3, 0xac, 0xc7, 0xeb, 0xb5, 0xf7, 0xd5, 0xfb, 0x00
                     };


uint8_t adjustRight[] = {0xc4, 0xfa, 0xb5, 0xc4, 0xcd, 0xb7, 0xb2, 0xbf, 0xb9, 0xfd, 0xd3, 0xda, 0xbf, 0xbf, 0xd3, 0xd2, 0xa3, 0xac, 0xc7, 0xeb, 0xb5, 0xf7, 0xd5, 0xfb, 0xa3, 0xa1, 0x00};

uint8_t adjustLeft[] = {0xc4, 0xfa, 0xb5, 0xc4, 0xcd, 0xb7, 0xb2, 0xbf, 0xb9, 0xfd, 0xd3, 0xda, 0xbf, 0xbf, 0xd7, 0xf3, 0xa3, 0xac, 0xc7, 0xeb, 0xb5, 0xf7, 0xd5, 0xfb, 0xa3, 0xa1, 0x00};

uint8_t failedLocation[] = {0xb6, 0xa8, 0xce, 0xbb, 0xca, 0xa7, 0xb0, 0xdc, 0xa3, 0xac, 0xbc, 0xb4, 0xbd, 0xab, 0xb3, 0xe7, 0xd6, 0xc3, 0x00};

uint8_t successfulLocation[] = {0xb6, 0xa8, 0xce, 0xbb, 0xb3, 0xc9, 0xb9, 0xa6, 0x00};

uint8_t confirmDisFailed[] = {0xbe, 0xe0, 0xc0, 0xeb, 0xb8, 0xa1, 0xb6, 0xaf, 0xbd, 0xcf, 0xb4, 0xf3, 0xa3, 0xac, 0xd5, 0xfd, 0xd4, 0xda, 0xd6, 0xd8, 0xd0, 0xc2, 0xb2, 0xe2, 0xc1, 0xbf, 0xa3, 0xa1, 0x00};

uint8_t cannotConfirmDisHaveToReset[] = {0xb2, 0xe2, 0xbe, 0xe0, 0xca, 0xa7, 0xb0, 0xdc, 0xa3, 0xac, 0xbc, 0xb4, 0xbd, 0xab, 0xb3, 0xe7, 0xd6, 0xc3, 0x00};

uint8_t successfulConfirmDis[] = {0xb2, 0xe2, 0xbe, 0xe0, 0xb3, 0xc9, 0xb9, 0xa6, 0xa3, 0xa1, 0x00};

uint8_t failedTransverseScan[] = {0xba, 0xe1, 0xcf, 0xf2, 0xcb, 0xf8, 0xb6, 0xa8, 0xca, 0xa7, 0xb0, 0xdc, 0xa3, 0xac, 0xbc, 0xb4, 0xbd, 0xab, 0xb3, 0xe7, 0xd6, 0xc3, 0x00};

uint8_t leftSuccessful[] = {0xd2, 0xd1, 0xc8, 0xb7, 0xb6, 0xa8, 0xd7, 0xf3, 0xb2, 0xe0, 0xbd, 0xe7, 0xcf, 0xde, 0xa3, 0xa1, 0x00};

uint8_t rightSuccessful[] = {0xd3, 0xd2, 0xb2, 0xe0, 0xcb, 0xf8, 0xb6, 0xa8, 0xb3, 0xc9, 0xb9, 0xa6, 0xa3, 0xa1, 0x00};

float standardDistance = 0.0;

int flag = 0;

bool potentiometerFlag = true;

int topBottomAngle;
int bottomServoLeftDeg;
int bottomServoRightDeg;

int confirmDistanceFailuresTimes = 0;

bool isinterrupt = false;

void(* resetFunc) (void) = 0;


int readPotentiometer(int potentiometerPin = A0, int delayTime = 0) {
  int val = analogRead(potentiometerPin);
  delay(delayTime);
  return val;
}

void servopulse(int servopin, int angle)
{
  int pulsewidth = (angle * 11) + 500;
  digitalWrite(servopin, HIGH);
  delayMicroseconds(pulsewidth);
  digitalWrite(servopin, LOW);
  delayMicroseconds(20000 - pulsewidth);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  syn6288_init();
  oled_init();
  oled_draw("It is switched on and working!", 0);
  ut_hc_sr04.init();
  delay(1000);
  syn6288_play(tips, sizeof(tips));
  oled_draw("Positioning the head!", 0);
  pinMode(bottomServoPin, OUTPUT);
  servopulse(bottomServoPin, 90);
  topBottomAngle = TopServoInit();
  if (!topBottomAngle)
  {
    isinterrupt = true;
    delay(500);
    resetFunc();
    return;
  }
  delay(1000);

  syn6288_play(successfulLocation, sizeof(successfulLocation));
  delay(1500);
  oled_draw("Measuring distance!", 0);
  float conDisRet = confirmDis();

  if (!conDisRet)
  {
    isinterrupt = true;
    delay(500);
    resetFunc();
    return;
  }
  else
  {
    standardDistance = conDisRet;
  }

  bottomServoLeftDeg = BottomServoInit();
}
void loop()
{
  if (isinterrupt)
  {
    return;
  }
  for (int i = bottomServoRightDeg; i >= 90; i -= 5) {
    delay(100);
    servopulse(bottomServoPin, i);
  }
  servopulse(bottomServoPin, 90);
  float distance = 0.0;
  distance = ut_hc_sr04.getDistance(false, 100);
  if ((distance < 5) || ((distance - standardDistance) >= 30))
  {
    flag++;
    if (flag >= 5)
    {
      oled_draw("Please note that your head is too low!", 0);
      Serial.println("Adjust the upper and lower bearing.");
      syn6288_play(adjustUp, sizeof(adjustUp));
      digitalWrite(ledPin, HIGH);
      delay(3000);
    }
  }
  else
  {
    flag = 0;
    oled_draw("Monitoring, sitting normally, please keep it!", 0);
    digitalWrite(ledPin, LOW);
  }
  bottomServoSweep();
  int pVal = readPotentiometer(potentiometerPin, 0);
  if (pVal == 0) setVol(0);
  else if (pVal <= 64) setVol(1);
  else if (pVal <= 128) setVol(2);
  else if (pVal <= 192) setVol(3);
  else if (pVal <= 256) setVol(4);
  else if (pVal <= 320) setVol(5);
  else if (pVal <= 384) setVol(6);
  else if (pVal <= 448) setVol(7);
  else if (pVal <= 512) setVol(8);
  else if (pVal <= 576) setVol(9);
  else if (pVal <= 640) setVol(10);
  else if (pVal <= 704) setVol(11);
  else if (pVal <= 768) setVol(12);
  else if (pVal <= 832) setVol(13);
  else if (pVal <= 896) setVol(14);
  else if (pVal <= 960) setVol(15);
  else setVol(16);
}
float confirmDis()
{
  float confirmDistanceArr[5] = {0.0};
  int sum = 0;
  for (int i = 0; i < 5; i++)
  {
    confirmDistanceArr[i] = ut_hc_sr04.getDistance(false, 100);
    Serial.print(confirmDistanceArr[i]);
    Serial.print(",");
    for (int j = 0; j < i; j++)
    {
      if ((confirmDistanceArr[i] - confirmDistanceArr[j] > 10) ||
          (confirmDistanceArr[j] - confirmDistanceArr[i] > 10))
      {
        if (confirmDistanceFailuresTimes >= 3)
        {
          syn6288_play(cannotConfirmDisHaveToReset, sizeof(cannotConfirmDisHaveToReset));
          oled_draw("Distance measurement failed. Reset is imminent!", 0);
          delay(3000);
          return 0;
        }
        syn6288_play(confirmDisFailed, sizeof(confirmDisFailed));
        delay(3500);
        confirmDistanceFailuresTimes++;
        float ret = confirmDis();
        return ret;
      }
    }
    sum += confirmDistanceArr[i];
  }
  syn6288_play(successfulConfirmDis, sizeof(successfulConfirmDis));
  delay(1500);
  return sum / 5;
}
int TopServoInit() {
  pinMode(topServoPin, OUTPUT);
  int init_degree = 65;
  servopulse(topServoPin, init_degree);
  delay(1000);

  int topBottomAngle = 0;
  float distance = 0.0;
  for (int i = 0; i < 5; i++)
    standardDistance = ut_hc_sr04.getDistance(true, 0);
  for (int i = init_degree; i >= 0; i -= 5)
  {
    servopulse(topServoPin, i);
    Serial.println(i);
    distance = ut_hc_sr04.getDistance(true, 0);
    if ((distance < 0) || ((distance - standardDistance) >= 30))
    {
      Serial.println("located head.");

      for (int k = i; k < i + 30; k++)
      {
        servopulse(topServoPin, k);
        delay(100);
        int d = ut_hc_sr04.getDistance(true, 0);
        if ((distance > 0) && ((d - standardDistance) <= 10))
        {
          topBottomAngle = k;
          topBottomAngle += 10;
          servopulse(topServoPin, topBottomAngle);
          Serial.println(topBottomAngle);
          break;
        }
        if (k >= i + 29)
        {
          Serial.println("Location failed!");
          syn6288_play(failedLocation, sizeof(failedLocation));
          oled_draw("Failed to locate the head. Reset is imminent!", 0);
          delay(2000);
          return 0;
        }
      }
      break;
    }
    delay(100);
    standardDistance = distance;
    if (i == 0)
    {
      Serial.println("Location failed!");
      syn6288_play(failedLocation, sizeof(failedLocation));
      oled_draw("Failed to locate the head. Reset is imminent!", 0);
      delay(2000);
      return 0;
    }
  }
  return topBottomAngle;
}
int BottomServoInit() {
  int bottomServoInitDeg = 90;
  servopulse(bottomServoPin, bottomServoInitDeg);
  bottomServoLeftDeg = 0;
  int stDis = standardDistance;
  float dis = 0.0;
  //======================================================================LEFT======================================================================
  for (int i = bottomServoInitDeg; i >= 20; i -= 5) {
    servopulse(bottomServoPin, i);
    Serial.println(i);
    dis = ut_hc_sr04.getDistance(true, 0);
    if ((dis < 0) || ((dis - stDis) >= 30)) {
      Serial.println("Lateral locking.");
      for (int k = i; k < i + 30; k++) {
        servopulse(bottomServoPin, k);
        delay(100);
        int d = ut_hc_sr04.getDistance(true, 0);
        if ((dis > 0) && ((d - standardDistance) <= 10))
        {
          bottomServoLeftDeg = k;
          servopulse(bottomServoPin, bottomServoLeftDeg);
          Serial.println(bottomServoLeftDeg);
          syn6288_play(leftSuccessful, sizeof(leftSuccessful));
          delay(2500);
          break;
        }
        if (k >= i + 29)
        {
          Serial.println("Failed Transverse Scan!");
          syn6288_play(failedTransverseScan, sizeof(failedTransverseScan));
          oled_draw("Failed transverse scan. Reset is imminent!", 0);
          delay(4000);
          resetFunc();
          return 0;
        }
      }
      break;
    }
    stDis = dis;
    delay(200);
    if (i == 20)
    {
      Serial.println("Failed Transverse Scan!");
      syn6288_play(failedTransverseScan, sizeof(failedTransverseScan));
      oled_draw("Failed transverse scan. Reset is imminent!", 0);
      delay(4000);
      resetFunc();
      return 0;
    }
  }
  for (int p = bottomServoLeftDeg; p <= 90; p += 5) {
    servopulse(bottomServoPin, p);
    delay(100);
  }
  servopulse(bottomServoPin, bottomServoInitDeg);
  //======================================================================RIGHT======================================================================
  for (int i = bottomServoInitDeg; i <= 160  ; i += 5) {
    servopulse(bottomServoPin, i);
    Serial.println(i);
    dis = ut_hc_sr04.getDistance(true, 0);
    if ((dis < 0) || ((dis - stDis) >= 30)) {
      Serial.println("Lateral locking.");
      for (int k = i; k > i - 30; k--) {
        servopulse(bottomServoPin, k);
        delay(100);
        int d = ut_hc_sr04.getDistance(true, 0);
        if ((dis > 0) && ((d - standardDistance) <= 10))
        {
          bottomServoRightDeg = k;
          servopulse(bottomServoPin, bottomServoRightDeg);
          Serial.println(bottomServoRightDeg);
          syn6288_play(rightSuccessful, sizeof(rightSuccessful));
          delay(2500);
          break;
        }
        if (k <= i - 29)
        {
          Serial.println("Failed Transverse Scan!");
          syn6288_play(failedTransverseScan, sizeof(failedTransverseScan));
          oled_draw("Failed transverse scan. Reset is imminent!", 0);
          delay(4000);
          resetFunc();
          return 0;
        }
      }
      break;
    }
    stDis = dis;
    delay(500);
    if (i == 160)
    {
      Serial.println("Failed Transverse Scan!");
      syn6288_play(failedTransverseScan, sizeof(failedTransverseScan));
      oled_draw("Failed transverse scan. Reset is imminent!", 0);
      delay(4000);
      resetFunc();
      return 0;
    }
  }
  return bottomServoLeftDeg;
}
void bottomServoSweep(void) {
  servopulse(bottomServoPin, 90);
  for (int k = 90; k >= bottomServoLeftDeg; k -= 5) {
    delay(300);
    servopulse(bottomServoPin, k);
  }
  servopulse(bottomServoPin, bottomServoLeftDeg);
  int flag = 0;
  for (int j = 0; j < 5; j++) {
    float dist = 0.0;
    dist = ut_hc_sr04.getDistance(false, 100);
    if ((dist < 5) || ((dist - standardDistance) >= 30))
    {
      flag++;
      if (flag >= 5)
      {
        oled_draw("Please note that your head is on right!", 0);
        Serial.println("Adjust on left bearing.");
        syn6288_play(adjustRight, sizeof(adjustRight));
        digitalWrite(ledPin, HIGH);
        delay(800);
        digitalWrite(ledPin, LOW);
        delay(800);
        digitalWrite(ledPin, HIGH);
        delay(800);
        digitalWrite(ledPin, LOW);
        delay(3000);
      }
    }
    else
    {
      flag = 0;
      oled_draw("Monitoring, sitting normally, please keep it!", 0);
      digitalWrite(ledPin, LOW);
    }
  }
  //----------------------------------------------------------------------Turn Right--------------------------------------------------------------------
  for (int m = bottomServoLeftDeg; m <= bottomServoRightDeg; m += 5) {
    delay(300);
    servopulse(bottomServoPin, m);
  }
  servopulse(bottomServoPin, bottomServoRightDeg);
  flag = 0;
  for (int j = 0; j < 5; j++) {
    float dist = 0.0;
    dist = ut_hc_sr04.getDistance(false, 100);
    if ((dist < 5) || ((dist - standardDistance) >= 30))
    {
      flag++;
      if (flag >= 5)
      {
        oled_draw("Please note that your head is on left!", 0);
        Serial.println("Adjust on right bearing.");
        syn6288_play(adjustLeft, sizeof(adjustLeft));
        digitalWrite(ledPin, HIGH);
        delay(800);
        digitalWrite(ledPin, LOW);
        delay(800);
        digitalWrite(ledPin, HIGH);
        delay(800);
        digitalWrite(ledPin, LOW);
        delay(3000);
      }
    }
    else
    {
      flag = 0;
      oled_draw("Monitoring, sitting normally, please keep it!", 0);
      digitalWrite(ledPin, LOW);
    }
  }
}
