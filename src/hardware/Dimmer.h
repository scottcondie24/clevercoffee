#ifndef DIMMER_H
#define DIMMER_H

#include <RBDdimmer.h>
#include "GPIOPin.h"

class Dimmer {
public:
    Dimmer(GPIOPin& controlPin, GPIOPin& zeroCrossPin, DIMMER_MODE_typedef mode = NORMAL_MODE);
    void begin();
    void setPower(int percentage); // 0–100%
    void on();
    void off();
    bool isOn() const;
    int getPower() const;

private:
    GPIOPin& controlPin;
    GPIOPin& zeroCrossPin;
    dimmerLamp dimmer;
    bool state;
    int power;
};

#endif // DIMMER_H
