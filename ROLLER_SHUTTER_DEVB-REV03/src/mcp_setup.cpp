#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "functions.h"
#include "global_variables.h"

Adafruit_MCP23008 MCP_1;
Adafruit_MCP23008 MCP_2;
Adafruit_MCP23008 MCP_3;
Adafruit_MCP23008 MCP_4;
Adafruit_MCP23008 MCP_5;
Adafruit_MCP23008 MCP_6;
Adafruit_MCP23008 MCP_7;
Adafruit_MCP23008 MCP_8;

void mcp_setup()
{
    // Inicjalizacja MCP23008
    test_mpc_1 = MCP_1.begin(MCP1_ADDRESS);
    if(test_mpc_1)Serial.println("MPC 1: start");
    test_mpc_2 = MCP_2.begin(MCP2_ADDRESS);
    if(test_mpc_2)Serial.println("MPC 2: start");
    test_mpc_3 = MCP_3.begin(MCP3_ADDRESS);
    if(test_mpc_3)Serial.println("MPC 3: start");
    test_mpc_4 = MCP_4.begin(MCP4_ADDRESS);
    if(test_mpc_4)Serial.println("MPC 4: start");
    test_mpc_5 = MCP_5.begin(MCP5_ADDRESS);
    if(test_mpc_5)Serial.println("MPC 5: start");
    test_mpc_6 = MCP_6.begin(MCP6_ADDRESS);
    if(test_mpc_6)Serial.println("MPC 6: start");
    test_mpc_7 = MCP_7.begin(MCP7_ADDRESS);
    if(test_mpc_7)Serial.println("MPC 7: start");
    test_mpc_8 = MCP_8.begin(MCP8_ADDRESS);
    if(test_mpc_8)Serial.println("MPC 8: start");
    Serial.println("");

    // Ustawienie pinów 4-7 jako wejścia i włączenie podciągania rezystorów
    for (byte i = 4; i < 8; i++)
    {
        if (test_mpc_1)
        {
            MCP_1.pinMode(i, INPUT);
        }
        if (test_mpc_2)
        {
            MCP_2.pinMode(i, INPUT);
        }
        if (test_mpc_3)
        {
            MCP_3.pinMode(i, INPUT);
        }
        if (test_mpc_4)
        {
            MCP_4.pinMode(i, INPUT);
        }
        if (test_mpc_5)
        {
            MCP_5.pinMode(i, INPUT);
        }
        if (test_mpc_6)
        {
            MCP_6.pinMode(i, INPUT);
        }
        if (test_mpc_7)
        {
            MCP_7.pinMode(i, INPUT);
        }
        if (test_mpc_8)
        {
            MCP_8.pinMode(i, INPUT);
        }
    }
    // ustawiam piny  0-3 jako wyjscia dla przekaznikow
    for (byte i = 0; i < 4; i++)
    {
        if (test_mpc_1)
        {
            MCP_1.pinMode(i, OUTPUT);
            MCP_1.digitalWrite(i, LOW);
        }
        if (test_mpc_2)
        {
            MCP_2.pinMode(i, OUTPUT);
            MCP_2.digitalWrite(i, LOW);
        }
        if (test_mpc_3)
        {
            MCP_3.pinMode(i, OUTPUT);
            MCP_3.digitalWrite(i, LOW);
        }
        if (test_mpc_4)
        {
            MCP_4.pinMode(i, OUTPUT);
            MCP_4.digitalWrite(i, LOW);
        }
        if (test_mpc_5)
        {
            MCP_5.pinMode(i, OUTPUT);
            MCP_5.digitalWrite(i, LOW);
        }
        if (test_mpc_6)
        {
            MCP_6.pinMode(i, OUTPUT);
            MCP_6.digitalWrite(i, LOW);
        }
        if (test_mpc_7)
        {
            MCP_7.pinMode(i, OUTPUT);
            MCP_7.digitalWrite(i, LOW);
        }
        if (test_mpc_8)
        {
            MCP_8.pinMode(i, OUTPUT);
            MCP_8.digitalWrite(i, LOW);
        }
    }
}