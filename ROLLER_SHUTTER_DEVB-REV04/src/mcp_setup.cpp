#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "functions.h"
#include "global_variables.h"

#include <Wire.h>
#define I2C_SDA 27
#define I2C_SCL 22
#define MCP_INT_PIN 35   // Pin przerwania MCP23008

// Rejestry MCP23008
#define MCP23008_IODIR   0x00
#define MCP23008_IPOL    0x01
#define MCP23008_GPINTEN 0x02
#define MCP23008_DEFVAL  0x03
#define MCP23008_INTCON  0x04
#define MCP23008_IOCON   0x05
#define MCP23008_GPPU    0x06
#define MCP23008_INTF    0x07
#define MCP23008_INTCAP  0x08
#define MCP23008_GPIO    0x09
#define MCP23008_OLAT    0x0A

// Funkcja do zapisu rejestru MCP23008
void mcpWriteReg(uint8_t addr, uint8_t reg, uint8_t val)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

// Funkcja pomocnicza – przypisanie aktywnych modułów
void out_id_active(String mpc_id)
{
    for (byte i = 0; i < 32; i++)
    {
        if (output_id[i][1] == mpc_id)
        {
            for (byte j = 0; j < 17; j++)
            {
                if (match_table_output[j][1] == output_id[i][0] ||
                    match_table_output[j][2] == output_id[i][0])
                {
                    match_table_output[j][3] = "1"; // status aktywny
                }
            }
        }
    }
}

// Funkcja konfiguracji MCP23008
void mcp_setup()
{
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(100000);

    // Inicjalizacja tablic stanów i czasów zmian dla debounce
    for (byte mcp = 0; mcp < 8; mcp++)
    {
        for (byte pin = 0; pin < 8; pin++)
        {
            last_state[mcp][pin] = 1;              
            last_change_time[mcp][pin] = millis(); 
        }
    }

    String messageToPrint = "Wykryte moduly:\n";

    // Inicjalizacja wszystkich MCP23008
    struct { Adafruit_MCP23008* mcp; uint8_t addr; } MCPsAll[8] = {
        { &MCP_1, MCP1_ADDRESS },
        { &MCP_2, MCP2_ADDRESS },
        { &MCP_3, MCP3_ADDRESS },
        { &MCP_4, MCP4_ADDRESS },
        { &MCP_5, MCP5_ADDRESS },
        { &MCP_6, MCP6_ADDRESS },
        { &MCP_7, MCP7_ADDRESS },
        { &MCP_8, MCP8_ADDRESS }
    };

    for (byte i = 0; i < 8; i++)
    {
        bool initOK = MCPsAll[i].mcp->begin(MCPsAll[i].addr);
        if (initOK)
        {
            Serial.print("MPC ");
            Serial.print(i + 1);
            Serial.println(": start");
            messageToPrint += "MPC " + String(i + 1) + ": 0x" + String(MCPsAll[i].addr, HEX) + "\n";
            out_id_active(String(i + 1));
            *test_mpc_flags[i] = true; // oznacz jako aktywny
        }
        else
        {
            *test_mpc_flags[i] = false;
        }
    }

    Serial.println("");
    lcdShowCenterText(messageToPrint);

    // Konfiguracja pinów i INT dla każdego aktywnego MCP
    for (byte mcp_index = 0; mcp_index < 8; mcp_index++)
    {
        if (*test_mpc_flags[mcp_index])
        {
            Adafruit_MCP23008 *mcp = MCPsAll[mcp_index].mcp;
            uint8_t addr = MCPsAll[mcp_index].addr;

            // --- INT jako open-drain, active-low ---
            mcpWriteReg(addr, MCP23008_IOCON, 0b00000010); // ODR=1, INTPOL=0

            uint8_t intMask = 0; // maska pinów wejściowych

            for (byte mcp_pin = 0; mcp_pin < 8; mcp_pin++)
            {
                switch (mcp_index)
                {
                case 0: case 1: case 2: case 3:
                    switch (mcp_pin)
                    {
                    case 4: case 5: case 6: case 7: // wejścia
                        mcp->pinMode(mcp_pin, INPUT);
                        mcp->pullUp(mcp_pin, HIGH);
                        intMask |= (1 << mcp_pin);
                        break;
                    case 0: case 1: case 2: case 3: // wyjścia
                        mcp->pinMode(mcp_pin, OUTPUT);
                        mcp->digitalWrite(mcp_pin, LOW);
                        break;
                    }
                    break;

                case 4: case 5: case 6: case 7:
                    switch (mcp_pin)
                    {
                    case 0: case 4: case 5: case 6: // wejścia
                        mcp->pinMode(mcp_pin, INPUT);
                        mcp->pullUp(mcp_pin, HIGH);
                        intMask |= (1 << mcp_pin);
                        break;
                    case 1: case 2: case 3: case 7: // wyjścia
                        mcp->pinMode(mcp_pin, OUTPUT);
                        mcp->digitalWrite(mcp_pin, LOW);
                        break;
                    }
                    break;
                }
            }

            // Włącz INT dla wejść
            mcpWriteReg(addr, MCP23008_INTCON, 0x00);   // interrupt on change
            mcpWriteReg(addr, MCP23008_GPINTEN, intMask);
        }
    }
}
