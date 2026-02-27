// THIS CODE TESTS THE COMMUNICATION BETWEEN PI AND AN ARDUINO UNO R3
// BUILTIN LED STATUS IS BASED ON ARROW KEY COMMANDS SEND FROM PI TO ARDUINO

unsigned long lastCmd = 0;
const unsigned long TIMEOUT = 3000; // ms

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    lastCmd = millis();

    if (cmd == "FWD") {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print("Received command: ");
      Serial.println(cmd);
    }
    else if (cmd == "REV") {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print("Received command: ");
      Serial.println(cmd);
    }
    else if (cmd == "LEFT") {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print("Received command: ");
      Serial.println(cmd);
    }
    else if (cmd == "RIGHT") {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print("Received command: ");
      Serial.println(cmd);
    }
    else if (cmd == "STOP") {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print("Received command: ");
      Serial.println(cmd);
    }
  }

  // safety stop if commands stop coming
  if (millis() - lastCmd > TIMEOUT) {
    Serial.print("Received command: ");
    Serial.println("SAFETY STOP");
  }
}