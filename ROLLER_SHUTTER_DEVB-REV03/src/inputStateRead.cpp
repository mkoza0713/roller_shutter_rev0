#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"

extern Adafruit_MCP23008 MCP_1;
extern Adafruit_MCP23008 MCP_2;
extern Adafruit_MCP23008 MCP_3;
extern Adafruit_MCP23008 MCP_4;
extern Adafruit_MCP23008 MCP_5;
extern Adafruit_MCP23008 MCP_6;
extern Adafruit_MCP23008 MCP_7;
extern Adafruit_MCP23008 MCP_8;

void inputStateRead()
{
  /*****************odczyt stanow z wejsc programowalnych****************/
  // tworze tablice i wypalniam ja wartosciami domyslnymi, czyli 1. Wartosc 1 to odczytany pullup, 0 to odczytany przycisk
  // tablica w petli jest cały czas zerowana.
  int value_of_input[9][4];
  // zerowanie tablicy tylko raz przy uruchomieniu programu.
  bool is_get_input = false;
  bool first_input_table_look = true;
  if (first_input_table_look)
  {
    for (byte i = 0; i < 9; i++)
    {
      value_of_input[i][0] = 0;
      value_of_input[i][1] = 0;
      value_of_input[i][2] = 0;
      value_of_input[i][3] = 0;
    }
    first_input_table_look = false; // blokuje ponowne zerowanie
  }

  // odczytuje gdzie wystapil stan 1 dla wszystkich wejsc
  for (byte i = 4; i < 8; i++)
  {
    if (test_mpc_1)
    {
      bool input_state = !MCP_1.digitalRead(i);
      if (input_state)
      {
        value_of_input[1][i - 4] = input_state;
        is_get_input = true;
      }
    }
    if (test_mpc_2)
    {
      bool input_state = !MCP_2.digitalRead(i);
      if (input_state)
      {
        value_of_input[2][i - 4] = input_state;
        is_get_input = true;
      }
    }
    if (test_mpc_3)
    {
      bool input_state = !MCP_3.digitalRead(i);
      if (input_state)
      {
        value_of_input[3][i - 4] = input_state;
        is_get_input = true;
      }
    }
    if (test_mpc_4)
    {
      bool input_state = !MCP_4.digitalRead(i);
      if (input_state)
      {
        value_of_input[4][i - 4] = input_state;
        is_get_input = true;
      }
    }
    if (test_mpc_5)
    {
      bool input_state = !MCP_5.digitalRead(i);
      if (input_state)
      {
        value_of_input[5][i - 4] = input_state;
        is_get_input = true;
      }
    }
    if (test_mpc_6)
    {
      bool input_state = !MCP_6.digitalRead(i);
      if (input_state)
      {
        value_of_input[6][i - 4] = input_state;
        is_get_input = true;
      }
    }
    if (test_mpc_7)
    {
      bool input_state = !MCP_7.digitalRead(i);
      if (input_state)
      {
        value_of_input[7][i - 4] = input_state;
        is_get_input = true;
      }
    }
    if (test_mpc_8)
    {
      bool input_state = !MCP_8.digitalRead(i);
      if (input_state)
      {
        value_of_input[8][i - 4] = input_state;
        is_get_input = true;
      }
    }
  }

  if (is_get_input)
  {
    for (byte i = 1; i <= 8; i++)
    {
      for (byte j = 0; j <= 3; j++)
      {
        if (value_of_input[i][j] == 1)
        {
          // zalaczam przekazniki
          unsigned long currentTime = millis();
          int rollerid_1;
          int rollerid_2;

          switch (i)
          {
          case 1: // przypadek dla mpc1
            rollerid_1 = 1;
            rollerid_2 = 2;
            break;
          case 2: // przypadek dla mpc2
            rollerid_1 = 3;
            rollerid_2 = 4;
            if (j == 0 && rollers[rollerid_1][4] == "1" && startTimeForShutter[rollerid_1] == 0) // zakładam ze jest otwarta
            {
              MCP_2.digitalWrite(j, HIGH);
              startTimeForShutter[rollerid_1] = currentTime; // czas startu pomiaru czasu dla danego we/wy
            }
            else if (j == 1 && rollers[rollerid_1][4] == "0" && startTimeForShutter[rollerid_1] == 0) // zakładam ze jest zamknieta
            {
              MCP_2.digitalWrite(j, HIGH);
              startTimeForShutter[3] = currentTime; // czas startu pomiaru czasu dla danego we/wy
            }
            /******************************************************************** */
            if (j == 2 && rollers[rollerid_2][4] == "1" && startTimeForShutter[rollerid_2] == 0)
            {
              MCP_2.digitalWrite(j, HIGH);
              startTimeForShutter[rollerid_2] = currentTime;
            }
            else if (j == 3 && rollers[rollerid_2][4] == "0" && startTimeForShutter[rollerid_2] == 0)
            {
              MCP_2.digitalWrite(j, HIGH);
              startTimeForShutter[rollerid_2] = currentTime;
            }
            break;
          case 3:
            rollerid_1 = 5;
            rollerid_2 = 6;
            break;
          case 4:
            rollerid_1 = 7;
            rollerid_2 = 8;
            break;
          case 5:
            rollerid_1 = 9;
            rollerid_2 = 10;
            break;
          case 6:
            rollerid_1 = 11;
            rollerid_2 = 12;
            break;
          case 7:
            rollerid_1 = 13;
            rollerid_2 = 14;
            break;
          case 8:
            rollerid_1 = 15;
            rollerid_2 = 16;
            break;
          }
        }
      }
    }
  }
}