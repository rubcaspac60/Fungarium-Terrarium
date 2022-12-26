# Project Nectar - Powered by AI Thinker ESP32 CAM module

## INTRODUCTION
Project 'NECTAR' is based on several gas sensor and soil moisture sensor to take
reading of the greenhouse environment periodically. ESP32-CAM is used to take
picture periodically and is saved into SD cards as well for visual monitoring.

## INSTALLATIONS
Arduino IDE is required along with ESP32 board installed on it. Use following
method to instlal ESP32 board

- Step1: Enter following link into the File > Preference > Additional Boards
Manager URL

```
https://dl.espressif.com/dl/package_esp32_index.json
```

- Step2: Go to Tools > Board > Board Manager. Search for ESP32 and install it
- Step3: Select AI Thinker ESP32-Cam module fomr Tools > Board > ESP32 Arduino
- Step4: Select COMM port from the Tools > Port
- Step4: Compile and upload

Note:
This project was primarily developed on VS Code IDE with C++ and Arduino
extensions.

## DEPENDENCIES
Following arduino libraries are neded as part of this project dependency

- ✔️ Seeed_Arduino_Multigas by Seeed Studios
- ✔️ Arduino-i2c-scd30 by Sensirion

To install the above mentioned libraries simply go to Documents > Arduino >
libraries folder and run the following commands

```
git clone https://github.com/Seeed-Studio/Seeed_Arduino_MultiGas.git
git clone https://github.com/Sensirion/arduino-i2c-scd30.git
git clone https://github.com/Sensirion/arduino-core.git
```

To run the above commands GIT is required to be installed on the system.
Otherwise go to those links and download the library as zip file and place it
inside the libraries folder.

## HARDWARE
Following are the required hardware components needed for this application

| S. No. | Item | Description |
|:-------|:-----|:------------|
| 1 | [ESP32-CAM](docs/datasheets/ESP32-CAM.pdf) | Main compute module of the project by AI Thinker |
| 2 | OV2640 Camera | Camera module norammly comes with ESP32-CAM module |
| 3 | Soil Sensor | Capacitive Soil Moisture Sensor by DF Robots |
| 4 | Gas Sensor | Multichannel gas sensor by Seeed and SCD30 by Seed and Sensirion |

Important Links:

- [Capacitive Soil Moisture Sensor & Calibration](https://makersportal.com/blog/2020/5/26/capacitive-soil-moisture-calibration-with-arduino)
- [Multichanlled Gas Sensor](https://wiki.seeedstudio.com/Grove-Multichannel-Gas-Sensor-V2/)
- [SCD30 CO2 Sensor by Seeed](https://wiki.seeedstudio.com/Grove-CO2_Temperature_Humidity_Sensor-SCD30/)
- [SCD30 CO2 Sensor by Sensirion](https://sensirion.com/de/produkte/katalog/SCD30/)

## CONNECTIONS

- See block diagram [here](docs/ProjectNectar.pptx)

![ESP32-CAM Pinout](docs/ESP32_CAM_Pinout.png)

| ESP32-CAM | Sensor Modules |
|:----------|:---------------|
| GPIO12 | Soil Sensor 1 |
| GPIO13 | Soil Sensor 2 |
| GPIO15 | Soil Sensor 3 |
| GPIO 2 | I2C SDA PIN for all gas sensor |
| GPIO 4 | I2C SCL PIN for all gas sensor |

## USAGE

Simply upload the program using Arduino IDE
