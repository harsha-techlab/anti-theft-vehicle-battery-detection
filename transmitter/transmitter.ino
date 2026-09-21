/*
  Anti-Theft Vehicle Battery Detection System
  TRANSMITTER Arduino Uno — battery/sensor location

  Based on the supplied project documentation.
  LoRa E32 serial pins: module TXD -> Arduino D10, RXD <- Arduino D11
  IMPORTANT: Follow the module manufacturer's voltage/interface requirements.
*/

#include <SoftwareSerial.h>

SoftwareSerial LoRa(10, 11); // Arduino RX, TX

#define PIR_PIN 4
#define VIBR_PIN 3
#define VOLT_PIN A0
#define BUZZER_PIN 7

#define VOLT_RATIO 5.0
#define BATTERY_THRESHOLD 10.0

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

  pinMode(PIR_PIN, INPUT);
  pinMode(VIBR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Transmitter Ready");
}

void loop() {
  int pirVal = digitalRead(PIR_PIN);
  int vibrVal = digitalRead(VIBR_PIN);
  int rawVolt = analogRead(VOLT_PIN);

  // Assumes the voltage-sensor scaling used in the supplied documentation.
  float voltage = (rawVolt / 1023.0) * 5.0 * VOLT_RATIO;

  Serial.print("PIR: ");
  Serial.print(pirVal);
  Serial.print(" VIBR: ");
  Serial.print(vibrVal);
  Serial.print(" VOLT: ");
  Serial.println(voltage);

  // Battery disconnected / voltage below configured threshold.
  if (voltage < BATTERY_THRESHOLD) {
    if (!batteryLost) {
      Serial.println("Battery voltage below threshold!");
    }
    batteryLost = true;
    digitalWrite(BUZZER_PIN, HIGH);
    LoRa.println("BATTERY_LOST");
    delay(500);
    return;
  }

  // Battery voltage recovered after a battery-loss state.
  if (batteryLost) {
    batteryLost = false;
    digitalWrite(BUZZER_PIN, LOW);
    LoRa.println("BATTERY_OK");
    Serial.println("Battery reconnected - buzzer stopped!");
  }

  // Both sensors must be HIGH together to trigger the tampering alert.
  if (pirVal == HIGH && vibrVal == HIGH) {
    Serial.println("ALERT - Motion + Vibration detected TOGETHER!");
    beepBuzzer(5);
    LoRa.println("ALERT");
    delay(2000); // Cooldown to reduce repeated triggers
  }

  delay(300);
}
