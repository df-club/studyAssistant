/*
   Latest Update: 6/17/2020
   Author: OscarXia
*/
#ifndef HC_SR04_H
#define HC_SR04_H

class HC_SR04
{
  public:
    HC_SR04(int TRIGPIN, int ECHOPIN);
    void init();
    double getDistance(bool isSerialOutput = false, int delayTime = 1000);
  private:
    int trigPin;
    int echoPin;

};


#endif
