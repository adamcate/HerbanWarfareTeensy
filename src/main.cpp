#include <Arduino.h>
#include "motors.hpp"
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20649.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Motor myMotors{};

void setup() {

}

void loop() {
  myMotors.Drive(255.f, 255.f);
  delay(5000);
  myMotors.Drive(127.f, 127.f);
  delay(5000);
  myMotors.Drive(-255.f, -255.f);
  delay(5000);
}