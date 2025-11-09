#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"

/*TFT_eSPI file to change drom folder*/
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS


#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include <XPT2046_Touchscreen.h>
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

void psetup()
{
    Serial.begin(115200);
    delay(5000);
    Serial.println("Start programu");

    /***********LCD+TFT**************/
    // Start the SPI for the touchscreen and init the touchscreen
    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);
    // Set the Touchscreen rotation in landscape mode
    // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
    touchscreen.setRotation(3);
    // Start the tft display
    tft.init();
    // Set the TFT display rotation in landscape mode
    tft.setRotation(3);
    tft.invertDisplay(true); // odwrocenie kolorow

    // Clear the screen before writing to it
    tft.fillScreen(TFT_WHITE);
    // tft.setTextColor(TFT_WHITE, TFT_BLACK, 1);
    tft.setTextColor(TFT_BLACK, TFT_BLACK);
    tft.setFreeFont(&FreeSans9pt7b);

    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    /***********LCD+TFT**************/
}