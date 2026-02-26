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

const auto deltaT = 37.5ms;
// hacky solution for now bc converting from chrono_literals SUCKS :( just make sure they match
const float deltaTS = 37.5f / 1000.f;

#define DRIVE_TIME 1000
#define SPRAY_TIME 1000

Queue queue{};
Queue avoidQueue{};

const Task _init_tasks[MAX_TASKS] = {DRIVE_T(0,0,255,255,2000),DRIVE(255,255,DRIVE_TIME),HALT(2000),DRIVE(255,-255,200),EMPTY(),EMPTY(),EMPTY(),EMPTY(),EMPTY()};

Motor myMotors{};
IMU myIMU{65535, deltaTS};

PeriodicTimer t1(RTC); // this uses the real time clock to trigger interrupts, integrating values etc.


#define SPRAY_DURATION_MS 2500  // run motors for 2.5 seconds

Motor motors;         // Create motor object
bool spraying = false; // flag to know if motors are running
unsigned long sprayStart = 0;

void setup() {
  //t1.begin([] {myIMU.Update();}, deltaT); // SHOULD update the IMU data and integrate every 25ms
  pinMode(PUMP_ENABLE, OUTPUT);
  pinMode(PUMP_STATUS_LED, OUTPUT);
  digitalWrite(PUMP_ENABLE, LOW);
  for(int i = 0; i < MAX_TASKS; ++i) queue.pushToNextEmpty(_init_tasks[i]);
  Serial.begin(115200);
  Serial.println("Teensy ready");
}

void loop() {
    // Check for serial input
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();  // remove any newline / whitespace

    if (cmd == "SPRAY" && !spraying) {
      spraying = true;
      sprayStart = millis();

      // Run motors (example: forward at half speed)
      motors.Drive(255, 255);

      Serial.println("SPRAYING");
    }
  }

  // Stop motors after SPRAY_DURATION_MS
  if (spraying && millis() - sprayStart >= SPRAY_DURATION_MS) {
    motors.Drive(0, 0);  // stop motors
    spraying = false;
    Serial.println("DONE");
  }
}