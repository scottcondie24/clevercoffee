#pragma once
ESP32Encoder encoder;

unsigned long startMillisEncoderSw = 0;
unsigned long EncoderSwitchBackflushInterval = 2000;
unsigned long EncoderSwitchControlInterval = 800;
bool encoderSwPressed = false;

enum EncoderControlID {
    MENU_POWER = 1,
    MENU_PRESSURE,
    MENU_RECIPE,
    MENU_FLOW,
    MENU_KP,
    MENU_KI,
    MENU_KD,
    MENU_DIM_METHOD
};

struct EncoderControl {
    EncoderControlID id;
    const char* label;
    float* value;
    float step;
    float min;
    float max;
};

EncoderControl encoderControls[] = {
    {}, // index 0 is encoder disabled
    {MENU_POWER,     "Power",     &DimmerPower,      1.0f, 0.0f, 100.0f},
    {MENU_PRESSURE,  "Pressure",  &setPressure,      0.2f, 4.0f, 10.0f},
    {MENU_RECIPE,    "Recipe",    nullptr,           1.0f, 0, recipesCount - 1},
    {MENU_FLOW,      "Flow",      &setPumpFlowRate,  0.2f, 0.0f, 10.0f},
    {MENU_KP,        "Kp",        &flowKp,           0.2f, 0.0f, 40.0f},
    {MENU_KI,        "Ki",        &flowKi,           0.2f, 0.0f, 40.0f},
    {MENU_KD,        "Kd",        &flowKd,           0.01f,0.0f, 4.0f},
    {MENU_DIM_METHOD,"DimMethod",nullptr,            1.0f, 1, 2}
};
const int encoderControlCount = sizeof(encoderControls) / sizeof(EncoderControl);

void initEncoder() {
    ESP32Encoder::useInternalWeakPullResistors = puType::up;
    encoder.attachHalfQuad (PIN_ROTARY_DT, PIN_ROTARY_CLK);
    encoder.setCount (0);
}

void encoderHandler() {
    if(ENCODER_CONTROL > 0) {
        static long lastencodervalue = 0;
        float tempvalue = 0.0;      //use a tempvalue so only the final result is written to each variable

        if(machineState != kBackflush) {
            long value = encoder.getCount() / 2;

            if(value != lastencodervalue) {
                LOGF(INFO, "Rotary Encoder Value: %i", value);
                if (menuLevel == 1) {
                    tempvalue = encoderControl + (value - lastencodervalue);
                    encoderControl = constrain(tempvalue, 1, encoderControlCount - 1);
                } else if (menuLevel == 2 && encoderControl >= 1 && encoderControl < encoderControlCount) {
                    const auto& control = encoderControls[encoderControl];

                    if (control.value != nullptr) {
                        float delta = (value - lastencodervalue) * control.step;
                        *control.value = constrain(*control.value + delta, control.min, control.max);
                    } else if (control.id == MENU_RECIPE) { // Recipe selection
                        currentRecipeIndex = constrain(currentRecipeIndex + (value - lastencodervalue), 0, recipesCount - 1);
                        recipeName = recipes[currentRecipeIndex].name;
                        currentPhaseIndex = 0;
                    } else if (control.id == MENU_DIM_METHOD) { // Dimmer control method
                        featurePumpDimmer = constrain(featurePumpDimmer + (value - lastencodervalue), 1, 2);
                    }
                }




                /*if(menuLevel == 1) {
                    tempvalue = (value-lastencodervalue);
                    tempvalue = encodercontrol + tempvalue;
                    encodercontrol = constrain(tempvalue, 1, 8);    //menus 1 to 8

                    LOGF(INFO, "Rotary Encoder Mode Changed: %i", encodercontrol);
                    pumpintegral = 0;
                    previousError = 0;
                    if(encodercontrol == 3) {//Recipes
                        recipeName = recipes[currentRecipeIndex].name;
                        lastPreinfusion = preinfusion;
                        lastPreinfusionPause = preinfusionPause;
                        lastBrewTime = brewTime;
                        preinfusion = 0;            // disable preinfusion time in s
                        preinfusionPause = 0;       // disable preinfusion pause time in s
                    }
                    else {
                        preinfusion = lastPreinfusion;            // preinfusion time in s
                        preinfusionPause = lastPreinfusionPause; // preinfusion pause time in s
                        brewTime = lastBrewTime;                       // brewtime in s
                    }
                }

                if(menuLevel == 2) {
                    if(encodercontrol == 1) {
                        tempvalue = DimmerPower + (value-lastencodervalue);
                        DimmerPower = constrain(tempvalue, 0, 100);
                    }
                    else if(encodercontrol == 2) {
                        tempvalue = (value-lastencodervalue)/5.0;
                        tempvalue = setPressure + tempvalue;
                        setPressure = constrain(tempvalue, 4.0, 10.0);    //4-10
                    }
                    else if(encodercontrol == 3) {
                        tempvalue = (value-lastencodervalue); 
                        tempvalue = currentRecipeIndex + tempvalue;
                        currentRecipeIndex = constrain(tempvalue, 0.0, recipesCount - 1);    //0-recipesCount
                        currentPhaseIndex = 0;
                        recipeName = recipes[currentRecipeIndex].name;

                        LOGF(INFO, "Recipe Index: %i -- Recipe Name: %s", currentRecipeIndex, recipeName);
                    }
                    else if(encodercontrol == 4) {
                        tempvalue = (value-lastencodervalue)/5.0; 
                        tempvalue = setPumpFlowRate + tempvalue;
                        setPumpFlowRate = constrain(tempvalue, 0.0, 10.0);    //0-10
                    }
                    else if(encodercontrol == 5) {
                        tempvalue = (value-lastencodervalue)/5.0; 
                        tempvalue = flowKp + tempvalue;
                        flowKp = constrain(tempvalue, 0.0, 40.0);    //0-40
                    }
                    else if(encodercontrol == 6) {
                        tempvalue = (value-lastencodervalue)/5.0; 
                        tempvalue = flowKi + tempvalue;
                        flowKi = constrain(tempvalue, 0.0, 40.0);    //0-40
                    }
                    else if(encodercontrol == 7) {
                        tempvalue = (value-lastencodervalue)/100.0; 
                        tempvalue = flowKd + tempvalue;
                        flowKd = constrain(tempvalue, 0.0, 4.0);    //0-4
                    }
                    else if(encodercontrol == 8) {
                        tempvalue = (value-lastencodervalue); 
                        tempvalue = featurePumpDimmer + tempvalue;
                        featurePumpDimmer = constrain(tempvalue, 1, 2);    //1-2
                    }
                }*/


                lastencodervalue = value;
            }
        }

        if(encoderSw->isPressed()) {
            if(encoderSwPressed == false) {
                startMillisEncoderSw = millis();
                encoderSwPressed = true;
            }
        }
        else {
            if(encoderSwPressed == true) {
                unsigned long duration = millis() - startMillisEncoderSw;
                if(duration > EncoderSwitchBackflushInterval) {   //toggle every interval
                    if(machineState == kBackflush) {
                        setBackflush(0);
                        startMillisEncoderSw = millis();
                    }
                    if(machineState == kPidNormal) {
                        setBackflush(1);
                        startMillisEncoderSw = millis();
                    }
                }
                else if(duration > EncoderSwitchControlInterval) {   //toggle every interval
                    menuLevel = 0;
                }
                else {
                    menuLevel = (menuLevel == 1) ? 2 : 1;
                }
                LOGF(INFO, "Rotary Encoder Button down for: %lu ms", duration);
            }
            encoderSwPressed = false;
        }
    }
}