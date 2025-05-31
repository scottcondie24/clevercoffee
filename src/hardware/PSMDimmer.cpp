/*
#include "PSMDimmer.h"
#include "GPIOPin.h"

float PSMflowRate1 = 292.4; //g in 30 seconds using flush
float PSMflowRate2 = 135.6; //g in 30 seconds using water switch, measured from return line
float PSMflowRate2Pres = 10.0; //Bars that OPV is set to

hw_timer_t* triacTimer = nullptr;

PSMDimmer* PSMDimmer::instance = nullptr;

PSMDimmer::PSMDimmer(GPIOPin& pumpPin, GPIOPin& zeroCrossPin)
    : _pumpPin(pumpPin), _zcPin(zeroCrossPin),
      _lastZCInterrupt(0), _currentPowerLevel(0), _power(0) {
    instance = this;
}

void PSMDimmer::begin() {
    currentState = false;
    _pumpPin.write(LOW);
    attachInterrupt(_zcPin.getPin(), onZeroCrossStatic, RISING);
}

void PSMDimmer::resetCounter() {
    _currentPowerLevel = 0;
}

void PSMDimmer::handleZeroCross() {
    unsigned long now = millis();
    if (now - _lastZCInterrupt < 15) return; // Debounce
    _lastZCInterrupt = now;

    if ((_power <= 0)||(currentState == false)) {
        _pumpPin.write(LOW);
        return;
    }

    _currentPowerLevel += _power;

    if (_currentPowerLevel >= 100) {
        _pumpPin.write(HIGH);
        _currentPowerLevel -= 100;
    } else {
        _pumpPin.write(LOW);
    }
}

void IRAM_ATTR PSMDimmer::onZeroCrossStatic() {
    if (instance) {
        instance->handleZeroCross();
    }
}

void PSMDimmer::off() {
    currentState = false;
}

void PSMDimmer::on() {
    if (currentState == false) {    //only reset once in case Pump.on() is called repeatedly
        resetCounter();
    }
    currentState = true;
}

bool PSMDimmer::getState() const {
    return currentState;
}

void PSMDimmer::setPower(int newPower) {
    // Illegal value range, turn pump off to be on the safe side. 
    if (newPower < 0  || newPower > 100) {
        _power = 0;
        return;
    }
    _power = newPower;
    //_power = constrain(newPower, 0, 100); //alternative method that just caps at 0 and 100
}

int PSMDimmer::getPower() const {
    return _power;
}

float PSMDimmer::getFlow(float pressure) {
    float powerMultiplier = 0;
    if(currentState) {  //logs keep showing flow when preinfusion pause, trying to be more explicit - turns out its logging paused
        powerMultiplier = float(getPower())/100;
    }
    else {
        powerMultiplier = 0;
    }
    
    //simple linear interplolation
    float flowRate = powerMultiplier*(-((PSMflowRate1-PSMflowRate2)/PSMflowRate2Pres)*pressure + PSMflowRate1)/30; // result in g/s
    return flowRate;
}
*/