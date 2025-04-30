/**
 * @file pressureSensorAds1115.h
 *
 * @brief analog pressure sensor connected to 16bit analog to digital converter
 */

#pragma once

#include "Logger.h"
#include "userConfig.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads1115;

const unsigned long intervalPressureDebug = 1000;
unsigned long previousMillisPressureDebug = 0;

uint8_t ADS_id = 0x48;                    // i2c address
double analog_pressure = 0.0;             // pressure reading in bar
#define CONVERSION_FACTOR_MV 0.188        // 188uV/bit for ads1115
#define CONVERSION_FACTOR_P 0.003         // sensor is 12 Bar over 4000mV
#define RANGEOFFSET 500                   // minimum reading is 500mV

/*uint8_t ABP2_data[7];                     // holds output data
uint8_t ABP2_cmd[3] = {0xAA, 0x00, 0x00}; // command to be sent
double ABP2_press_counts = 0.0;           // digital pressure reading [counts]
double ABP2_temp_counts = 0.0;            // digital temperature reading [counts]
double ABP2_pressure = 0.0;               // pressure reading [bar, psi, kPa, etc.]
double ABP2_temperature = 0.0;            // temperature reading in deg C
double ABP2_outputmax = 15099494.0;       // output at maximum pressure [counts]
double ABP2_outputmin = 1677722.0;        // output at minimum pressure [counts]
double ABP2_pmax = 10.0;                  // maximum value of pressure range [bar, psi, kPa, etc.]
double ABP2_pmin = 0.0;                   // minimum value of pressure range [bar, psi, kPa, etc.]
double ABP2_percentage = 0.0;             // holds percentage of full scale data
*/

float measurePressure() {
    int16_t adc0 = 0;
    double measured_voltage = 0.0;
    ads1115.begin(ADS_id);
    adc0 = ads1115.readADC_SingleEnded(0);

    /*Wire.beginTransmission(ABP2_id);
    int stat = Wire.write(ABP2_cmd, 3); // write command to the sensor
    stat |= Wire.endTransmission();
    delay(ABP2_READ_DELAY_MS);

    // read back Sensor data 7 bytes
    Wire.requestFrom(ABP2_id, (uint8_t)7);

    for (int i = 0; i < 7; i++) {
        ABP2_data[i] = Wire.read();
    }

    // calculate digital pressure counts
    ABP2_press_counts = (double)(ABP2_data[3] + ABP2_data[2] * 256 + ABP2_data[1] * 65536);

    // calculate digital temperature counts
    ABP2_temp_counts = (double)(ABP2_data[6] + ABP2_data[5] * 256 + ABP2_data[4] * 65536);

    // calculate temperature in deg c
    ABP2_temperature = (ABP2_temp_counts * 270.0 / 16777215.0) - 40.0;

    // calculate pressure as percentage of full scale
    ABP2_percentage = (ABP2_press_counts / 16777215.0) * 100.0;

    // calculation of pressure value according to equation 2 of datasheet
    ABP2_pressure = ((ABP2_press_counts - ABP2_outputmin) * (ABP2_pmax - ABP2_pmin)) / (ABP2_outputmax - ABP2_outputmin) + ABP2_pmin;
    */

    measured_voltage = (adc0*CONVERSION_FACTOR_MV) - RANGEOFFSET;
    analog_pressure = measured_voltage*CONVERSION_FACTOR_P;

    IFLOG(TRACE) {
        unsigned long currentMillisPressureDebug = millis();

        if (currentMillisPressureDebug - previousMillisPressureDebug >= intervalPressureDebug) {
            LOGF(TRACE, "Raw: %f, Pressure: %f", adc0, analog_pressure);
            previousMillisPressureDebug = currentMillisPressureDebug;
        }
    }

    return (float)analog_pressure;
}
