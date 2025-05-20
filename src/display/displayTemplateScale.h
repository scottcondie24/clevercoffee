/**
 * @file displayTemplateScale.h
 *
 * @brief Display template with brew scale
 *
 */

#pragma once
#include "displayCommon.h"

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

    // Show current weight if scale has no error
    u8g2.setCursor(32, 36);
    u8g2.print(langstring_weight);
    u8g2.setCursor(82, 36);
    if (scaleFailure) {
        u8g2.print("fault");
    }
    else {
        if (shouldDisplayBrewTimer()) {
            u8g2.print(weightBrewed, 1);
            if(featureBrewControl && weightSetpoint > 0) {
                u8g2.print("/");
                u8g2.print(weightSetpoint, 0);
            }
        }
        else {
            u8g2.print(currWeight, 1);
        }
        u8g2.print(" g");
    }

    if (machineState == kManualFlush) {
    // Shown flush time
        u8g2.setCursor(32, 26);
        u8g2.print(langstring_manual_flush);
        u8g2.setCursor(82, 26);
        u8g2.print(timeBrewed / 1000, 0);
        u8g2.print(" s");
    }
    else if (shouldDisplayBrewTimer()) {
        // time
        u8g2.setCursor(32, 26);
        u8g2.print(langstring_brew);
        u8g2.setCursor(82, 26);
        u8g2.print(timeBrewed / 1000, 0);

        if (featureBrewControl && brewTime > 0) {
            u8g2.print("/");
            u8g2.print(totalBrewTime / 1000, 0);
        }
        u8g2.print(" s");
    }

#if (FEATURE_PRESSURESENSOR == 1) || (FEATURE_PRESSURESENSOR == 2)
    u8g2.setCursor(32, 46);
    u8g2.print("P:");
    u8g2.print(inputPressure, 2);
    u8g2.print(" ");
    u8g2.print(DimmerPower,0);
    u8g2.print(" ");
    u8g2.print(setPressure,1);
#endif

    // Show heater output in %
    displayProgressbar(pidOutput / 10, 30, 60, 98);

    buffer_ready = true;
    //u8g2.sendBuffer();
}
