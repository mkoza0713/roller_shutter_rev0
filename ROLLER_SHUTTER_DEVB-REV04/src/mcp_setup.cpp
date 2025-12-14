#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "functions.h"
#include "global_variables.h"

#include <Wire.h>
#define I2C_SDA 27
#define I2C_SCL 22

// funkcja pomocnicza
void out_id_active(String mpc_id)
{
    // dla danych expanderow przypisuje w tablicy czy są aktywne
    for (byte i = 0; i < 32; i++)
    {
        if (output_id[i][1] == mpc_id)
        {
            // teraz wiem dla ktorych outx_x mam w drugiej tablicy dane
            for (byte j = 0; j < 17; j++)
            {
                // teraz szukam w tablicy match_table_output wyjsc z ekspanderem nr 1
                if (match_table_output[j][1] == output_id[i][0] ||
                    match_table_output[j][2] == output_id[i][0])
                {
                    match_table_output[j][3] = "1"; // status że dane id aktywne
                }
            }
        }
    }
}

void mcp_setup()
{
    Wire.begin(I2C_SDA, I2C_SCL);  // teraz MCP będzie korzystał z właściwych pinów
    Wire.setClock(100000);
    
    // Inicjalizacja tablic stanów i czasów zmian dla debouncae
    for (byte mcp = 0; mcp < 8; mcp++)
    {
        for (byte pin = 0; pin < 8; pin++)
        {
            last_state[mcp][pin] = 1;              // domyślnie HIGH = nie wciśnięty
            last_change_time[mcp][pin] = millis(); // ustaw aktualny czas
        }
    }

    String messageToPrint = "Wykryte moduly:\n";
    // Inicjalizacja MCP23008
    test_mpc_1 = MCP_1.begin(MCP1_ADDRESS);
    if (test_mpc_1)
    {
        Serial.println("MPC 1: start");
        messageToPrint = messageToPrint + "MPC 1: 0x" + String(MCP1_ADDRESS, HEX) + "\n";
        out_id_active("1");
    }

    test_mpc_2 = MCP_2.begin(MCP2_ADDRESS);
    if (test_mpc_2)
    {
        Serial.println("MPC 2: start");
        messageToPrint = messageToPrint + "MPC 2: 0x" + String(MCP2_ADDRESS, HEX) + "\n";
        out_id_active("2");
    }

    test_mpc_3 = MCP_3.begin(MCP3_ADDRESS);
    if (test_mpc_3)
    {
        Serial.println("MPC 3: start");
        messageToPrint = messageToPrint + "MPC 3: 0x" + String(MCP3_ADDRESS, HEX) + "\n";
        out_id_active("3");
    }

    test_mpc_4 = MCP_4.begin(MCP4_ADDRESS);
    if (test_mpc_4)
    {
        Serial.println("MPC 4: start");
        messageToPrint = messageToPrint + "MPC 4: 0x" + String(MCP4_ADDRESS, HEX) + "\n";
        out_id_active("4");
    }

    test_mpc_5 = MCP_5.begin(MCP5_ADDRESS);
    if (test_mpc_5)
    {
        Serial.println("MPC 5: start");
        messageToPrint = messageToPrint + "MPC 5: 0x" + String(MCP5_ADDRESS, HEX) + "\n";
        out_id_active("5");
    }

    test_mpc_6 = MCP_6.begin(MCP6_ADDRESS);
    if (test_mpc_6)
    {
        Serial.println("MPC 6: start");
        messageToPrint = messageToPrint + "MPC 6: 0x" + String(MCP6_ADDRESS, HEX) + "\n";
        out_id_active("6");
    }

    test_mpc_7 = MCP_7.begin(MCP7_ADDRESS);
    if (test_mpc_7)
    {
        Serial.println("MPC 7: start");
        messageToPrint = messageToPrint + "MPC 7: 0x" + String(MCP7_ADDRESS, HEX) + "\n";
        out_id_active("7");
    }

    test_mpc_8 = MCP_8.begin(MCP8_ADDRESS);
    if (test_mpc_8)
    {
        Serial.println("MPC 8: start");
        messageToPrint = messageToPrint + "MPC 8: 0x" + String(MCP8_ADDRESS, HEX) + "\n";
        out_id_active("8");
    }
    Serial.println("");
    lcdShowCenterText(messageToPrint);

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
