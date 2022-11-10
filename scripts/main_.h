// We start by inclusing the libraries we need 

#include "esp_camera.h"
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "SoftwareSerial.h" 
#include "Groove_gases.h"
#include <Groove_SCD30.h>
#include <Soil_Moisture.h>
#include <Sensirion_SCD30.h>
#include <Wire.h>
#include <HTTPClient.h>



// connecting to the WiFi and accessing the server

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.1.106:1880/update-sensor";

//define the pins for the sensors
#define PWDN_GPIO_NUM  32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  0
#define SIOD_GPIO_NUM  26
#define SIOC_GPIO_NUM  27
#define Y9_GPIO_NUM    35
#define Y8_GPIO_NUM    34
#define Y7_GPIO_NUM    39
#define Y6_GPIO_NUM    36
#define Y5_GPIO_NUM    21
#define Y4_GPIO_NUM    19
#define Y3_GPIO_NUM    18
#define Y2_GPIO_NUM    5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM  23
#define PCLK_GPIO_NUM  22
#define led 13
#define tvocPin 7

void setup(){
Serial.begin(9600);
// Device to serial monitor feedback
pinMode(6, OUTPUT);
pinMode(tvocPin, OUTPUT);

// Warming up sensors
digitalWrite(6, HIGH);        // Ozone sensor
digitalWrite(tvocPin, HIGH);  // TVOC sensor
delay(20 * 1000); // delay 20 seconds
digitalWrite(6, LOW);
digitalWrite(tvocPin, LOW);

Sensirion_SCD30 SCD30; // Creats a DHT object
SCD30  rtc(SDA, SCL); // Initiate the DS3231 Real Time Clock module using the I2C interface
Time  t; // Init a Time-data structure
Groove_SCD30 myGroove_SCD30;    // CO2 Sensor
SoftwareSerial co2Serial(2, 3);  // (RX, TX) MH-Z19 serial
SoftwareSerial pmsSerial(8, 9); // Particulate Matter sensor
PMS pms(pmsSerial);
PMS::DATA data;



float SCD_co2_ppm, SCD_temperature, SCD_relative_humidity,Groove_co2_ppm, Groove_temperature, Groove_relative_humidity;
int16_t SCD_err,Groove_err;
int16_t interval_in_seconds = 2;

/* Initialize I2C */
    sensirion_i2c_init();

    /* Busy loop for initialization, because the main loop does not work without
     * a SCDor.
     */
    while (scd30_probe() != NO_ERROR) {
        printf("SCD30 sensirion probing failed\n");
        sensirion_sleep_usec(1000000u);
    }
    printf("SCD30 sensirion probing successful\n");

    scd30_set_measurement_interval(interval_in_seconds);
    sensirion_sleep_usec(20000u);
    scd30_start_periodic_measurement(0);

    while (1) {
        uint16_t data_ready = 0;
        uint16_t timeout = 0;

        /* Poll data_ready flag until data is available. Allow 20% more than
         * the measurement interval to account for clock imprecision of the
         * SCDor.
         */
        for (timeout = 0; (100000 * timeout) < (interval_in_seconds * 1200000);
             ++timeout) {
            SCD_err = scd30_get_data_ready(&data_ready);
            if (SCD_err != NO_ERROR) {
                printf("Error reading data_ready flag: %i\n", err);
            }
            if (data_ready) {
                break;
            }
            sensirion_sleep_usec(100000);
        }
        if (!data_ready) {
            printf("Timeout waiting for data_ready flag\n");
            continue;
        }

        /* Measure co2, temperature and relative humidity and store into
         * variables.
         */
        SCD_err =
            scd30_read_measurement(&SCD_co2_ppm, &SCD_temperature, &SCD_relative_humidity);
        if (SCD_err != NO_ERROR) {
            printf("error reading measurement\n");

        } else {
            printf("measured co2 concentration: %0.2f ppm, "
                   "measured temperature: %0.2f degreeCelsius, "
                   "measured humidity: %0.2f %%RH\n",
                   SCD_co2_ppm, SCD_temperature, SCD_relative_humidity);
                }
    }

    scd30_stop_periodic_measurement();
    return 0;

}

void loop(){
  // put your main code here, to run repeatedly:
  int hours;