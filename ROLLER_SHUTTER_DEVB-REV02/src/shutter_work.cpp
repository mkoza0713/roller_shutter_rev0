#include "Arduino.h"
#include "global_variables.h"

void shutter_work()
{
    interrupt_flag = false;  //usatwiam flage przerwania na false.
    // wysweitlam pelna tablice stanow
    for (byte i = 1; i <= 8; i++)
    {
        for (byte j = 0; j <= 3; j++)
        {
            // Serial.print(value_of_input[i][j]);  //wyswietlam tablice
            if (value_of_input[i][j] == 1)
            {
                String stringToWrite = "Wyjscie:" + String(i) + "." + String(j + 1) + " rozpoczyna prace";
                Serial.println(stringToWrite);
            }
        }
        // Serial.println();  //wyswietlam tablice
    }
    /*ZAŁOZENIA
    1. Ustalam start pracy dla wszystkich wybranych rolet
    2. Musze zablokowac mozliwosc uruchomienia "sasiadów" czyli przyciskow gora i dol(sa rowniez zablokowane konfiguracja przekaznikow)
    3. Do rozpatrzenia mozliwosc zliczania czasu wcisniecia dla KAZDEGo przycisku z osobna. 
        3.1 Nalezy utworzyć tablice z impulsami
        3.2 Tablica powinna w takim wypadku zawierac komplet kolumn z liczba wcisnietych przyciskow.
        3.3 Nalezy po pewnym czasie te impulsy zerowac
        3.4 Nalezy po wykonaniu pracy te impulsy zerowac
        3.5 Zerowanie nie moze zatrzymywac petli main    
    */


}