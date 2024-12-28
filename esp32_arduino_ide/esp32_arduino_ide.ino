#include <Wire.h>
#include <screen_elements.h>
#include <variables.h>
#include <SPI.h>
/*TFT_eSPI file to change drom folder*/
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include <XPT2046_Touchscreen.h>
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);


/***********HTML**************/
#include <WiFi.h>
#include <HTTPClient.h>

// String tempQuery1 = "?deviceWorkingState=";
// String tempValue1 = "3";
String tempQuery1 = "";
String tempValue1 = "";
unsigned int serverTime;
int serverTimeH;
int serverTimeM;
int serverTimeS;
/***********HTML**************/

/***********MPC**************/
#include <Adafruit_MCP23008.h>
#define MCP1_ADDRESS 0x20 // Adres I2C MCP23008 (domyślnie 0x20)
#define MCP2_ADDRESS 0x21 // Adres I2C MCP23008 (domyślnie 0x20)


Adafruit_MCP23008 MCP_1;
Adafruit_MCP23008 MCP_2;
Adafruit_MCP23008 MCP_3;
Adafruit_MCP23008 MCP_4;
Adafruit_MCP23008 MCP_5;
Adafruit_MCP23008 MCP_6;
Adafruit_MCP23008 MCP_7;
Adafruit_MCP23008 MCP_8;

/***********MPC**************/
/***********PRZERWANIE**************/
// #define MCP23008_INT_PIN 35 // Pin ESP32, do którego podłączony jest sygnał INT

// // Funkcja do zapisu rejestrów MCP23008
// void writeRegister(uint8_t address, uint8_t reg, uint8_t value) {
//     Wire.beginTransmission(address);
//     Wire.write(reg);
//     Wire.write(value);
//     Wire.endTransmission();
// }

// // Funkcja do odczytu rejestrów MCP23008
// uint8_t readRegister(uint8_t address, uint8_t reg) {
//     Wire.beginTransmission(address);
//     Wire.write(reg);
//     Wire.endTransmission();

//     Wire.requestFrom(address, (uint8_t)1);
//     return Wire.read();
// }
// void IRAM_ATTR interruptFunction() {
//   Serial.println("test przerwania pnkt 1");
//   interruptFunctionCode();
//     // Odczytaj GPIO, aby zresetować flagę przerwania dla MCP1
//     readRegister(MCP1_ADDRESS, 0x09);
// }
/***********PRZERWANIE**************/


void setup() {
  psetup();  //funkcje setup()
  i2c_scanner();  //skanowanie urzadzen i2c
  //led_test();
  //relay_test();
  nav();
  screen_1();
}
void loop() {
  input_switch();  //reakcja na przycisk w pomieszczeniu
  screensaver();  //wygaszanie ekranu
  x = 0;
  y = 0;
  z = 0;
  while (touchscreen.tirqTouched() && touchscreen.touched()) {
    if (lock_key_1) {  //f wywoluje sie tylko raz. Nie ma migotania
      lock_key_1 = 0;
      String touch_function_result = touch_function();
      if (touch_function_result == "button_1") {
        screen_changer--;
        if (screen_changer == 0) screen_changer = screen_sum;
        else if (screen_changer > screen_sum) screen_changer = 1;
        //tutaj ide w dol z ekranami

      } else if (touch_function_result == "button_2") {
        screen_changer++;
        if (screen_changer > screen_sum) screen_changer = 1;
        else if (screen_changer > screen_sum) screen_changer = 1;
        //tutaj ide w gore z ekranami

      } else if (touch_function_result == "button_3") {
        screen_changer = 10;
        //funkcje przycisku 3
      } else if (touch_function_result == "button_4") {
        screen_changer = 11;
        //funkcje przycisku 4
      } else if (touch_function_result == "button_5") {
        screen_changer = 12;
        //funkcje przycisku 5
      } else if (touch_function_result == "button_6") {
        screen_changer = 13;
        //funkcje przycisku 6
      } else if (touch_function_result == "button_7") {
        screen_changer = 14;
        //funkcje przycisku 6
      } else if (touch_function_result == "button_8") {
        screen_changer = 15;
        //funkcje przycisku 6
      } else if (touch_function_result == "setting_button_1") {
        screen_changer = 30;
        //funkcje z ustawien
      } else if (touch_function_result == "setting_button_2") {
        screen_changer = 31;
        //funkcje z ustawien
      }
    }
    delay(200);
  }
  if (lock_key_1 == 0) {
    tft.fillScreen(TFT_WHITE);  //moment czyszczenia ekranu
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
      case 10:
        screen_level_2();
        break;
      case 11:
        screen_level_2();
        break;
      case 12:
        screen_level_2();
        break;
      case 13:
        screen_level_2();
        break;
      case 14:
        screen_level_2();
        break;
      case 15:
        screen_level_2();
        break;
      case 30:
        screen_4();
        break;
      case 31:
        screen_5();
        break;
    }
    lock_key_1 = 1;
  }
}
