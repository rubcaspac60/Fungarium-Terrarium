#include "scd30.h"  \\ necesary library

#include <stdio.h> /* printf */

/* TO USE CONSOLE OUTPUT (printf) YOU MAY NEED TO ADAPT THE
 * INCLUDE ABOVE OR DEFINE IT ACCORDING TO YOUR PLATFORM.
 * #define printf(...)
 */

int main(void) {
    float SCD_co2_ppm, SCD_temperature, SCD_relative_humidity;
    int16_t SCD_err;
    uint16_t interval_in_seconds = 2;

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