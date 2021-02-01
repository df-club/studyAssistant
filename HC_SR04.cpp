/*
   Latest Update: 6/17/2020
   Author: OscarXia
*/
#include "HC_SR04.h"
#include <Arduino.h>

HC_SR04::HC_SR04(int TRIGPIN, int ECHOPIN) {
  this -> trigPin = TRIGPIN;
  this -> echoPin = ECHOPIN;
}

void HC_SR04::init() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

double HC_SR04::getDistance(bool isSerialOutput = false, int delayTime = 1000) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPin, LOW);

  double distanceInCm = pulseIn(echoPin, HIGH) / 58.0;
  distanceInCm = (int(distanceInCm * 100.0)) / 100.0;
  if (isSerialOutput) {
    Serial.print("Distance:");
    Serial.print(distanceInCm);
    Serial.print("cm");
    Serial.println();
  }
  delay(delayTime);
  return distanceInCm;

}
