#include "PhaseDimmer.h"

#if defined(ARDUINO_ARCH_ESP32)

#include "Arduino.h"

#define pulseWidth 1

static int current_dim = 0;
static dimmerLamp* dimmer;
static volatile uint16_t dimPower;
static volatile uint16_t dimOutPin;
static volatile uint16_t dimZCPin;
static volatile uint16_t zeroCross;
static volatile DIMMER_MODE_typedef dimMode;
static volatile ON_OFF_typedef dimState;
static volatile uint16_t dimCounter;
static uint16_t dimPulseBegin;
static volatile uint16_t togMax;
static volatile uint16_t togMin;
static volatile bool togDir;
static int toggleCounter = 0;
static int toggleReload = 25;

static const uint16_t powerBuf[] = {
    100, 99, 98, 97, 96, 95, 94, 93, 92, 91,
     90, 89, 88, 87, 86, 85, 84, 83, 82, 81,
     80, 79, 78, 77, 76, 75, 74, 73, 72, 71,
     70, 69, 68, 67, 66, 65, 64, 63, 62, 61,
     60, 59, 58, 57, 56, 55, 54, 53, 52, 51,
     50, 49, 48, 47, 46, 45, 44, 43, 42, 41,
     40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
     30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
     20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
     10,  9,  8,  7,  6,  5,  4,  3,  2,  1
};

void IRAM_ATTR isr_ext()
{
    if (dimState == ON) {
        zeroCross = 1;
    }
}

void IRAM_ATTR onTimerISR()
{
    toggleCounter++;
    if (zeroCross) {
        dimCounter++;
        if (dimMode == TOGGLE_MODE) {
            if (dimPulseBegin >= togMax) togDir = false;
            if (dimPulseBegin <= togMin) togDir = true;
            if (toggleCounter == toggleReload) {
                dimPulseBegin += (togDir ? 1 : -1);
            }
        }
        if (dimCounter >= dimPulseBegin) {
            digitalWrite(dimOutPin, HIGH);
        }
        if (dimCounter >= dimPulseBegin + pulseWidth) {
            digitalWrite(dimOutPin, LOW);
            zeroCross = 0;
            dimCounter = 0;
        }
    }
    if (toggleCounter >= toggleReload) toggleCounter = 1;
}

// dimmerLamp implementation
dimmerLamp::dimmerLamp(int user_dimmer_pin, int zc_dimmer_pin, int timer_num)
    : dimmer_pin(user_dimmer_pin), zc_pin(zc_dimmer_pin), timer_num(timer_num)
{
    current_dim++;
    current_num = current_dim - 1;
    dimmer = this;

    dimOutPin = user_dimmer_pin;
    dimZCPin = zc_dimmer_pin;
    dimCounter = 0;
    zeroCross = 0;
    dimPulseBegin = 1;
    dimMode = NORMAL_MODE;
    togMin = 0;
    togMax = 1;
    toggle_state = false;

    pinMode(user_dimmer_pin, OUTPUT);
}

void dimmerLamp::timer_init()
{
    hw_timer_t* timer = timerBegin(timer_num, 250, true);
    timerAttachInterrupt(timer, &onTimerISR, true);
    timerAlarmWrite(timer, 30, true);
    timerAlarmEnable(timer);
}

void dimmerLamp::ext_int_init()
{
    pinMode(zc_pin, INPUT_PULLUP);
    attachInterrupt(zc_pin, isr_ext, RISING);
}

void dimmerLamp::begin(DIMMER_MODE_typedef mode, ON_OFF_typedef state)
{
    dimMode = mode;
    dimState = state;
    timer_init();
    ext_int_init();
}

void dimmerLamp::setPower(int power)
{
    if (power >= 99) power = 99;
    dimPower = power;
    dimPulseBegin = powerBuf[power];
    //delay(1);
}

int dimmerLamp::getPower() {
    return (dimState == ON) ? dimPower : 0;
}

void dimmerLamp::setState(ON_OFF_typedef state) {
    dimState = state;
}

bool dimmerLamp::getState() {
    return dimState == ON;
}

void dimmerLamp::changeState() {
    dimState = (dimState == ON) ? OFF : ON;
}

DIMMER_MODE_typedef dimmerLamp::getMode() {
    return dimMode;
}

void dimmerLamp::setMode(DIMMER_MODE_typedef mode) {
    dimMode = mode;
}

void dimmerLamp::toggleSettings(int minValue, int maxValue)
{
    maxValue = min(maxValue, 99);
    minValue = max(minValue, 1);
    dimMode = TOGGLE_MODE;
    togMin = powerBuf[maxValue];
    togMax = powerBuf[maxValue];
    toggleReload = 50;
}

Dimmer::Dimmer(GPIOPin& outputPin, GPIOPin& zeroCrossPin, int timer_num)
: output(outputPin),
  zc(zeroCrossPin),
  dimmer(outputPin.getPin(), zeroCrossPin.getPin(), timer_num),
  currentPower(0),
  currentState(false) {}

void Dimmer::begin() {
    dimmer.begin(NORMAL_MODE, OFF);
}

void Dimmer::setPower(int power) {
    power = constrain(power, 0, 95);
    currentPower = power;
    dimmer.setPower(power);
}

int Dimmer::getPower() const {
    return currentPower;
}

bool Dimmer::getState() const {
    return currentState;
}

void Dimmer::off() {
    dimmer.setState(OFF);
    currentState = false;
}

void Dimmer::on() {
    dimmer.setState(ON);
    currentState = true;
}

#endif