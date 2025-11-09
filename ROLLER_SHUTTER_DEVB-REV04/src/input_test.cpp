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

      for (byte pin = 4; pin < 7; pin++)
      {
        int state = mcp->digitalRead(pin); // 1 = nie wciśnięty, 0 = wciśnięty

        if (state == 0)
        { // aktywne LOW
          Serial.print("MCP 0x2");
          Serial.print(mcp_index);
          Serial.print(" Pin");
          Serial.print(pin);
          Serial.println(": PRESSED");
        }
      }
    }
  }
}
