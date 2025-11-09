#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "functions.h"
#include "global_variables.h"

void mcp_setup()
{
    // Inicjalizacja MCP23008
    test_mpc_1 = MCP_1.begin(MCP1_ADDRESS);
    if (test_mpc_1)
        Serial.println("MPC 1: start");

    test_mpc_2 = MCP_2.begin(MCP2_ADDRESS);
    if (test_mpc_2)
        Serial.println("MPC 2: start");

    test_mpc_3 = MCP_3.begin(MCP3_ADDRESS);
    if (test_mpc_3)
        Serial.println("MPC 3: start");

    test_mpc_4 = MCP_4.begin(MCP4_ADDRESS);
    if (test_mpc_4)
        Serial.println("MPC 4: start");

    test_mpc_5 = MCP_5.begin(MCP5_ADDRESS);
    if (test_mpc_5)
        Serial.println("MPC 5: start");

    test_mpc_6 = MCP_6.begin(MCP6_ADDRESS);
    if (test_mpc_6)
        Serial.println("MPC 6: start");

    test_mpc_7 = MCP_7.begin(MCP7_ADDRESS);
    if (test_mpc_7)
        Serial.println("MPC 7: start");

    test_mpc_8 = MCP_8.begin(MCP8_ADDRESS);
    if (test_mpc_8)
        Serial.println("MPC 8: start");
    Serial.println("");

    /**
     Dla adresów: 0x24 0x25 0x26 0x27:
     Ustawienie pinow mpc: 0,4,5,6 jako wejscia (przyciski), 1,2,3,7 jako wyjscia (przekazniki)
     Dla adresów: 0x20 0x21 0x22 0x23
     Ustawienie pinow mpc: 4,5,6,7 jako wejscia (przyciski), 0,1,2,3 jako wyjscia (przekazniki)
     */
    for (byte mcp_index = 0; mcp_index < 8; mcp_index++)
    {
        if (*test_mpc_flags[mcp_index]) // ustawiam tylko aktywne mcp
        {
            Adafruit_MCP23008 *mcp = MCPs[mcp_index];
            for (byte mcp_pin = 0; mcp_pin < 8; mcp_pin++)
            {
                switch (mcp_index)
                {
                case 0:
                case 1:
                case 2:
                case 3:
                    switch (mcp_pin)
                    {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        mcp->pinMode(mcp_pin, INPUT);
                        mcp->pullUp(mcp_pin, HIGH);
                        break;
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        mcp->pinMode(mcp_pin, OUTPUT);
                        mcp->digitalWrite(mcp_pin, LOW);
                        break;
                    }
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    switch (mcp_pin)
                    {
                    case 0:
                    case 4:
                    case 5:
                    case 6:
                        mcp->pinMode(mcp_pin, INPUT);
                        mcp->pullUp(mcp_pin, HIGH);
                        break;
                    case 1:
                    case 2:
                    case 3:
                    case 7:
                        mcp->pinMode(mcp_pin, OUTPUT);
                        mcp->digitalWrite(mcp_pin, LOW);
                        break;
                    }
                    break;
                }
            }
        }
    }
}