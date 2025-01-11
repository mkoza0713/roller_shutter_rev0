#include "Arduino.h"
#include "Adafruit_MCP23008.h"
volatile bool interrupt_flag = false;

extern Adafruit_MCP23008 MCP_1;
extern Adafruit_MCP23008 MCP_2;

void handleInterrupt(){
  interrupt_flag = true;
}
void main_handleInterrupt(){
    interrupt_flag = false;
    Serial.println("Przerwanie zostało wywołane!");

    // Obsługa przerwania - odczyt wejść z pinów 4-7
    for (byte i = 4; i < 8; i++) {
      bool state = MCP_1.digitalRead(i);
      bool state2 = MCP_2.digitalRead(i);
      Serial.print("Pin ");
      Serial.print(i);
      Serial.print(" state1: ");
      Serial.println(state);
      Serial.print(" state2: ");
      Serial.println(state2);
    }

    // Odczyt MCP23008 INTCAP, aby wyczyścić przerwanie
    MCP_1.readGPIO();
    MCP_2.readGPIO();

}