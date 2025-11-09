#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"

// Tablice do zapamiętania stanu i czasu ostatniej zmiany
// int last_state[8][8];                 
// unsigned long last_change_time[8][8]; 

void inputstateReadTest()
{
  for (byte mcp_index = 0; mcp_index < 8; mcp_index++)
    {
        if (*test_mpc_flags[mcp_index])
        {
            Adafruit_MCP23008 *mcp = MCPs[mcp_index];

            for (byte pin = 0; pin < 8; pin++)
            {
                int state = 1;  // domyślnie HIGH = nie wciśnięty
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

                        if (state == 0)  // wciśnięty
                        {
                            Serial.print("MCP 0x2");
                            Serial.print(mcp_index);
                            Serial.print(" Pin");
                            Serial.print(pin);
                            Serial.println(": PRESSED");

                            value_of_input[mcp_index][pin] = 1;
                            String messageToLcd = "MCP 0x2" + String(mcp_index) + " Pin" + String(pin) + ": PRESSED";
                            lcdShowCenterText(messageToLcd);
                        }
                        else  // puszczony
                        {
                            Serial.print("MCP 0x2");
                            Serial.print(mcp_index);
                            Serial.print(" Pin");
                            Serial.print(pin);
                            Serial.println(": RELEASED");

                            value_of_input[mcp_index][pin] = 0;
                            String messageToLcd = "MCP 0x2" + String(mcp_index) + " Pin" + String(pin) + ": RELEASED";
                            lcdShowCenterText(messageToLcd);
                        }
                    }
                }
            }
        }
    }

}
