/**
 * @file steamSwitch.h
 *
 * @brief Handler for digital steam switch
 */
#include <hardware/pinmapping.h>

uint8_t currStateSteamSwitch;

void checkSteamSwitch() {
    if (FEATURE_STEAMSWITCH) {
        uint8_t steamSwitchReading = steamSwitch->isPressed();

        if (STEAMSWITCH_TYPE == Switch::TOGGLE) {
            // Set steamON to 1 when steamswitch is HIGH
            if (steamSwitchReading == HIGH) {
                steamON = 1;
            }

            // if activated via web interface then steamFirstON == 1, prevent override
            if (steamSwitchReading == LOW && !steamFirstON) {
                steamON = 0;
            }

            // monitor QuickMill thermoblock steam-mode
            if (machine == QuickMill) {
                if (steamQM_active == true) {
                    if (checkSteamOffQM() == true) { // if true: steam-mode can be turned off
                        steamON = 0;
                        steamQM_active = false;
                        lastTimeOptocouplerOn = 0;
                    }
                    else {
                        steamON = 1;
                    }
                }
            }
        }
        else if (STEAMSWITCH_TYPE == Switch::MOMENTARY) {
            if (steamSwitchReading != currStateSteamSwitch) {
                currStateSteamSwitch = steamSwitchReading;

                // only toggle heating power if the new button state is HIGH
                if (currStateSteamSwitch == HIGH) {
                    if (steamON == 0) {
                        steamON = 1;
                    }
                    else {
                        steamON = 0;
                    }
                }
            }
        }
    }
}
