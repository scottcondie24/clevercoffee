#include "Dimmer.h"

Dimmer::Dimmer(GPIOPin& outputPin, GPIOPin& zeroCrossPin) //, int timerNum
    : output(outputPin), zc(zeroCrossPin),
      dimmer(outputPin.getPin(), zeroCrossPin.getPin()), currentPower(0) {} //, timerNu

void Dimmer::begin() {
    dimmer.begin(NORMAL_MODE, OFF);
}

void Dimmer::setPower(int power) {
    power = constrain(power, 0, 100);
    currentPower = power;
    dimmer.setPower(power);
    //dimmer.setState(ON);
}

int Dimmer::getPower() const {
    return currentPower;
}

void Dimmer::off() {
    //currentPower = 0;
    //dimmer.setPower(0);
    dimmer.setState(OFF);
}

void Dimmer::on() {
    //dimmer.setPower(currentPower);
    dimmer.setState(ON);
}