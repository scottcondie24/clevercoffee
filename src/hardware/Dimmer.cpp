#include "Dimmer.h"

Dimmer::Dimmer(GPIOPin& controlPin, GPIOPin& zeroCrossPin, DIMMER_MODE_typedef mode)
    : controlPin(controlPin), zeroCrossPin(zeroCrossPin),
      dimmer(controlPin.getPinNumber(), zeroCrossPin.getPinNumber()),
      state(false), power(0) {
    dimmer.begin(mode, OFF);
}

void Dimmer::begin() {
    dimmer.setPower(0);
}

void Dimmer::setPower(int percentage) {
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;
    power = percentage;
    dimmer.setPower(power);
    state = (power > 0);
}

void Dimmer::on() {
    //setPower(power > 0 ? power : 100);
    //dimmer.setState(ON);
}

void Dimmer::off() {
    //setPower(0);
    //dimmer.setState(OFF);
}

bool Dimmer::isOn() const {
    return state;
}

int Dimmer::getPower() const {
    return power;
}
