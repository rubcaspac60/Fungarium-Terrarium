//============================================================================//
/*!
 *      ___        ___       _   _                _ _            _           
 *     |  _|  /\  |_  |     | | | |              (_) |        /\| |/\        
 *     | |   /  \   | |_   _| |_| |__   ___  _ __ _| |_ _   _ \ ` ' / ______ 
 *     | |  / /\ \  | | | | | __| '_ \ / _ \| '__| | __| | | |_     _|______|
 *     | | / ____ \ | | |_| | |_| | | | (_) | |  | | |_| |_| |/ , . \        
 *     | |/_/    \_\| |\__,_|\__|_| |_|\___/|_|  |_|\__|\__, |\/|_|\/        
 *     |___|      |___|                                  __/ |               
 *                                                      |___/                
 *
 * @author  Syed Asad Amin
 * @date    Dec 19th, 2022
 * @file    Nectar.ino
 * @version v1.2.1 -- CHANGELOG
 *              | v1.0.0 - Initial commit with base code
 *              | v1.1.0 - Added camera module support with SD card
 *              | v1.2.0 - ADded soil moisture sensor support
 *              | v1.2.1 - Added gas moisture sensor support
 * 
 * @details This applicaiton is written in C++ language using Arduino core
 *          framework for ESP32 platform
 * 
 *          This application is part of project 'NECTAR'
 * 
 *          Project 'NECTAR' is based on several gas sensor and soil moisture
 *          sensor to take reading of the greenhouse environment periodically
 * 
 * @note    IMPORTANT:
 *              - Select board "AI Thinker ESP32-CAM"
 *              - GPIO 0 must be connected to GND to upload sketch
 *              - Press RST button on board to upload the sketch
 * 
 * @sa      /doc/ProjectNectar.pptx
 *
 */
//============================================================================//

//===== INCLUDES =============================================================//
#include <Arduino.h>
#include <WiFi.h>

#include "camera.h"
#include "sensor.h"
//============================================================================//

//===== CONSTANTS AND VARIABLES ==============================================//
// Hearteat LED
static const uint8_t LED_HEARTBEAT          = 16;

// Activity counter
static const uint32_t BASE_TIME_INTERVAL    = 1000;                             // 1 sec or 1000 ms
static const uint32_t SENS_READ_INTERVAL    = 60 * BASE_TIME_INTERVAL;          // Keeping the readout time
static const uint32_t CAM_PICTURE_INTERVAL  = 60 * BASE_TIME_INTERVAL;          // and camera picture time sperate

// WiFi
static const uint8_t WIFI_SSID[]            = "";
static const uint8_t WIFI_PASS[]            = "";

// H/W Timer
static hw_timer_t *timer                    = NULL;
static portMUX_TYPE spinLock                = portMUX_INITIALIZER_UNLOCKED;

// Flags
bool readSensorFlag                         = false;
bool takePictureFlag                        = false;
//============================================================================//

//===== EVENS AND ISR ========================================================//
void IRAM_ATTR onTimerTick(void) {
    static uint32_t hearbeatCounter = 0;
    static uint32_t sensorReadoutCounter = 0;
    static uint32_t cameraPictureCounter = 0;
    
    portENTER_CRITICAL_ISR(&spinLock);
    
    hearbeatCounter++;
    if(hearbeatCounter >= 1000) {
        digitalWrite(LED_HEARTBEAT, !digitalRead(LED_HEARTBEAT));
        hearbeatCounter = 0;
    }

    sensorReadoutCounter++;
    if(sensorReadoutCounter >= SENS_READ_INTERVAL) {
        readSensorFlag = true;
        sensorReadoutCounter = 0;
    }

    cameraPictureCounter++;
    if(cameraPictureCounter >= CAM_PICTURE_INTERVAL) {
        takePictureFlag = true;
        cameraPictureCounter = 0;
    }

    portEXIT_CRITICAL_ISR(&spinLock);
}
//============================================================================//

//===== FUNCTION DEFINITIONS =================================================//
void initGPIO(void) {
    pinMode(LED_HEARTBEAT, OUTPUT);
    digitalWrite(LED_HEARTBEAT, LOW);
}

void initSerial(void) {
    Serial.begin(115200);
    while(!Serial);
}

void initTimer(void) {
    timer = timerBegin(1, 80, true);
    timerAttachInterrupt(timer, &onTimerTick, true);
    timerAlarmWrite(timer, 1000, true);
    timerAlarmEnable(timer);
}

void setup() {
    initGPIO();
    initSerial();
    initTimer();

    initSensor();
    initCamera();
}

void loop() {
    if(readSensorFlag) {
        readSoilSensor();
        readGasSensor();
    }

    if(takePictureFlag) {
        takePicture();
    }

    // To use sensor data to upload via wifi
    uint32_t NO2 = sensorData.NO2;
    uint32_t C2H5CH = sensorData.C2H5CH;
    uint32_t VOC = sensorData.VOC;
    uint32_t CO = sensorData.CO;
    float CO2 = sensorData.CO2_1;
    float temperature = sensorData.temperature_1;
    float humidity = sensorData.humidity_1;
    float volt1 = sensorData.voltage1;
    float volt2 = sensorData.voltage2;
    float volt3 = sensorData.voltage3;
}
//============================================================================//
