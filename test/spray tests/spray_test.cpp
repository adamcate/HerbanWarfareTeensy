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
#include "pins.h"

using namespace std::chrono_literals;
using namespace TeensyTimerTool;

const auto deltaT = 37.5ms;
// hacky solution for now bc converting from chrono_literals SUCKS :( just make sure they match
const float deltaTS = 37.5f / 1000.f;

#define DRIVE_TIME 1000
#define SPRAY_TIME 1000

Motor myMotors{};
IMU myIMU{65535, deltaTS};

PeriodicTimer t1(RTC); // this uses the real time clock to trigger interrupts, integrating values etc.


#define SPRAY_DURATION_MS 2500  // run motors for 2.5 seconds

Motor motors;         // Create motor object

unsigned long sprayStart = 0;

bool isSpraying = true;
void setup() {
  //t1.begin([] {myIMU.Update();}, deltaT); // SHOULD update the IMU data and integrate every 25ms
  pinMode(PUMP_ENABLE, OUTPUT);
  pinMode(PUMP_STATUS_LED, OUTPUT);
  digitalWrite(PUMP_ENABLE, LOW);
  //Serial.begin(115200);
  //Serial.println("Teensy ready");
  delay(5000);
}

void loop() {
  for(int i = 0; i < 10; ++i)
  {
    digitalWrite(PUMP_ENABLE, HIGH);
    delay(2000);
    digitalWrite(PUMP_ENABLE, LOW);
    delay(3000);
  }
    /*// Check for serial input
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
  }*/
}