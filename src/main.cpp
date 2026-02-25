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
#include <algorithm>
#include "queue.hpp"
#include "pins.h"

using namespace std::chrono_literals;
using namespace TeensyTimerTool;

const auto deltaT = 5ms;
// hacky solution for now bc converting from chrono_literals SUCKS :( just make sure they match
const float deltaTS = 5.f / 1000.f;

#define DRIVE_TIME 3000

Queue queue{};
Queue avoidQueue{};

const Task _init_tasks[MAX_TASKS] = {DRIVE_T(0,0,255,255,2000),DRIVE(255,255,1000),HALT(1000),ROTATE(90),SPRAY(1000),EMPTY(),EMPTY(),EMPTY(),EMPTY()};

Motor myMotors{};
IMU myIMU{65535, deltaTS};

PeriodicTimer t1(RTC); // this uses the real time clock to trigger interrupts, integrating values etc.

void setup() {
  t1.begin([] {myIMU.Update();}, deltaT); // SHOULD update the IMU data and integrate every 25ms
  pinMode(PUMP_ENABLE, OUTPUT);
  digitalWrite(PUMP_ENABLE, LOW);
  for(int i = 0; i < MAX_TASKS; ++i) queue.pushToNextEmpty(_init_tasks[i]);
}

void loop() {
  queue.startFrame();

  queue.executeAction(myMotors, myIMU);

  queue.endFrame();
}