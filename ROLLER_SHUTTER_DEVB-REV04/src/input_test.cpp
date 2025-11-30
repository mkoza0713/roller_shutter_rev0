/*Funkcja odczytuje wejścia z MCP oraz zapisuje aktualne stany w tablicy value_of_input[][] */

#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"

void inputstateReadTest()
{
    for (byte mcp_index = 0; mcp_index < 8; mcp_index++)
    {
        if (*test_mpc_flags[mcp_index])
        {
            Adafruit_MCP23008 *mcp = MCPs[mcp_index];

            for (byte pin = 0; pin < 8; pin++)
            {
                int state = 1; // domyślnie HIGH = nie wciśnięty
                bool valid_pin = false;

                // MCP 0–3 -> piny 4–7
                if (mcp_index <= 3 && pin >= 4 && pin <= 7)
                {
                    state = mcp->digitalRead(pin);
                    valid_pin = true;
                }

                // MCP 4–7 -> piny 0,4,5,6
                if (mcp_index >= 4 && (pin == 0 || pin == 4 || pin == 5 || pin == 6))
                {
                    state = mcp->digitalRead(pin);
                    valid_pin = true;
                }

                if (valid_pin)
                {
                    unsigned long now = millis();

                    // sprawdzamy, czy minął debounce i stan się zmienił
                    if (state != last_state[mcp_index][pin] &&
                        (now - last_change_time[mcp_index][pin] >= debonuce_time))
                    {
                        last_change_time[mcp_index][pin] = now;
                        last_state[mcp_index][pin] = state;

                        if (state == 0) // wciśnięty
                        {
                            if (pin == 0)
                                input_id[(mcp_index * 4) + 7 - 4][1] = "1";
                            else
                                input_id[(mcp_index * 4) + pin - 4][1] = "1";
                            Serial.println();
                            Serial.print("MCP 0x2");
                            Serial.print(mcp_index);
                            Serial.print(" Pin");
                            Serial.print(pin);
                            Serial.print(": PRESSED");
                            Serial.print(" INPUT ID: ");
                            String messageToLcd;
                            for (byte i = 0; i < 32; i++)
                            {
                                if (input_id[i][1] != "")
                                {
                                    Serial.println(input_id[i][0]);
                                    messageToLcd = "WCISNIETY PRZYCISK\nMCP 0x2" + String(mcp_index) + " Pin" + String(pin) + " ID: " + String(input_id[i][0]) + "\n";
                                }
                            }

                            lcdShowCenterText(messageToLcd);
                        }
                        else // puszczony
                        {
                            Serial.print("MCP 0x2");
                            Serial.print(mcp_index);
                            Serial.print(" Pin");
                            Serial.print(pin);
                            Serial.print(": RELEASED");
                            Serial.print(" INPUT ID: ");
                            String messageToLcd;
                            for (byte i = 0; i < 32; i++)
                            {
                                if (input_id[i][1] != "")
                                {
                                    Serial.println(input_id[i][0]);
                                    messageToLcd = "PUSZCZONY PRZYCISK\nMCP 0x2" + String(mcp_index) + " Pin" + String(pin) + " ID: " + String(input_id[i][0]) + "\n";
                                }
                            }

                            if (pin == 0)
                                input_id[(mcp_index * 4) + 7 - 4][1] = "0";
                            else
                                input_id[(mcp_index * 4) + pin - 4][1] = "0";

                            lcdShowCenterText(messageToLcd);
                        }
                    }
                }
            }
        }
    }
}
