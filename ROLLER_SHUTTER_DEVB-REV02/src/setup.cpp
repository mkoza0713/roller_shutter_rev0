#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "functions.h"

#define int_pin_esp 35
#define MCP1_ADDRESS 0x20  // Adres I2C MCP23008
#define MCP2_ADDRESS 0x21  // Adres I2C MCP23008

Adafruit_MCP23008 MCP_1;
Adafruit_MCP23008 MCP_2;

void psetup(){
    Serial.begin(11520);
  // Inicjalizacja MCP23008
  MCP_1.begin(MCP1_ADDRESS);
  MCP_2.begin(MCP2_ADDRESS);

  // Ustawienie pinów 4-7 jako wejścia i włączenie podciągania rezystorów
  for (byte i = 4; i < 8; i++) {
    MCP_1.pinMode(i, INPUT);
    MCP_1.pullUp(i, HIGH);
    MCP_2.pinMode(i, INPUT);
    MCP_2.pullUp(i, HIGH);
  }

  // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
  Wire.beginTransmission(MCP1_ADDRESS);
  Wire.write(0x02); // MCP23008_GPINTEN
  Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
  Wire.endTransmission();
  Serial.println("GPINTEN configured");

  Wire.beginTransmission(MCP1_ADDRESS);
  Wire.write(0x04); // MCP23008_INTCON
  Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
  Wire.endTransmission();
  Serial.println("INTCON configured");

  Wire.beginTransmission(MCP1_ADDRESS);
  Wire.write(0x03); // MCP23008_DEFVAL
  Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
  Wire.endTransmission();
  Serial.println("DEFVAL configured");


  // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
  Wire.beginTransmission(MCP2_ADDRESS);
  Wire.write(0x02); // MCP23008_GPINTEN
  Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
  Wire.endTransmission();
  Serial.println("GPINTEN configured");

  Wire.beginTransmission(MCP2_ADDRESS);
  Wire.write(0x04); // MCP23008_INTCON
  Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
  Wire.endTransmission();
  Serial.println("INTCON configured");

  Wire.beginTransmission(MCP2_ADDRESS);
  Wire.write(0x03); // MCP23008_DEFVAL
  Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
  Wire.endTransmission();
  Serial.println("DEFVAL configured");


  // Konfiguracja przerwania na Arduino
  pinMode(int_pin_esp, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(int_pin_esp), handleInterrupt, FALLING);
  Serial.println("Interrupt attached");

}