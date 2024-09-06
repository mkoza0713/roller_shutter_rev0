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
byte lock_key_1 = 1;      //zmienna dotyku przyciskow
byte screen_changer = 1;  //zmienna kolejnych ekranów w menu
byte screen_sum = 2;      //zmienna kolejnych ekranów w menu

void setup() {
  psetup();
  screen_1(0, 0);
}
void loop() {
  //musze zrobic nav i to zawsze wyswietlac.
  //ponizej beda ekrany screen_1, _2 etc
  switch (screen_changer) {
    case 1:  //screen_1
      while (touchscreen.tirqTouched() && touchscreen.touched()) {
        if (lock_key_1) {
          lock_key_1 = 0;
          if (touch_function() == "button_1") {
            screen_changer--;
            if (screen_changer == 0) screen_changer = screen_sum;
            //tutaj ide w dol z ekranami
            Serial.println("test 1");
          } else if (touch_function() == "button_2") {
            screen_changer++;
            if (screen_changer > screen_sum) screen_changer = 1;
            //tutaj ide w gore z ekranami
            Serial.println("test 2");
          } else if (touch_function() == "button_3") {
            Serial.println("test 3");
          } else if (touch_function() == "button_4") {
            Serial.println("test 4");
          } else if (touch_function() == "button_5") {
            Serial.println("test 5");
          } else if (touch_function() == "button_6") {
            Serial.println("test 6");
          }
        }
      }
      if (lock_key_1 == 0) {
        screen_1(0, 0);
        lock_key_1 = 1;
      }
      break;
    case 2:  //screen_2
      tft.fillScreen(TFT_WHITE);

      break;
  }
  Serial.println(screen_changer);
}