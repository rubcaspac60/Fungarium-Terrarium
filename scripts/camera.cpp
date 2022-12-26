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
 * @file    camera.cpp
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
#include <Arduino.h>
#include <esp_camera.h>
#include <FS.h>
#include <SD_MMC.h>
#include <EEPROM.h>

#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>

#include "camera.h"
//============================================================================//

//===== CONSTANTS AND VARIABLES ==============================================//
static const u_int32_t EEPROM_SIZE      = 1;
//============================================================================//

//===== FUNCTION DEFINITIONS =================================================//
void initCamera(void) {
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);  // Disable brownout detector

    camera_config_t camCfg;
    camCfg.ledc_channel     = LEDC_CHANNEL_0;
    camCfg.ledc_timer       = LEDC_TIMER_0;
    camCfg.pin_d0           = Y2_GPIO_NUM;
    camCfg.pin_d1           = Y3_GPIO_NUM;
    camCfg.pin_d2           = Y4_GPIO_NUM;
    camCfg.pin_d3           = Y5_GPIO_NUM;
    camCfg.pin_d4           = Y6_GPIO_NUM;
    camCfg.pin_d5           = Y7_GPIO_NUM;
    camCfg.pin_d6           = Y8_GPIO_NUM;
    camCfg.pin_d7           = Y9_GPIO_NUM;
    camCfg.pin_xclk         = XCLK_GPIO_NUM;
    camCfg.pin_pclk         = PCLK_GPIO_NUM;
    camCfg.pin_vsync        = VSYNC_GPIO_NUM;
    camCfg.pin_href         = HREF_GPIO_NUM;
    camCfg.pin_sscb_sda     = SIOD_GPIO_NUM;
    camCfg.pin_sscb_scl     = SIOC_GPIO_NUM;
    camCfg.pin_pwdn         = PWDN_GPIO_NUM;
    camCfg.pin_reset        = RESET_GPIO_NUM;
    camCfg.xclk_freq_hz     = 20e6;
    camCfg.pixel_format     = PIXFORMAT_JPEG;

    if(psramFound()) {
        camCfg.frame_size   = FRAMESIZE_UXGA;   
        camCfg.jpeg_quality = 10;
        camCfg.fb_count     = 2;
    } else {
        camCfg.frame_size   = FRAMESIZE_SVGA;
        camCfg.jpeg_quality = 12;
        camCfg.fb_count     = 1;
    }

    // Camera initialized
    if(esp_camera_init(&camCfg) != ESP_OK) {
        Serial.println("Camera initialization failed");
        return;
    }

    // SD Card initialize
    if(!SD_MMC.begin()) {
        Serial.println("SD card mount failed");
        return;
    }

    uint8_t cardType = SD_MMC.cardType();
    if(cardType == CARD_NONE) {
        Serial.println("No SD card attached");
        return;
    }

    // EEPROM initialize
    EEPROM.begin(EEPROM_SIZE);
}

void takePicture(void) {
    camera_fb_t *fb = NULL;
    fb = esp_camera_fb_get();
    if(!fb) {
        Serial.println("Camera capture failed");
        return;
    }

    /*
    // FOR INFLUX DB INTEGRATION USE FOLLOWING VARIABLES
    fb->buf;        // This buffer contains JPEG data
    fb->len;        // This is the length of the buffer
    */

    // Save pictre to SD card
    uint32_t pictureNo = EEPROM.read(0) + 1;
    String filePath = "/esp_" + String(pictureNo) + ".jpg";     // esp_xxx.jpg
    Serial.printf("Picture filename: %s\n", filePath.c_str());

    fs::FS &fs = SD_MMC;
    File file = fs.open(filePath.c_str(), FILE_WRITE);
    if(!file) {
        Serial.println("Failed to open file in wirte mode");
    }
    file.write(fb->buf, fb->len);
    file.flush();
    file.close();

    // Saving current picture no into EEPROM
    EEPROM.write(0, pictureNo);
    EEPROM.commit();

    Serial.println("Picture taken and saved");

    // Returing the frame buffer to reuse it again
    esp_camera_fb_return(fb);

    // Turn of ESP32 CAM on boad LED flash
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
}
//============================================================================//
