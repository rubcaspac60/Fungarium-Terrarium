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
 * @date    Dec 21st, 2022
 * @file    sensor.cpp
 * @version v1.0.0 -- CHANGELOG
 *
 * @details This program is written in C++ language using Arduino framework for
 *          ESP32 platform
 * 
 *          This file deals with the sensor readout for various modules
 *          connected on I2C bus.
 *          These sensor inlcude(s):
 *              - Soil moistuture sensor
 *              - Multichannel gas sensor
 *              - SCD30 CO2 sensor
 * 
 * @sa      TwoWire interface for arduino & /doc/ESP32_CAM_Pinout.png
 *
 */
//============================================================================//

//===== INCLUDES =============================================================//
#include <Arduino.h>
#include <Wire.h>

#include "sensor.h"
#include "Multichannel_Gas_GMXXX.h"
#include "SensirionI2cScd30.h"
//============================================================================//

//===== CONSTANTS AND VARIABLES ==============================================//
// SOIL GPIO PIN
static const uint8_t SOIL_PIN1              = 12;
static const uint8_t SOIL_PIN2              = 13;
static const uint8_t SOIL_PIN3              = 15;

// Software I2C bus
static TwoWire sensorBus = TwoWire(0);
static const uint8_t I2C_SDA                = 2;
static const uint8_t I2C_SCL                = 4;
static const uint32_t I2C_FREQ              = 100e3;

// Multichannel gas Sensor
GAS_GMXXX<TwoWire> gas;

// SCD30 gas sensor
SensirionI2cScd30 scd30;

sensor_data_t sensorData;
//============================================================================//

//===== FUNCTION DEFINITIONS =================================================//
void initSensor(void) {
    memset(&sensorData, 0, sizeof(sensorData));

    sensorBus.begin(I2C_SDA, I2C_SCL, I2C_FREQ);
    
    gas.begin(sensorBus, 0x08);

    scd30.begin(sensorBus, SCD30_I2C_ADDR_61);
    scd30.stopPeriodicMeasurement();
    scd30.softReset();
    scd30.startPeriodicMeasurement(0);
}

void readGasSensor(void) {
    //--------------------------------------------------------------------------
    /* Multichannel gas sensor */
    // Nitrogen Dioxide - NO2
    uint32_t gasNO2 = gas.getGM102B();
    // Ethyl Alcohol - C2H5CH
    uint32_t gasC2H5CH = gas.getGM302B();
    // Volatile Organic Compounds - VOC
    uint32_t gasVOC = gas.getGM502B();
    // Carbon Monooxide - CO
    uint32_t gasCO = gas.getGM702B();

    sensorData.NO2 = gasNO2;
    sensorData.C2H5CH = gasC2H5CH;
    sensorData.VOC = gasVOC;
    sensorData.CO = gasCO;

    Serial.println("Multichannel Gas Sensor Data");
    Serial.printf(" Nitro Dioxide (NO2): %d ppm", gasNO2);
    Serial.printf(" Ethyl Alcohol (C2H5CH): %d ppm", gasC2H5CH);
    Serial.printf(" Volatile Organic Compound (VOC): %d ppm", gasVOC);
    Serial.printf(" Carbon Monooxide (CO): %d ppm", gasCO);
    Serial.println();
    //--------------------------------------------------------------------------

    // WE CANNOT USE BOTH SCD30 SENSOR AT THE SAME TIME ON THE SAME BUS
    // Since the address of SCD30 is ox60 & 0x61 it will cause bus collision
    // during the data transmission.

    //--------------------------------------------------------------------------
    /* SCD30 Sensirion Module */
    // Carbon Dioxide - CO2 & Temperature / Humidity
    float CO2, temperature1, humidity1;
    scd30.blockingReadMeasurementData(CO2, temperature1, humidity1);

    sensorData.CO2_1 = CO2;
    sensorData.temperature_1 = temperature1;
    sensorData.humidity_1 = humidity1;

    Serial.println("SCD30 Sensor (Sensirion)");
    Serial.printf(" Carbon Dioxode (CO2): %0.3f", CO2);
    Serial.printf(" Temperature (C): %0.3f", temperature1);
    Serial.printf(" Humidity (gm3): %0.3f", humidity1);
    Serial.println();
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    /* SCD30 Seeed Module */
    // Carbon Dioxide - CO2 & Temperature / Humidity
    // float co2, temperature2, humidity2;
    // scd30.blockingReadMeasurementData(co2, temperature1, humidity1);

    // Serial.println("SCD30 Sensor (Sensirion)");
    // Serial.printf(" Carbon Dioxode (CO2): %0.3f", co2);
    // Serial.printf(" Temperature (C): %0.3f", temperature2);
    // Serial.printf(" Humidity (gm3): %0.3f", humidity2);
    // Serial.println();
    //--------------------------------------------------------------------------
}

void readSoilSensor(void) {
    // Reading the analog value and converting into voltage reading.
    // IMPORTANT NOTE:
    //  - Analog resolution: 12 bit default
    //  - Analog reference: 3.3V default
    float volt1 = (analogRead(SOIL_PIN1) / 4095.0) * 3.3;
    float volt2 = (analogRead(SOIL_PIN2) / 4095.0) * 3.3;
    float volt3 = (analogRead(SOIL_PIN3) / 4095.0) * 3.3;

    sensorData.voltage1 = volt1;
    sensorData.voltage2 = volt2;
    sensorData.voltage3 = volt3;

    // https://makersportal.com/blog/2020/5/26/capacitive-soil-moisture-calibration-with-arduino
    // For calibration of the sensor use the above link.
    // After calibration convert the voltage reading into soil mixutre unit i.e.
    // (cm3 / cm3)

    // Another way is the send the voltage reading directly to server and
    // perform the calcualtion on the server

    Serial.println("Soil Moisture Sensor");
    Serial.printf(" Voltage1: %0.3f", volt1);
    Serial.printf(" Voltage2: %0.3f", volt2);
    Serial.printf(" Voltage3: %0.3f", volt3);
    Serial.println();
}
//============================================================================//
