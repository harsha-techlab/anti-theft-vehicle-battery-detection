
# 🚗 Anti-Theft Vehicle Battery Detection System

A wireless security system designed to detect suspicious activity near a vehicle battery and alert the owner using LoRa communication.

## 📌 Project Overview

This project uses two Arduino Uno boards to monitor a vehicle battery area and transmit alerts wirelessly to a receiver unit.

The transmitter monitors motion, vibration, and battery voltage. When suspicious activity or a battery disconnection condition is detected, the system activates a local buzzer and sends an alert to the receiver.

## ✨ Features

- Motion detection using an HC-SR505 PIR sensor
- Vibration detection using an SW-420 sensor
- Battery voltage monitoring
- Combined motion-and-vibration detection to reduce false alarms
- Wireless communication using LoRa E32-433T20D modules
- Local and remote buzzer alerts
- Battery disconnection detection using a 10 V threshold
- No Wi-Fi or internet connection required for the LoRa link

## 🧰 Components Used

| Component | Quantity |
|---|---:|
| Arduino Uno | 2 |
| LoRa E32-433T20D module | 2 |
| HC-SR505 PIR sensor | 1 |
| SW-420 vibration sensor | 1 |
| Voltage sensor module | 1 |
| Active buzzer | 2 |
| Power supply, jumper wires and other accessories | As required |

## ⚙️ Working Principle

### 1. Normal Monitoring
The transmitter continuously reads the PIR sensor, vibration sensor, and battery voltage. The buzzers remain silent under normal conditions.

### 2. Motion and Vibration Detection
When both the PIR sensor and vibration sensor detect activity together, the transmitter activates its buzzer for five beeps and sends an `ALERT` message through LoRa.

The receiver gets the message and activates its buzzer for five beeps.

### 3. Battery Disconnection Detection
The voltage sensor monitors the battery voltage. When the measured voltage falls below the configured 10 V threshold, the transmitter sends `BATTERY_LOST` and activates a continuous buzzer alarm.

The receiver also activates its continuous alarm.

### 4. Battery Reconnection
When the measured voltage returns to at least 10 V after a battery-loss condition, the transmitter sends `BATTERY_OK` and stops its buzzer. The receiver stops its buzzer after receiving the message.

## 📡 System Architecture

Vehicle Battery Area
→ Sensors
→ Arduino Uno Transmitter
→ LoRa E32-433T20D
→ LoRa E32-433T20D
→ Arduino Uno Receiver
→ Owner Alert Buzzer

## 💻 Software and Communication

- **Programming language:** Arduino C/C++
- **Development environment:** Arduino IDE
- **Wireless communication:** LoRa, 433 MHz
- **Serial communication:** SoftwareSerial at 9600 baud

## 📁 Repository Structure

```text

anti-theft-vehicle-battery-detection/
├── README.md
├── transmitter/
│   └── transmitter.ino
├── receiver/
│   └── receiver.ino
└── docs/
    └── Anti-Theft vehicle battery detection system.pdf
    

```

*Add the folders and images when you have those files ready.*

## 🧪 Testing

The documented testing procedure includes:

- Testing the PIR and vibration sensors individually
- Testing combined motion and vibration detection
- Monitoring voltage readings through the Serial Monitor
- Simulating a battery disconnection using a test setup
- Checking LoRa alert reception and buzzer responses

## 🎯 Applications

- Vehicle battery security demonstrations
- Wireless tampering-alert prototypes
- Embedded systems and IoT learning projects

## 🚀 Future Improvements

- Add a display for sensor and battery status
- Add event logging
- Improve alert reliability and power management
- Evaluate additional communication and notification options

## 👨‍💻 Project Information

**Project:** Anti-Theft Vehicle Battery Detection System  
**Controller:** Arduino Uno  
**Communication:** LoRa E32-433T20D  
**Status:** Prototype project

---

> This is an educational prototype. Test with a suitable, isolated test setup and get qualified supervision before connecting it to a vehicle battery.
