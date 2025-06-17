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

// Mapowanie MCP do rolet
const int roller_map[8][2] = {
  {1, 2}, {3, 4}, {5, 6}, {7, 8},
  {9, 10}, {11, 12}, {13, 14}, {15, 16}
};

// Zmienne do przytrzymania przycisków
unsigned long buttonPressStart[8][4] = {0}; // dla każdego MCP i 4 przycisków
bool buttonWasPressed[8][4] = {false};

void allRollersDown() {
  Serial.println("Wszystkie rolety jadą w dół (ALL DOWN)");
  for (int r = 1; r <= 16; r++) {
    if (rollers[r][4] == "1") { // jeśli roleta jest na górze
      // TODO: wstaw logikę do puszczenia przekaźnika do jazdy w dół
      // np. startTimeForShutter[r] = millis();
      Serial.print("Roleta ");
      Serial.print(rollers[r][1]);
      Serial.println(" jedzie w dół (ALL DOWN)");
    }
  }
}

void resetSystem() {
  Serial.println("Reset systemu: wszystkie rolety się zamykają");
  for (int r = 1; r <= 16; r++) {
    // TODO: wstaw logikę do zamknięcia rolety (np. startTimeForShutter[r] = millis() itd.)
    Serial.print("Roleta ");
    Serial.print(rollers[r][1]);
    Serial.println(" zamyka się (RESET)");
  }
}

void inputStateRead()
{
  bool is_get_input = false;

  // Zerowanie tablicy stanów wejść
  for (byte i = 0; i < 9; i++)
    for (byte j = 0; j < 4; j++)
      value_of_input[i][j] = 0;

  unsigned long currentTime = millis();

  // Odczyt stanów wejść dla każdego MCP
  for (byte mpc_index = 0; mpc_index < 8; mpc_index++)
  {
    if (*test_mpc_flags[mpc_index])
    {
      Adafruit_MCP23008* mcp = MCPs[mpc_index];
      byte mpc_id = mpc_index + 1;

      for (byte pin = 4; pin < 8; pin++)
      {
        bool input_state = !mcp->digitalRead(pin); // aktywne low
        value_of_input[mpc_id][pin - 4] = input_state ? 1 : 0;

        if (input_state) {
          is_get_input = true;
          // Obsługa czasu przytrzymania przycisku
          if (!buttonWasPressed[mpc_index][pin - 4]) {
            buttonPressStart[mpc_index][pin - 4] = currentTime;
            buttonWasPressed[mpc_index][pin - 4] = true;
          }
          else {
            unsigned long pressedDuration = currentTime - buttonPressStart[mpc_index][pin - 4];

            if (pressedDuration >= 10000) {
              // Reset systemu (przytrzymanie >10s)
              resetSystem();
              // Po resecie, by uniknąć ciągłego wywoływania:
              buttonPressStart[mpc_index][pin - 4] = currentTime + 10000;
            }
            else if (pressedDuration >= 5000) {
              // Wszystkie rolety w dół (przytrzymanie 5-10s)
              allRollersDown();
            }
            // else: jeszcze nie minęło 5s - normalna obsługa poniżej
          }
        }
        else {
          // Przytrzymanie zakończone (puszczenie przycisku)
          if (buttonWasPressed[mpc_index][pin - 4]) {
            unsigned long pressedDuration = currentTime - buttonPressStart[mpc_index][pin - 4];

            if (pressedDuration < 5000) {
              // Normalne działanie tylko gdy przytrzymanie < 5 sekund

              int rollerid_1 = roller_map[mpc_index][0];
              int rollerid_2 = roller_map[mpc_index][1];

              // Sprawdzenie, który przycisk był puszczony i działanie tylko dla MCP aktywnych
              if (pin - 4 == 0 && *test_mpc_flags[mpc_index] && rollers[rollerid_1][4] == "1" && startTimeForShutter[rollerid_1] == 0) {
                mcp->digitalWrite(0, HIGH);
                startTimeForShutter[rollerid_1] = currentTime;
                Serial.print("Roleta ");
                Serial.print(rollers[rollerid_1][1]);
                Serial.println(" jedzie w górę");
              }
              else if (pin - 4 == 1 && *test_mpc_flags[mpc_index] && rollers[rollerid_1][4] == "0" && startTimeForShutter[rollerid_1] == 0) {
                mcp->digitalWrite(1, HIGH);
                startTimeForShutter[rollerid_1] = currentTime;
                Serial.print("Roleta ");
                Serial.print(rollers[rollerid_1][1]);
                Serial.println(" jedzie w dół");
              }
              else if (pin - 4 == 2 && *test_mpc_flags[mpc_index] && rollers[rollerid_2][4] == "1" && startTimeForShutter[rollerid_2] == 0) {
                mcp->digitalWrite(2, HIGH);
                startTimeForShutter[rollerid_2] = currentTime;
                Serial.print("Roleta ");
                Serial.print(rollers[rollerid_2][1]);
                Serial.println(" jedzie w górę");
              }
              else if (pin - 4 == 3 && *test_mpc_flags[mpc_index] && rollers[rollerid_2][4] == "0" && startTimeForShutter[rollerid_2] == 0) {
                mcp->digitalWrite(3, HIGH);
                startTimeForShutter[rollerid_2] = currentTime;
                Serial.print("Roleta ");
                Serial.print(rollers[rollerid_2][1]);
                Serial.println(" jedzie w dół");
              }
            }
            buttonWasPressed[mpc_index][pin - 4] = false;
          }
        }
      }
    }
  }

  if (!is_get_input) return;
}
