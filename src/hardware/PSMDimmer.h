/**
 * @file PSMDimmer.h
 *
 * @brief Controls TRIAC Dimmer by skipping cycles
 */
#pragma once

#include <Arduino.h>

// Forward declaration of GPIOPin class
class GPIOPin;

class PSMDimmer {
public:
    PSMDimmer(GPIOPin& pumpPin, GPIOPin& zeroCrossPin);
    void begin();
    void setPower(int newPower);
    int getPower() const;
    bool getState() const;
    void resetCounter();
    void handleZeroCross(); // To be called from ISR
    //void IRAM_ATTR onZeroCrossISR();
    //void IRAM_ATTR onTimerISR();
    void off();
    void on();
    float getFlow(float pressure);

private:
    GPIOPin& _pumpPin;
    GPIOPin& _zcPin;
    volatile unsigned long _lastZCInterrupt;
    volatile int _currentPowerLevel;
    volatile int _power;
    static PSMDimmer* instance;
    static void IRAM_ATTR onZeroCrossStatic();
    //static void IRAM_ATTR onZeroCrossISRStatic();
    //static void IRAM_ATTR onTimerISRStatic();
    bool currentState;
};