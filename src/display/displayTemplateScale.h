/**
 * @file displayTemplateScale.h
 *
 * @brief Display template with brew scale
 *
 */

#pragma once
#include "displayCommon.h"

void displayWeight(int x, int y, float weight, float setpoint = -1, bool fault = false) {
    if (fault) {
        u8g2.setCursor(x, y);
        u8g2.print(langstring_weight);
        u8g2.setCursor(x + 50, y);
        u8g2.print(langstring_scale_Failure);
        return;
    }

    u8g2.setCursor(x, y);
    u8g2.print(langstring_weight);
    u8g2.setCursor(x + 50, y);
    u8g2.print(weight, 1);

    if (setpoint > 0) {
        u8g2.print("/");
        u8g2.print(setpoint, 0);
    }

    u8g2.print(" g");
}

/**
 * @brief Send data to display
 */
void printScreen() {

    // Show fullscreen brew timer:
    if (displayFullscreenBrewTimer()) {
        // Display was updated, end here
        return;
    }

    // Show fullscreen manual flush timer:
    if (displayFullscreenManualFlushTimer()) {
        // Display was updated, end here
        return;
    }

    // Print the machine state
    if (displayMachineState()) {
        // Display was updated, end here
        return;
    }
    
    // If no specific machine state was printed, print default:
    u8g2.clearBuffer();

    displayStatusbar();

    displayThermometerOutline(4, 62);

    // Draw current temp in thermometer
    if (fabs(temperature - setpoint) < 0.3) {
        if (isrCounter < 500) {
            drawTemperaturebar(8, 50, 30);
        }
    }
    else {
        drawTemperaturebar(8, 50, 30);
    }

    u8g2.setFont(u8g2_font_profont11_tf);

    u8g2.setCursor(32, 16);
    u8g2.print("T: ");
    u8g2.print(temperature, 1);

    u8g2.print("/");
    u8g2.print(setpoint, 1);
    u8g2.print((char)176);
    u8g2.print("C");

    // Show current weight if scale has no error
    displayWeight(32, 26, currWeight, -1, scaleFailure);

    /**
     * @brief Shot timer for scale
     *
     * If scale has an error show fault on the display otherwise show current reading of the scale
     * if brew is running show current brew time and current brew weight
     * if brewControl is enabled and time or weight target is set show targets
     * show flush time during manualFlush
     * if FEATURE_PRESSURESENSOR is enabled show current pressure during brew
     * if brew is finished show brew values for postBrewTimerDuration
     */

    //dev board
    
    //scaleFailure = false;
    //currWeight = 30.5;
    //weightBrewed = 22.3;
    

#if (FEATURE_BREWSWITCH == 1)

    if (featureBrewControl) {

        if (shouldDisplayBrewTimer()) {
            // time
            u8g2.setCursor(32, 36);
            u8g2.print(langstring_brew);
            u8g2.setCursor(84, 36);
            u8g2.print(timeBrewed / 1000, 0);
            u8g2.print("/");
            u8g2.print(totalBrewTime / 1000, 0);
            u8g2.print(" s");

            // weight
            u8g2.setDrawColor(0);
            u8g2.drawBox(32, 27, 100, 10);
            u8g2.setDrawColor(1);
            displayWeight(32, 26, weightBrewed, weightSetpoint, scaleFailure);
        }
        // Shown flush time while machine is flushing
        if (machineState == kManualFlush) {
            u8g2.setDrawColor(0);
            u8g2.drawBox(32, 37, 100, 10);
            u8g2.setDrawColor(1);
            u8g2.setCursor(32, 36);
            u8g2.print(langstring_manual_flush);
            u8g2.setCursor(84, 36);
            u8g2.print(timeBrewed / 1000, 0);
            u8g2.print(" s");
        }
    }
    else {
        // Brew Timer with optocoupler
        if (shouldDisplayBrewTimer()) {
            // time
            u8g2.setCursor(32, 36);
            u8g2.print(langstring_brew);
            u8g2.setCursor(84, 36);
            u8g2.print(timeBrewed / 1000, 0);
            u8g2.print(" s");

            // weight
            u8g2.setDrawColor(0);
            u8g2.drawBox(32, 27, 100, 10);
            u8g2.setDrawColor(1);
            displayWeight(32, 26, weightBrewed, -1, scaleFailure);
        }
    }
#endif

#if (FEATURE_PRESSURESENSOR == 1) || (FEATURE_PRESSURESENSOR == 2)
    u8g2.setFont(u8g2_font_profont10_tf);
    u8g2.setCursor(32, 46);
    u8g2.print("P:");
    u8g2.print(inputPressure, 2);
    u8g2.print(" ");
    u8g2.print(DimmerPower,0);
    if(encodercontrol == 1) u8g2.print(" Power");
    if(encodercontrol == 2) u8g2.print(" Pressure");
    if(encodercontrol == 3) {
        if(machineState == kBrew) {
            if(pumpControl == PRESSURE) {
                u8g2.print(" Pressure");
            }
            else if(pumpControl == FLOW) {
                u8g2.print(" Flow");
            }
            else if(pumpControl == POWER) {
                u8g2.print(" Power");
            }
        }
        else {
            u8g2.print(" Recipe");
        }
    }
    if(encodercontrol == 4) u8g2.print(" Flow");
    if(encodercontrol == 5) u8g2.print(" Kp");
    if(encodercontrol == 6) u8g2.print(" Ki");
    if(encodercontrol == 7) u8g2.print(" Kd");
    if(encodercontrol == 8) u8g2.print(" DimMethod");
    u8g2.setCursor(32, 55);
    u8g2.print(pumpFlowRate,1);
    u8g2.print(" mL/s ");
    if(encodercontrol == 2) u8g2.print(setPressure,1);
    if(encodercontrol == 3) {
        if(machineState == kBrew) {
            u8g2.print(phaseName);
        }
        else {
            displayScrollingSubstring(80, 55, 35, recipeName, false);  // true = bounce, false = wrap
        }
    }
    if(encodercontrol == 4) u8g2.print(setPumpFlowRate,1);
    if(encodercontrol == 5) u8g2.print(flowKp,1);  
    if(encodercontrol == 6) u8g2.print(flowKi,1);  
    if(encodercontrol == 7) u8g2.print(flowKd,2);  
#if (FEATURE_PUMP_DIMMER > 0)
    if (encodercontrol == 8) {
        PumpDimmerCore::ControlMethod method = pumpRelay.getControlMethod();
        u8g2.print(controlMethodToString(method));
    }
#endif
    u8g2.setFont(u8g2_font_profont11_tf);

#endif

    // Show heater output in %
//    displayProgressbar(pidOutput / 10, 30, 60, 98);

    buffer_ready = true;
    //u8g2.sendBuffer();
}



