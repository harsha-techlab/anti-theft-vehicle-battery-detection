/*
  Anti-Theft Vehicle Battery Detection System
  RECEIVER Arduino Uno — owner location

  LoRa E32 serial pins: module TXD -> Arduino D10, RXD <- Arduino D11
*/

#include <SoftwareSerial.h>

SoftwareSerial LoRa(10, 11); // Arduino RX, TX

#define BUZZER_PIN 8

bool batteryLost = false;

void beepBuzzer(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);
  }
}

void setup() {
  Serial.begin(9600);
  LoRa.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Receiver Ready");
}

void loop() {
  // Keep the receiver buzzer active during the battery-loss state.
  if (batteryLost) {
    digitalWrite(BUZZER_PIN, HIGH);
  }

  if (LoRa.available()) {
    String msg = LoRa.readStringUntil('\n');
    msg.trim();

    Serial.print("Received: ");
    Serial.println(msg);

    if (msg == "ALERT") {
      Serial.println("Alert! Beeping 5 times.");
      // Avoid a short alert beep overriding the continuous battery alarm.
      if (!batteryLost) {
        beepBuzzer(5);
      }
    }

    if (msg == "BATTERY_LOST") {
      Serial.println("Battery removed! Continuous alarm!");
      batteryLost = true;
      digitalWrite(BUZZER_PIN, HIGH);
    }

    if (msg == "BATTERY_OK") {
      Serial.println("Battery reconnected. Alarm stopped.");
      batteryLost = false;
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

  delay(100);
}
