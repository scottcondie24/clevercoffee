#pragma once

#include <RBDdimmer.h>
#include "GPIOPin.h"

class Dimmer {
public:
    Dimmer(GPIOPin& outputPin, GPIOPin& zeroCrossPin); //, int timerNum = 1
    void begin();
    void setPower(int power);     // 0–100
    int getPower() const;
    void off();
    void on();

private:
    GPIOPin& output;
    GPIOPin& zc;
    dimmerLamp dimmer;
    int currentPower;
};