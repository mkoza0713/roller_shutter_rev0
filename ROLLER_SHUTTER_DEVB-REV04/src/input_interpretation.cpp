// funkcja do interpretacji wejść
// założenia:
//  wciskam raz - interpretuje jako króki imppuls powiedzmy
//  wciskam i trzymam - interpretuje jako długi impuls powiedzmy
//  wciskam i trzymam dłuzej - interpretuje jako bardzo długi impuls powiedzmy
// pojedyncze wcisniecie - otwieranie/stop/zamykanie
// długie wcisnięcie - zbiorcze otwieranie/zamykanie wszystkich rolet w danej strefie
// bardzo długie wcisnięcie - zamykanie wszystkich rolet w domu (funkcja alarmowa)

#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"
#include "global_variables.h"

void input_interpretation()
{
    static byte matched = 0;
    static byte matched_index = 0;
    for (byte i = 0; i < 32; i++)
    {

        if (input_id[i][1] == "1")
        {
            // brak akcji przy wcisnietym przycisku
        }
        else if (input_id[i][1] == "0")
        { // dzialania dopiero po puszczeniu przycisku
            for (byte j = 0; j < 17; j++)
            {
                // indentyfikuje ktorej rolety dotyczy akcja
                if (match_table[j][1] == input_id[i][0])
                {
                    match_table[j][2] = "1"; // ustawiam akcje do wykonania - krótkie wcisniecie
                }
            }
            input_id[i][1] = ""; // resetujemy stan wejścia powiązanego z tą roletą
            for (byte j = 0; j < 17; j++)
            {
                if (match_table[j][2] == "1")
                {
                    String data_to_print = "Roleta: " + match_table[j][0] + " WE: " + match_table[j][1] + " A: " + match_table[j][2];
                    Serial.println(data_to_print);
                    lcdShowCenterText(data_to_print);
                }
            }
        }
    }
}