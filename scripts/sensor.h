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
 * @file    sensor.h
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
#include <stdint.h>
//============================================================================//

//===== CONSTANTS AND VARIABLES ==============================================//
// Creating global package for all sensor data
typedef struct {
    uint32_t NO2;
    uint32_t C2H5CH;
    uint32_t VOC;
    uint32_t CO;

    float CO2_1;
    float temperature_1;
    float humidity_1;

    float voltage1;
    float voltage2;
    float voltage3;
} sensor_data_t;

extern sensor_data_t sensorData;

//============================================================================//

//===== FUNCTION DECLARATIONS ================================================//
/*!
 * @brief Initializes all the sensors including GAS,Soil Moisture
 * @param None
 * @return None
 */
void initSensor(void);

/*!
 * @brief Reads the various gas sensor modules
 * @param None
 * @return None
 */
void readGasSensor(void);

/*!
 * @brief Reads the voltage level of soil moisture sensor module
 * @param None
 * @return None
 */
void readSoilSensor(void);
//============================================================================//
