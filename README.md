<div align="center">

# Smart Agriculture Arduino

Arduino-based smart agriculture prototype for environmental monitoring and automated motor control.

![Arduino](https://img.shields.io/badge/Arduino-Prototype-00878F?style=flat-square&logo=arduino&logoColor=white)
![DHT11](https://img.shields.io/badge/Sensor-DHT11-C9A227?style=flat-square)
![HC--SR04](https://img.shields.io/badge/Sensor-HC--SR04-C9A227?style=flat-square)

</div>

## Overview

This project demonstrates a compact smart agriculture automation system built with Arduino. It monitors temperature, humidity and distance data, displays real-time values on an LCD and controls a stepper motor automatically or manually.

## Features

- Temperature and humidity monitoring with DHT11
- Distance measurement with HC-SR04
- Real-time 16x2 I2C LCD output
- Automatic stepper motor activation below the humidity threshold
- Manual forward and reverse motor control using a joystick
- Serial monitor status messages
- Demonstration video included

## Hardware

- Arduino-compatible board
- DHT11 temperature and humidity sensor
- HC-SR04 ultrasonic distance sensor
- 28BYJ-48 stepper motor and driver
- 16x2 I2C LCD
- Joystick module
- Jumper cables and breadboard

## Pin Configuration

| Component | Pin |
|---|---|
| DHT11 Data | D2 |
| HC-SR04 Trig | D6 |
| HC-SR04 Echo | D7 |
| Stepper Motor | D8, D10, D9, D11 |
| Joystick Y | A1 |
| Joystick Button | D3 |
| I2C LCD | Address `0x27` |

## Project Files

```text
smart-agriculture-arduino/
├── smart-agriculture.ino
├── demo.mp4
└── README.md
```

## Required Libraries

- `Wire`
- `LiquidCrystal_I2C`
- `DHT sensor library`
- `Stepper`

Install the required libraries through the Arduino IDE Library Manager before compiling.

## Usage

1. Connect the components according to the pin table.
2. Open `smart-agriculture.ino` in Arduino IDE.
3. Select the correct board and port.
4. Install the required libraries.
5. Upload the sketch.
6. Monitor live values on the LCD or Serial Monitor.

The default humidity threshold is:

```cpp
const float nemEsik = 40.0;
```

## Author

Developed by **Yiğit Erdoğan** under **DevcodeTrek**.
