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
 * @date    Dec 20th, 2022
 * @file    camera.h
 * @version v1.0.0 -- CHANGELOG
 *
 * @details This program is written in C++ language using Arduino framework for
 *          ESP32 platform.
 * 
 *          This file deals with the camera module of the ESP32 - CAM.
 *          After perfroming initialization it'll take picture and save it to
 *          SD card
 * 
 * @sa      AI Thinker ESP32-CAM
 *          /doc/ESP32_CAM_Pinout.png
 * 
 */
//============================================================================//

//===== INCLUDES =============================================================//
#include <stdint.h>
//============================================================================//

//===== CONSTANTS AND VARIABLES ==============================================//

// OV2640 CAMERA PIN DEFINITIONS
static const uint8_t
//----- OV2640 SIDE 1 -----
    RESET_GPIO_NUM      = -1,           // No reset pin used
    XCLK_GPIO_NUM       = 0,            // XLCK     = GPIO0
    PCLK_GPIO_NUM       = 22,           // PCLK     = GPIO22
    VSYNC_GPIO_NUM      = 25,           // VSYNC    = GPIO25
    HREF_GPIO_NUM       = 23,           // HREF     = GPIO23
    SIOD_GPIO_NUM       = 26,           // SDA      = GPIO26
    SIOC_GPIO_NUM       = 27,           // SCL      = GPIO27
    PWDN_GPIO_NUM       = 32,           // PWR      = GPIO32
//----- OV2640 SIDE 2 -----
    Y2_GPIO_NUM         = 5,            // D0       = GPIO5
    Y3_GPIO_NUM         = 18,           // D1       = GPIO18
    Y4_GPIO_NUM         = 19,           // D2       = GPIO19
    Y5_GPIO_NUM         = 21,           // D3       = GPIO21
    Y6_GPIO_NUM         = 36,           // D4       = GPIO36
    Y7_GPIO_NUM         = 39,           // D5       = GPIO39
    Y8_GPIO_NUM         = 34,           // D6       = GPIO34
    Y9_GPIO_NUM         = 35;           // D7       = GPIO35
    
//============================================================================//

//===== FUNCTION DECLARATIONS ================================================//
/*!
 * @brief Initializes the camera module OV2640
 * @param None
 * @return None
 */
void initCamera(void);

/*!
 * @brief Takes the picture and saves it in the SD momory card
 * @param None
 * @return None
 */
void takePicture(void);
//============================================================================//
