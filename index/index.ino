#include <screen_elements.h>
#include <SPI.h>
/*
  IMPORTANT: change TFT_eSPI file from link below:
  FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd/ or https://RandomNerdTutorials.com/esp32-tft/   */
#include <TFT_eSPI.h>
// Touchscreen
#include <XPT2046_Touchscreen.h>
TFT_eSPI tft = TFT_eSPI();
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FONT_SIZE 2
// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;
byte lock_key_1 = 1;  //zmienna dotyku przyciskow

void setup() {
  psetup();
  ramka(0, 0);
}
void loop() {
  // // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z) info on the TFT display and Serial Monitor
  while (touchscreen.tirqTouched() && touchscreen.touched()) {
    if (lock_key_1) {
      lock_key_1 = 0;
      Serial.println(touch_function());
    }
  }
  if (lock_key_1 == 0) {
    ramka(0, 0);
    lock_key_1 = 1;
  }
}