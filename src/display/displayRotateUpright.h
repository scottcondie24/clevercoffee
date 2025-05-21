/**
 * @file displayRotateUpright.h
 *
 * @brief Display template based on the standard template but rotated 90 degrees
 *
 */

#pragma once

#if (OLED_DISPLAY == 1 || OLED_DISPLAY == 2)
/**
 * @brief initialize display
 */
void u8g2_prepare(void) {
    u8g2.setFont(u8g2_font_profont11_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    u8g2.setDisplayRotation(DISPLAYROTATE); // either put U8G2_R1 or U8G2_R3 in userconfig
}

/**
 * @brief print message
 */
void displayMessage(String text1, String text2, String text3, String text4, String text5, String text6) {
    u8g2.clearBuffer();
    u8g2.setCursor(0, 0);
    u8g2.print(text1);
    u8g2.setCursor(0, 10);
    u8g2.print(text2);
    u8g2.setCursor(0, 20);
    u8g2.print(text3);
    u8g2.setCursor(0, 30);
    u8g2.print(text4);
    u8g2.setCursor(0, 40);
    u8g2.print(text5);
    u8g2.setCursor(0, 50);
    u8g2.print(text6);
    u8g2.sendBuffer();
}
#endif

/**
 * @brief Draw a water empty icon at the given coordinates if water supply is low
 */
void displayWaterIcon(int x, int y) {
    if (!waterTankFull) {
        u8g2.drawXBMP(x, y, 8, 8, Water_Tank_Empty_Icon);
    }
}

/**
 * @brief print logo and message at boot
 */
void displayLogo(String displaymessagetext, String displaymessagetext2) {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 47, displaymessagetext.c_str());
    u8g2.drawStr(0, 55, displaymessagetext2.c_str());

    u8g2.drawXBMP(11, 4, CleverCoffee_Logo_width, CleverCoffee_Logo_height, CleverCoffee_Logo);

    u8g2.sendBuffer();
}

#if 0 // not used a.t.m.
/**
 * @brief display emergency stop
 */
void displayEmergencyStop(void) {
    u8g2.clearBuffer();
    u8g2.setCursor(1, 34);
    u8g2.print(langstring_current_temp_rot_ur);
    u8g2.print(temperature, 1);
    u8g2.print(" ");
    u8g2.print((char)176);
    u8g2.print("C");
    u8g2.setCursor(1, 44);
    u8g2.print(langstring_set_temp_rot_ur);
    u8g2.print(setPoint, 1);
    u8g2.print(" ");
    u8g2.print((char)176);
    u8g2.print("C");

    if (isrCounter < 500) {
        u8g2.setCursor(1, 4);
        u8g2.print(langstring_emergencyStop[0]);
        u8g2.setCursor(1, 14);
        u8g2.print(langstring_emergencyStop[1]);
    }

    u8g2.sendBuffer();
}
#endif

/**
 * @brief determines if brew timer should be visible; postBrewTimerDuration defines how long the timer after the brew is shown
 * @return true if timer should be visible, false otherwise
 */
bool shouldDisplayBrewTimer() {

    enum BrewTimerState {
        kBrewTimerIdle = 10,
        kBrewTimerRunning = 20,
        kBrewTimerPostBrew = 30
    };

    static BrewTimerState currBrewTimerState = kBrewTimerIdle;

    static uint32_t brewEndTime = 0;

    switch (currBrewTimerState) {
        case kBrewTimerIdle:
            if (brew()) {
                currBrewTimerState = kBrewTimerRunning;
            }
            break;

        case kBrewTimerRunning:
            if (!brew()) {
                currBrewTimerState = kBrewTimerPostBrew;
                brewEndTime = millis();
            }
            break;

        case kBrewTimerPostBrew:
            if ((millis() - brewEndTime) > (uint32_t)(postBrewTimerDuration * 1000)) {
                currBrewTimerState = kBrewTimerIdle;
            }
            break;
    }

    return (currBrewTimerState != kBrewTimerIdle);
}

/**
 * @brief display fullscreen brew timer
 */
bool displayFullscreenBrewTimer() {
    if (featureFullscreenBrewTimer == 0) {
        return false;
    }

    if (shouldDisplayBrewTimer()) {
        u8g2.clearBuffer();
        u8g2.drawXBMP(0, 0, Brew_Cup_Logo_width, Brew_Cup_Logo_height, Brew_Cup_Logo);
        displayWaterIcon(55, 1);
        if(FEATURE_SCALE) {
            u8g2.setFont(u8g2_font_profont22_tf);
            u8g2.setCursor(5, 50);
            u8g2.print(timeBrewed / 1000, 1);
            u8g2.setCursor(5, 75);
            if (scaleFailure) {
                u8g2.print("fault");
            }
            else {
                u8g2.print(weightBrewed, 1);
                    //if(featureBrewControl && weightSetpoint > 0) {
                    //    u8g2.print("/");
                    //    u8g2.print(weightSetpoint, 0);
                    //}
            }
        }
        else {
            u8g2.setFont(u8g2_font_profont22_tf);
            u8g2.setCursor(5, 70);
            u8g2.print(timeBrewed / 1000, 1);
        }

        if(FEATURE_PRESSURESENSOR > 0) {
            u8g2.setFont(u8g2_font_profont11_tf);
            u8g2.setCursor(5, 100);
            u8g2.print("P:");
            u8g2.print(inputPressure, 2);
            u8g2.setCursor(5, 115);
            u8g2.print(DimmerPower,0);
            u8g2.print(" ");
            u8g2.print(setPressure,1);
        }
        u8g2.sendBuffer();
        return true;
    }

    return false;
}

/**
 * @brief display fullscreen manual flush timer
 */
bool displayFullscreenManualFlushTimer() {
    if (featureFullscreenManualFlushTimer == 0) {
        return false;
    }

    if (machineState == kManualFlush) {
        u8g2.clearBuffer();
        u8g2.drawXBMP(0, 0, Manual_Flush_Logo_width, Manual_Flush_Logo_height, Manual_Flush_Logo);
        u8g2.setFont(u8g2_font_profont22_tf);
        u8g2.setCursor(5, 70);
        u8g2.print(timeBrewed / 1000, 1);
        u8g2.setFont(u8g2_font_profont11_tf);
        displayWaterIcon(55, 1);
        u8g2.sendBuffer();
        return true;
    }

    return false;
}

/*
Scrolling text example

int offset = 0;

void setup() {
  u8g2.begin();
}

void loop() {
  const char* scrollText = "Scrolling long text message using U8G2 on SSD1306...";
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  int textWidth = u8g2.getStrWidth(scrollText);
  int x = 128 - offset;
  u8g2.drawStr(x, 24, scrollText);

  u8g2.sendBuffer();

  offset++;
  if (offset > textWidth + 128) offset = 0;

  delay(50);
}*/


/*
overflow to new line example
void loop() {
  const char* longText = "This is a very long string that needs to wrap properly on the screen.";
  u8g2.clearBuffer();

  int x = 0;
  int y = 10;
  int maxWidth = 128; // screen width
  char buffer[100];
  int bufferIndex = 0;

  for (int i = 0; longText[i] != '\0'; i++) {
    buffer[bufferIndex++] = longText[i];
    buffer[bufferIndex] = '\0';

    int w = u8g2.getStrWidth(buffer);
    if (w > maxWidth || longText[i + 1] == '\0') {
      u8g2.drawStr(x, y, buffer);
      y += u8g2.getMaxCharHeight();
      bufferIndex = 0;
    }
  }

  u8g2.sendBuffer();
  delay(2000);
}
*/