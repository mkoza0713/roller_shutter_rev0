//funcja do sterowania wyjściami na podstawie tablicy match_table
//wykonuje działanie przypisane do danej rolety. Jeśli jechała w gore to stop,
//jeśli stała to w gore, jeśli jechała w dół to stop itd.
//konieeczne zapisanie poprzedniego stanu pracy aby zachowac logikę
//do każdej rolety zmatchować wyjścia na MCP23008, nalezy wykonać osobną tablicę do wyjść

#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"

void writeOutputStates()
{
    // Tutaj dodaj kod do obsługi wyjść (przekaźników) na MCP23008
    for (byte i = 0; i < 17; i++)
    {
        if (match_table[i][2] != "")
        {
            Serial.print("Action for ");
            Serial.print(match_table[i][0]);
            Serial.print(" on ");
            Serial.print(match_table[i][1]);
            Serial.print(": ");
            Serial.println(match_table[i][2]);

            // Po wykonaniu akcji resetujemy pole działania
            match_table[i][2] = "";
        }
    }
}
