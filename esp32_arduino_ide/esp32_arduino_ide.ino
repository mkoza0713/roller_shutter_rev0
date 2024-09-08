#include <screen_elements.h>
#include <variables.h>
#include <SPI.h>
/*TFT_eSPI file to change drom folder*/
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include <XPT2046_Touchscreen.h>
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

void setup() {
  psetup();
  nav();
  screen_1();
}
void loop() {
  x=0;
  y=0;
  z=0;
  while (touchscreen.tirqTouched() && touchscreen.touched()) {
    if (lock_key_1) {  //f wywoluje sie tylko raz. Nie ma migotania
      lock_key_1 = 0;
      String touch_function_result = touch_function();
      if (touch_function_result == "button_1") {
        screen_changer--;
        if (screen_changer == 0) screen_changer = screen_sum;
        else if(screen_changer>10)screen_changer=1;
        tft.fillScreen(TFT_WHITE);  //moment czyszczenia ekranu
        //tutaj ide w dol z ekranami

      } else if (touch_function_result == "button_2") {
        screen_changer++;
        if (screen_changer > screen_sum) screen_changer = 1;
        else if(screen_changer>10)screen_changer=1;
        tft.fillScreen(TFT_WHITE);  //moment czyszczenia ekranu
        //tutaj ide w gore z ekranami

      } else if (touch_function_result == "button_3") {
        screen_changer = 31;
        tft.fillScreen(TFT_WHITE);  //moment czyszczenia ekranu
        //funkcje przycisku 3
      } else if (touch_function_result == "button_4") {
        screen_changer = 41;
        tft.fillScreen(TFT_WHITE);  //moment czyszczenia ekranu
        //funkcje przycisku 4
      } else if (touch_function_result == "button_5") {
        screen_changer = 51;
        tft.fillScreen(TFT_WHITE);  //moment czyszczenia ekranu
        //funkcje przycisku 5
      } else if (touch_function_result == "button_6") {
        screen_changer = 61;
        tft.fillScreen(TFT_WHITE);  //moment czyszczenia ekranu
        //funkcje przycisku 6
      }
    }
    delay(150);
  }
  if (lock_key_1 == 0) {
    switch (screen_changer) {
      case 1:
        nav();
        screen_1();
        break;
      case 2:
        nav();
        screen_2();
        break;
      case 3:
        nav();
        screen_3();
        break;
      case 31:
        screen_31();
        break;
      case 41:
        screen_41();
        break;
      case 51:
        screen_51();
        break;
      case 61:
        screen_61();
        break;
    }
    lock_key_1 = 1;
  }
}