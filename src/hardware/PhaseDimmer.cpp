/*
#include "PhaseDimmer.h"

#if defined(ARDUINO_ARCH_ESP32)

#include "Arduino.h"

#define pulseWidth 1
#define ALL_DIMMERS 2

static int current_dim = 0;
static dimmerLamp* dimmer[ALL_DIMMERS];
static volatile uint16_t dimPower[ALL_DIMMERS];
static volatile uint16_t dimOutPin[ALL_DIMMERS];
static volatile uint16_t dimZCPin[ALL_DIMMERS];
static volatile uint16_t zeroCross[ALL_DIMMERS];
static volatile DIMMER_MODE_typedef dimMode[ALL_DIMMERS];
static volatile ON_OFF_typedef dimState[ALL_DIMMERS];
static volatile uint16_t dimCounter[ALL_DIMMERS];
static uint16_t dimPulseBegin[ALL_DIMMERS];
static volatile uint16_t togMax[ALL_DIMMERS];
static volatile uint16_t togMin[ALL_DIMMERS];
static volatile bool togDir[ALL_DIMMERS];
static int toggleCounter = 0;
static int toggleReload = 25;

float PhaseFlowRate1 = 300.0; //g in 30 seconds using flush
float PhaseFlowRate2 = 100.0; //g in 30 seconds using water switch, measured from return line
float PhaseFlowRate2Pres = 9.5; //Bars that OPV is set to

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
    for (int i = 0; i < current_dim; i++) {
        if (dimState[i] == ON) {
            zeroCross[i] = 1;
        }
    }
}

void IRAM_ATTR onTimerISR()
{
    toggleCounter++;
    for (int k = 0; k < current_dim; k++) {
        if (zeroCross) {
            dimCounter[k]++;
            if (dimMode[k] == TOGGLE_MODE) {
                if (dimPulseBegin[k] >= togMax[k]) togDir[k] = false;
                if (dimPulseBegin[k] <= togMin[k]) togDir[k] = true;
                if (toggleCounter == toggleReload) {
                    dimPulseBegin[k] += (togDir[k] ? 1 : -1);
                }
            }
            if (dimCounter[k] >= dimPulseBegin[k]) {
                digitalWrite(dimOutPin[k], HIGH);
            }
            if (dimCounter[k] >= dimPulseBegin[k] + pulseWidth) {
                digitalWrite(dimOutPin[k], LOW);
                zeroCross[k] = 0;
                dimCounter[k] = 0;
            }
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
    dimmer[current_num] = this;

    dimOutPin[current_num] = user_dimmer_pin;
    dimZCPin[current_num] = zc_dimmer_pin;
    dimCounter[current_num] = 0;
    zeroCross[current_num] = 0;
    dimPulseBegin[current_num] = 1;
    dimMode[current_num] = NORMAL_MODE;
    togMin[current_num] = 0;
    togMax[current_num] = 1;
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
    dimMode[current_num] = mode;
    dimState[current_num] = state;
    timer_init();
    ext_int_init();
}

void dimmerLamp::setPower(int power)
{
    if (power >= 99) power = 99;
    dimPower[current_num] = power;
    dimPulseBegin[current_num] = powerBuf[power];
    //delay(1);
}

int dimmerLamp::getPower() {
    return (dimState[current_num] == ON) ? dimPower[current_num] : 0;
}

void dimmerLamp::setState(ON_OFF_typedef state) {
    dimState[current_num] = state;
}

bool dimmerLamp::getState() {
    return dimState[current_num] == ON;
}

void dimmerLamp::changeState() {
    dimState[current_num] = (dimState[current_num] == ON) ? OFF : ON;
}

DIMMER_MODE_typedef dimmerLamp::getMode() {
    return dimMode[current_num];
}

void dimmerLamp::setMode(DIMMER_MODE_typedef mode) {
    dimMode[current_num] = mode;
}

void dimmerLamp::toggleSettings(int minValue, int maxValue)
{
    maxValue = min(maxValue, 99);
    minValue = max(minValue, 1);
    dimMode[current_num] = TOGGLE_MODE;
    togMin[current_num] = powerBuf[maxValue];
    togMax[current_num] = powerBuf[maxValue];
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

float Dimmer::getFlow(float pressure) {
    //this is unfinished
    float powerMultiplier = float(getPower())*2 - 100;  //only use 50% to 100% and map it 0 to 100
    powerMultiplier  = constrain(powerMultiplier, 0, 100)/100; //convert to 0-1
    //simple linear interplolation
    float flowRate = powerMultiplier*(((PhaseFlowRate2 - PhaseFlowRate1)/PhaseFlowRate2Pres)*pressure + PhaseFlowRate1)/30; // result in g/s
    return flowRate;
}

#endif
*/