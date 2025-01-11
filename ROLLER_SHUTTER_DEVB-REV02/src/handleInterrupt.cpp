#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"

extern Adafruit_MCP23008 MCP_1;
extern Adafruit_MCP23008 MCP_2;
extern Adafruit_MCP23008 MCP_3;
extern Adafruit_MCP23008 MCP_4;
extern Adafruit_MCP23008 MCP_5;
extern Adafruit_MCP23008 MCP_6;
extern Adafruit_MCP23008 MCP_7;
extern Adafruit_MCP23008 MCP_8;

bool value_of_input_lock = false;
// tablica lokalnie globalna dla wcisnietych klawiszy

void handleInterrupt()
{
    interrupt_flag = true;
}
void main_handleInterrupt()
{
    //interrupt_flag = false;//ustawiam na false ale w pliku shutter_work.cpp
    //tworze i zupelniam tablice stanow dla klawiszy
    if (value_of_input_lock)
    {
        for (byte i = 0; i < 9; i++)
        {
            value_of_input[i][0] = 0;
            value_of_input[i][1] = 0;
            value_of_input[i][2] = 0;
            value_of_input[i][3] = 0;
        }
        value_of_input_lock = false; // blokuje ponowne zerowanie
    }

    // odczytuje gdzie wystapil stan 1 dla wszystkich wejsc
    for (byte i = 4; i < 8; i++)
    {
        if (test_mpc_1)
        {
            bool input_state = MCP_1.digitalRead(i);
            value_of_input[1][i - 4] = !input_state;
        }
        if (test_mpc_2)
        {
            bool input_state = MCP_2.digitalRead(i);
            value_of_input[2][i - 4] = !input_state;
        }
        if (test_mpc_3)
        {
            bool input_state = MCP_3.digitalRead(i);
            value_of_input[3][i - 4] = !input_state;
        }
        if (test_mpc_4)
        {
            bool input_state = MCP_4.digitalRead(i);
            value_of_input[4][i - 4] = !input_state;
        }
        if (test_mpc_5)
        {
            bool input_state = MCP_5.digitalRead(i);
            value_of_input[5][i - 4] = !input_state;
        }
        if (test_mpc_6)
        {
            bool input_state = MCP_6.digitalRead(i);
            value_of_input[6][i - 4] = !input_state;
        }
        if (test_mpc_7)
        {
            bool input_state = MCP_7.digitalRead(i);
            value_of_input[7][i - 4] = !input_state;
        }
        if (test_mpc_8)
        {
            bool input_state = MCP_8.digitalRead(i);
            value_of_input[8][i - 4] = !input_state;
        }
    }

    // wysweitlenie tablicy wcisnietych klawiszy
    // if (is_get_input)
    // {
    //     for (byte i = 1; i <= 8; i++)
    //     {
    //         for (byte j = 0; j <= 3; j++)
    //         {
    //             //Serial.print(value_of_input[i][j]);  //wyswietlam tablice
    //             if (value_of_input[i][j] == 1) {
    //                String stringToWrite = "Wyjscie:" + String(i) + "." + String(j + 1) + " rozpoczyna prace";
    //                Serial.println(stringToWrite);
    //             }
    //         }
    //         //Serial.println();  //wyswietlam tablice
    //     }
    //     Serial.println("----------------");
    // }

    // Odczyt MCP23008 INTCAP, aby wyczyścić przerwanie
    if (test_mpc_1)
        MCP_1.readGPIO();
    if (test_mpc_2)
        MCP_2.readGPIO();
    if (test_mpc_3)
        MCP_3.readGPIO();
    if (test_mpc_4)
        MCP_4.readGPIO();
    if (test_mpc_5)
        MCP_5.readGPIO();
    if (test_mpc_6)
        MCP_6.readGPIO();
    if (test_mpc_7)
        MCP_7.readGPIO();
    if (test_mpc_8)
        MCP_8.readGPIO();
}