/**
 * @file PhaseDimmer.h
 *
 * @brief Controls TRIAC Dimmer by altering the on timing of each cycle
 */

 /*
#pragma once

#include "GPIOPin.h"

typedef enum {
    NORMAL_MODE = 0,
    TOGGLE_MODE = 1
} DIMMER_MODE_typedef;

typedef enum {
    OFF = false,
    ON = true
} ON_OFF_typedef;

class dimmerLamp {
private:
    int current_num;
    int timer_num;
    bool toggle_state;
    int tog_current;
    void timer_init(void);
    void ext_int_init(void);
public:
    uint16_t pulse_begin;
    int dimmer_pin;
    int tog_max;
    int tog_min;
    int zc_pin;

    dimmerLamp(int user_dimmer_pin, int zc_dimmer_pin, int timer_num);
    void begin(DIMMER_MODE_typedef DIMMER_MODE, ON_OFF_typedef ON_OFF);
    void setPower(int power);
    int getPower(void);
    void setState(ON_OFF_typedef ON_OFF);
    bool getState(void);
    void changeState(void);
    void setMode(DIMMER_MODE_typedef DIMMER_MODE);
    DIMMER_MODE_typedef getMode(void);
    void toggleSettings(int minValue, int maxValue);
};

class Dimmer {
public:
    Dimmer(GPIOPin& outputPin, GPIOPin& zeroCrossPin, int timerNum);
    void begin();
    void setPower(int power);
    int getPower() const;
    bool getState() const;
    void off();
    void on();
    float getFlow(float pressure);
private:
    GPIOPin& output;
    GPIOPin& zc;
    dimmerLamp dimmer;
    int currentPower;
    bool currentState;
};
*/