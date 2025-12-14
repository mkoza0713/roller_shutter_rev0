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
            // jeśli przycisk jest wciśnięty, start odmierzania czasu
            if (buttonPressTime[i] == 0)
                buttonPressTime[i] = millis();

            if (buttonPressTime[i] != 0)
            {
                unsigned long pressDuration = millis() - buttonPressTime[i];
                if (pressDuration >= 5000 && pressDuration < 10000)
                {
                    // Serial.println(": VERY LONG PRESS");
                    for (byte j = 0; j < 17; j++)
                    {
                        if (match_table[j][1] == input_id[i][0])
                        {                            // indetyfikacja roleta - wejscie
                            matched=3;
                            matched_index=j;
                        }
                    }
                }
                else if (pressDuration >= 2000 && pressDuration < 5000)
                {
                    // Serial.println(": LONG PRESS");
                    for (byte j = 0; j < 17; j++)
                    {
                        if (match_table[j][1] == input_id[i][0])
                        {          
                            matched=2;  
                            matched_index=j;              
                        }
                    }
                }
                else if (pressDuration >= 50 && pressDuration < 2000)
                {
                    // Serial.println(": SHORT PRESS");
                    for (byte j = 0; j < 17; j++)
                    {
                        if (match_table[j][1] == input_id[i][0])
                        {   
                            matched=1;
                            matched_index=j;                         
                        }
                    }
                }
            }
        }else if(input_id[i][1] == "0"){  //dzialania dopiero po puszczeniu przycisku
            if(matched>0){
                match_table[matched_index][2]=String(matched);
            }
            
            //resetowanie akcji powiązanej z tym wejściem
            matched=0;
            matched_index=0;
            for (byte j = 0; j < 32; j++)
            {
                input_id[j][1] = ""; // resetujemy stan wejścia powiązanego z tą roletą
            }

        }
        else
        {
            // Resetowanie czasu przycisku po puszczeniu
            buttonPressTime[i] = 0;

        }
    }
}