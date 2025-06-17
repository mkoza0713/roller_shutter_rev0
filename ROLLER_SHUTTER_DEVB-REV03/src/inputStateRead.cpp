#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"

// Deklaracje obiektów MCP (w main.cpp je tworzysz i inicjujesz)
extern Adafruit_MCP23008 MCP_1;
extern Adafruit_MCP23008 MCP_2;
extern Adafruit_MCP23008 MCP_3;
extern Adafruit_MCP23008 MCP_4;
extern Adafruit_MCP23008 MCP_5;
extern Adafruit_MCP23008 MCP_6;
extern Adafruit_MCP23008 MCP_7;
extern Adafruit_MCP23008 MCP_8;

// Tablice wskaźników i flag do iteracji
Adafruit_MCP23008* MCPs[8] = { &MCP_1, &MCP_2, &MCP_3, &MCP_4, &MCP_5, &MCP_6, &MCP_7, &MCP_8 };
bool* test_mpc_flags[8] = { &test_mpc_1, &test_mpc_2, &test_mpc_3, &test_mpc_4, &test_mpc_5, &test_mpc_6, &test_mpc_7, &test_mpc_8 };

// Mapowanie MPC do rolet
const int roller_map[8][2] = {
  {1, 2}, {3, 4}, {5, 6}, {7, 8},
  {9, 10}, {11, 12}, {13, 14}, {15, 16}
};

void inputStateRead()
{
  bool is_get_input = false;

  // Zerowanie tablicy stanów wejść
  for (byte i = 0; i < 9; i++)
    for (byte j = 0; j < 4; j++)
      value_of_input[i][j] = 0;

  // Odczyt stanów wejść dla każdego MCP
  for (byte mpc_index = 0; mpc_index < 8; mpc_index++)
  {
    if (*test_mpc_flags[mpc_index])
    {
      Adafruit_MCP23008* mcp = MCPs[mpc_index];
      byte mpc_id = mpc_index + 1;

      for (byte pin = 4; pin < 8; pin++)
      {
        bool input_state = !mcp->digitalRead(pin);
        if (input_state)
        {
          value_of_input[mpc_id][pin - 4] = 1;
          is_get_input = true;
        }
      }
    }
  }

  if (!is_get_input) return;

  unsigned long currentTime = millis();

  // Przetwarzanie wykrytych wejść
  for (byte mpc_id = 1; mpc_id <= 8; mpc_id++)
  {
    for (byte input_idx = 0; input_idx < 4; input_idx++)
    {
      if (value_of_input[mpc_id][input_idx] == 1)
      {
        int rollerid_1 = roller_map[mpc_id - 1][0];
        int rollerid_2 = roller_map[mpc_id - 1][1];

        Adafruit_MCP23008* mcp = MCPs[mpc_id - 1];

        if ((input_idx == 0 && rollers[rollerid_1][4] == "1" && startTimeForShutter[rollerid_1] == 0) ||
            (input_idx == 1 && rollers[rollerid_1][4] == "0" && startTimeForShutter[rollerid_1] == 0))
        {
          mcp->digitalWrite(input_idx, HIGH);
          startTimeForShutter[rollerid_1] = currentTime;

          Serial.print("Roleta ");
          Serial.print(rollers[rollerid_1][1]);
          Serial.print(" jedzie w ");
          if (input_idx == 0) Serial.println("górę");
          else Serial.println("dół");
        }
        else if ((input_idx == 2 && rollers[rollerid_2][4] == "1" && startTimeForShutter[rollerid_2] == 0) ||
                 (input_idx == 3 && rollers[rollerid_2][4] == "0" && startTimeForShutter[rollerid_2] == 0))
        {
          mcp->digitalWrite(input_idx, HIGH);
          startTimeForShutter[rollerid_2] = currentTime;

          Serial.print("Roleta ");
          Serial.print(rollers[rollerid_2][1]);
          Serial.print(" jedzie w ");
          if (input_idx == 2) Serial.println("górę");
          else Serial.println("dół");
        }

        Serial.print("Wejscie ");
        Serial.print(mpc_id);
        Serial.print(".");
        Serial.println(input_idx + 1);
      }
    }
  }
}
