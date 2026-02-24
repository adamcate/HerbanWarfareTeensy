#include <Arduino.h>
#include "motors.hpp"
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20649.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Encoder.h>
#include <imu.hpp>
#include <chrono>
#include <TeensyTimerTool.h>

using namespace std::chrono_literals;
using namespace TeensyTimerTool;
const auto deltaT = 25ms;
// hacky solution for now bc converting from chrono_literals SUCKS :( just make sure they match
const float deltaTS = 25.f / 1000.f;

Motor myMotors{};
IMU myIMU{65535, deltaTS};

PeriodicTimer t1(RTC); // this uses the real time clock to trigger interrupts, integrating values etc.

void setup() {
  t1.begin([] {myIMU.Update();}, deltaT); // SHOULD update the IMU data and integrate every 25ms, we'll see lol
}

void loop() {
}