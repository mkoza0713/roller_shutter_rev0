#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"

#define I2C_SDA 27
#define I2C_SCL 22
#define MCP_INT_PIN 35

void mcpWriteReg(uint8_t addr, uint8_t reg, uint8_t value) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void mcp_setup() {
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(400000); 

    // Twoje zdefiniowane adresy w tablicy dla pętli
    uint8_t addresses[8] = { 
        MCP1_ADDRESS, MCP2_ADDRESS, MCP3_ADDRESS, MCP4_ADDRESS, 
        MCP5_ADDRESS, MCP6_ADDRESS, MCP7_ADDRESS, MCP8_ADDRESS 
    };
    
    lcdShowCenterText("Wykryto MCP: ");
    for (byte i = 0; i < 8; i++) {
        // Używamy Twojej globalnej tablicy wskaźników MCPs[8]
        if (MCPs[i]->begin(addresses[i])) {
            Serial.printf("MCP %d (0x%02X): OK\n", i + 1, addresses[i]);
            *test_mpc_flags[i] = true;

            String info = String(i + 1) + " (0x" + String(addresses[i], HEX) + ")";
            lcdShowTopTextAdd(info);

            uint8_t intMask = 0;
            for (byte pin = 0; pin < 8; pin++) {
                bool isInput = false;
                
                // LOGIKA ADRESÓW (Twoje potwierdzenie: 0-3 vs 4-7)
                if (i <= 3) {
                    if (pin >= 4 && pin <= 7) isInput = true;
                } else {
                    if (pin == 0 || pin == 4 || pin == 5 || pin == 6) isInput = true;
                }

                if (isInput) {
                    MCPs[i]->pinMode(pin, INPUT);
                    MCPs[i]->pullUp(pin, HIGH);
                    intMask |= (1 << pin);
                } else {
                    MCPs[i]->pinMode(pin, OUTPUT);
                    MCPs[i]->digitalWrite(pin, LOW);
                }
            }

            // Rejestry dla przerwania na pinie 35
            mcpWriteReg(addresses[i], 0x05, 0b00000100); // IOCON (Open-Drain)
            mcpWriteReg(addresses[i], 0x03, 0x00);       // INTCON
            mcpWriteReg(addresses[i], 0x02, intMask);   // GPINTEN
            
            MCPs[i]->readGPIO(); // Pierwszy odczyt uzbraja przerwanie
        } else {
            *test_mpc_flags[i] = false;
        }
    }
    pinMode(MCP_INT_PIN, INPUT_PULLUP);
}