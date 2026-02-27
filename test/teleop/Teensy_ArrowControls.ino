// THIS CODE ALLOWS ARROW KEY CONTROL OF THE MOTORS

#include "motors.hpp"

Motor motor;

const int SPEED = 255;   // 0–255
unsigned long lastCmd = 0;
const unsigned long TIMEOUT = 3000; // ms

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    lastCmd = millis();

    if (cmd == "FWD") {
      motor.Drive(SPEED, SPEED);
    }
    else if (cmd == "REV") {
      motor.Drive(-SPEED, -SPEED);
    }
    else if (cmd == "LEFT") {
      motor.Drive(-SPEED, SPEED);
    }
    else if (cmd == "RIGHT") {
      motor.Drive(SPEED, -SPEED);
    }
    else if (cmd == "STOP") {
      motor.Drive(0, 0);
    }
  }

  // safety stop if commands stop coming
  if (millis() - lastCmd > TIMEOUT) {
    motor.Drive(0, 0);
  }
}
