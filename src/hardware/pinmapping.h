/**
 * @file pinmapping.h
 *
 * @brief Default GPIO pin mapping
 *
 */

#pragma once

/**
 * Input Pins
 */

// Switches/Buttons
#define PIN_POWERSWITCH 14  //not used, hardware power switch is the only AC switch
#define PIN_BREWSWITCH  34
#define PIN_STEAMSWITCH 35
#define PIN_WATERSWITCH 39 //was 36, testing 36 with ADC1-0

#define PIN_ROTARY_DT  4 // Rotary encoder data pin
#define PIN_ROTARY_CLK 3 // Rotary encoder clock pin
#define PIN_ROTARY_SW  5 // Rotary encoder switch

// Sensors
#define PIN_TEMPSENSOR  16
#define PIN_WATERSENSOR 5   //23    - reusing the PIN_ROTARY_SW pin as the encoder isnt used in the code yet
#define PIN_HXDAT       33 // Brew scale data pin 1
#define PIN_HXDAT2      25 // Brew scale data pin 2
#define PIN_HXCLK       32 // Brew scale clock pin
#define PIN_PRESSURESENSOR  36
// Pin mapping for MAX6675 temperature sensor
#define PIN_TEMPERATURE_SO  12  
#define PIN_TEMPERATURE_CS  13
#define PIN_TEMPERATURE_CLK 16  //this can be the same as PIN_TEMPSENSOR as it wouldnt otherwise be used

/**
 * Output pins
 */

// Relays
#define PIN_VALVE  17
#define PIN_PUMP   27
#define PIN_HEATER 2

// LEDs
#define PIN_STATUSLED 15    //notused
#define PIN_BREWLED   19
#define PIN_STEAMLED  1
#define PIN_WATERLED  26 //reusing statusled pin

// Periphery
#define PIN_ZC 18 // Dimmer circuit Zero Crossing

/**
 * Bidirectional Pins
 */
#define PIN_I2CSCL 22
#define PIN_I2CSDA 21
