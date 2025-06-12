#pragma once
ESP32Encoder encoder;

unsigned long startMillisEncoderSw = 0;
unsigned long EncoderSwitchBackflushInterval = 2000;
unsigned long EncoderSwitchControlInterval = 800;
bool encoderSwPressed = false;


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
                if(menuLevel == 1) {
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
                }
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
                    menuLevel -= 1;
                    if(menuLevel < 0) {
                        menuLevel = 2;
                    }
                }
                else {
                    menuLevel += 1;
                    if(menuLevel > 2) {
                        menuLevel = 0;
                    }
                }
                LOGF(INFO, "Rotary Encoder Button down for: %lu ms", duration);
            }
            encoderSwPressed = false;
        }
    }
}