
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
GAS_GMXXX<TwoWire> Groove_gas;
 
 int main(void) {
    float NO2_sensor, C2H5CH_sensor, VOC_sensor, CO_sensor;
    int16_t Groove_gases_err;
    uint16_t interval_in_seconds = 2;

  Groove_gas.begin(Wire, 0x08); // use the hardware I2C
    

    /* Busy loop for initialization, because the main loop does not work without
     * a sensor.
     */
    while (Groove_gas_probe() != NO_ERROR) {
        printf("Groove_gas sensor probing failed\n");
        Groove_gas_sleep_usec(1000000u);
    }
    printf("Groove_gas sensor probing successful\n");

    Groove_gas_set_measurement_interval(interval_in_seconds);
    Groove_gas_sleep_usec(20000u);
    Groove_gas_start_periodic_measurement(0);

    while (1) {
        uint16_t data_ready = 0;
        uint16_t timeout = 0;

        /* Poll data_ready flag until data is available. Allow 20% more than
         * the measurement interval to account for clock imprecision of the
         * sensor.
         */
        for (timeout = 0; (100000 * timeout) < (interval_in_seconds * 1200000);
             ++timeout) {
            Groove_gases_err = Groove_gas_get_data_ready(&data_ready);
            if (Groove_gases_err != NO_ERROR) {
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
        Groove_gases_err =
            Groove_gas_read_measurement(&NO2_sensor, &C2H5CH_sensor, &VOC_sensor, &CO_sensor);
        if (Groove_gases_err != NO_ERROR) {
            printf("error reading measurement\n");

        } else {
            printf("measured NO2 concentration: %0.2f ppm, "
                   "measured C2H5CH concentration: %0.2f ppm, "
                   "measured VOC concentration: %0.2f ppm,"
                   "measured CO concentration: %0.2f ppm,",
                   NO2_sensor, C2H5CH_sensor, VOC_sensor, CO_sensor);
           
                
        }
    }

    Groove_gas_stop_periodic_measurement();
    return 0;
}

/* simplest code 
void setup() {
  // put your setup code here, to run once:
  gas.begin(Wire, 0x08); // use the hardware I2C
}
 
void loop() {
// Select the font
  // GM102B NO2 sensor
  val = gas.getGM102B();
 
  // GM302B C2H5CH sensor
  val = gas.getGM302B();
 
  // GM502B VOC sensor
  val = gas.getGM502B();
  
  // GM702B CO sensor
  val = gas.getGM702B();
  
  delay(100);
 
}

*/