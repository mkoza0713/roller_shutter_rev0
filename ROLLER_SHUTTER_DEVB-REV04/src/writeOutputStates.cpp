// funcja do sterowania wyjściami na podstawie tablicy match_table
// wykonuje działanie przypisane do danej rolety. Jeśli jechała w gore to stop,
// jeśli stała to w gore, jeśli jechała w dół to stop itd.
// konieeczne zapisanie poprzedniego stanu pracy aby zachowac logikę
// do każdej rolety zmatchować wyjścia na MCP23008, nalezy wykonać osobną tablicę do wyjść

#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"

void output_stop(byte i) // funcja pomocnicza
{

    String output_up_id = "";
    String output_down_id = "";
    String mcp_number_up = "";
    String mcp_pin_up = "";
    String mcp_number_down = "";
    String mcp_pin_down = "";

    // koniec pracy
    Serial.print("KONIEC PRACY ROLETY ");
    Serial.println(rollers[i][0]);
    rollers[i][4] = "0"; // ustawiam ze nie pracuje

    // szukam na jakie wyjscia podpiete do rolety o id rollers[i][0]
    for (byte j = 0; j < 17; j++)
    {
        if (match_table_output[j][0] == rollers[i][0])
        {
            output_up_id = match_table_output[j][1];   // id wyjścia do otwierania
            output_down_id = match_table_output[j][2]; // id wyjścia do zamykania
        }
    }
    // szukam jakie mcp i piny są podpiete do powyzszych wyjsc
    for (byte j = 0; j < 32; j++)
    {
        if (output_id[j][0] == output_up_id)
        {
            mcp_number_up = output_id[j][1].toInt() - 1;
            mcp_pin_up = output_id[j][2];
        }
        if (output_id[j][0] == output_down_id)
        {
            mcp_number_down = output_id[j][1].toInt() - 1;
            mcp_pin_down = output_id[j][2];
        }
    }
    // wylaczam rpzekaźniki
    Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
    mcp_up->digitalWrite(mcp_pin_up.toInt(), LOW);
    Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];
    mcp_down->digitalWrite(mcp_pin_down.toInt(), LOW);
}
void output_start_single(byte i) // funkcja pomocnicza do pracy single
{
    // szukam adresu wyjscia dla danego id rolety
    // funkcja do uruchomienia pracy JEDNEJ rolety

    String output_up_id = "";
    String output_down_id = "";
    String mcp_number_up = "";
    String mcp_pin_up = "";
    String mcp_number_down = "";
    String mcp_pin_down = "";
    for (byte j = 0; j < 17; j++)
    {
        if (match_table_output[j][0] == match_table[i][0])
        {
            output_up_id = match_table_output[j][1];   // id wyjścia do otwierania
            output_down_id = match_table_output[j][2]; // id wyjścia do zamykania

            for (byte k = 0; k < 32; k++) // szukam w tablicy wyjść odpowiednich pinów i mcp
            {
                if (output_id[k][0] == output_up_id)
                {
                    mcp_number_up = output_id[k][1].toInt() - 1;
                    mcp_pin_up = output_id[k][2];
                }
                if (output_id[k][0] == output_down_id)
                {
                    mcp_number_down = output_id[k][1].toInt() - 1;
                    mcp_pin_down = output_id[k][2];
                }
            }

            String messageToLcd = "WYJSCIA: " + match_table[i][0] + " \nGORA MCP: 0x2" + mcp_number_up + " Pin: " + mcp_pin_up + " \nDOL MCP: 0x2" + mcp_number_down + " Pin: " + mcp_pin_down;
            lcdShowTopTextAdd(messageToLcd);

            for (byte s = 0; s < 17; s++)
            {
                if (rollers[s][0] == match_table[i][0])
                {
                    // musze znac poprzedni stan żeby wiedziec czy ma jechac w gore czy w dol
                    // w tablicy mam kolumne stan (4) i poziom otwarcia (5).
                    // Stanem moge oznaczać czy roleta jest w ruchu czy stoi

                    if (rollers[s][4] == "0") // 0 znaczy ze nie pracowała w momencie wcisniecia klwaisza
                    {
                        if (rollers[s][6] == "1")
                        { // jechała w gore
                            Serial.print("ROLETA JEDZIE W DOL ");
                            Serial.println(rollers[s][0]);
                            lcdShowTopTextAdd("JAZDA W DOL");
                            rollers[s][6] = "0"; // zmieniam poprzedni kieunek
                            rollers[s][4] = "1"; // ustawiam ze pracuje
                            /*************ZABEZPIECZENIE--------->***************/
                            Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
                            mcp_up->digitalWrite(mcp_pin_up.toInt(), LOW);
                            /*************<---------------ZABEZPIECZENIE***************/
                            Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];
                            mcp_down->digitalWrite(mcp_pin_down.toInt(), HIGH);

                            time_start_f0r_work[s][0] = millis(); // ustawiam czas startu
                        }
                        else if (rollers[s][6] == "0")
                        { // jechała w dol
                            Serial.print("ROLETA JEDZIE W GORE ");
                            Serial.println(rollers[s][0]);
                            lcdShowTopTextAdd("JAZDA W GORE");
                            rollers[s][6] = "1";
                            rollers[s][4] = "1"; // ustawiam ze pracuje

                            Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];
                            mcp_down->digitalWrite(mcp_pin_down.toInt(), HIGH);

                            /*************ZABEZPIECZENIE--------->***************/
                            Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
                            mcp_up->digitalWrite(mcp_pin_up.toInt(), HIGH);
                            /*************<---------------ZABEZPIECZENIE***************/

                            time_start_f0r_work[s][0] = millis(); // ustawiam czas startu
                        }
                        match_table[i][2] = ""; // musi byc w tym miejscuz eby nie wykrywał ponownego wcisniecia
                    }
                }
            }
        }
    }
}
void output_start_areas(byte i)
{
    // Szukam AREA rolet klikniętej w match_table[i][0]
    String clickedArea = "";
    for (byte j = 0; j < 17; j++)
    {
        if (match_table[i][0] == rollers[j][0])
        {
            clickedArea = rollers[j][2];
            break;
        }
    }

    if (clickedArea == "")
        return; // brak przypisanego AREA

    // Szukam rolet w tym AREA
    for (byte j = 0; j < 17; j++)
    {
        if (rollers[j][2] == clickedArea && rollers[j][4] == "0") // tylko niepracujące
        {
            String kierunek_inicjujacej = "";
            // Kierunek ustalam na podstawie "inicjującej" roletą z tego AREA
            if (rollers[j][6] == "1")
                kierunek_inicjujacej = "0"; // jechała w górę, teraz w dół
            else if (rollers[j][6] == "0")
                kierunek_inicjujacej = "1"; // jechała w dół, teraz w górę

            // Szukam wyjść dla tej rolety
            String output_up_id = "";
            String output_down_id = "";
            String mcp_number_up = "";
            String mcp_pin_up = "";
            String mcp_number_down = "";
            String mcp_pin_down = "";

            for (byte k = 0; k < 17; k++)
            {
                if (rollers[j][0] == match_table_output[k][0] && match_table_output[k][3] == "1")
                {
                    output_up_id = match_table_output[k][1];
                    output_down_id = match_table_output[k][2];

                    for (byte s = 0; s < 32; s++)
                    {
                        if (output_id[s][0] == output_up_id)
                        {
                            mcp_number_up = output_id[s][1].toInt() - 1;
                            mcp_pin_up = output_id[s][2];
                        }
                        if (output_id[s][0] == output_down_id)
                        {
                            mcp_number_down = output_id[s][1].toInt() - 1;
                            mcp_pin_down = output_id[s][2];
                        }
                    }

                    // Uruchamiam roletę
                    rollers[j][4] = "1"; // ustawiam że pracuje
                    if (kierunek_inicjujacej == "1")
                    {
                        rollers[j][6] = "1"; // nowy kierunek w górę
                        Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
                        mcp_up->digitalWrite(mcp_pin_up.toInt(), HIGH);
                        Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];
                        mcp_down->digitalWrite(mcp_pin_down.toInt(), LOW);
                    }
                    else
                    {
                        rollers[j][6] = "0"; // nowy kierunek w dół
                        Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
                        mcp_up->digitalWrite(mcp_pin_up.toInt(), LOW);
                        Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];
                        mcp_down->digitalWrite(mcp_pin_down.toInt(), HIGH);
                    }

                    // ustawiam czas startu
                    time_start_f0r_work[j][0] = millis();
                }
            }
        }
    }

    match_table[i][2] = ""; // czyszczenie akcji
}
void output_start_all(byte i)
{
    // Funkcja uruchamia wszystkie rolety w kierunku zgodnym z inicjującą roletą

    String kierunek_inicjujacej = "";
    // Szukam roletę inicjującą, z której przyszło polecenie
    for (byte j = 0; j < 17; j++)
    {
        if (rollers[j][0] == match_table[i][0])
        {
            if (rollers[j][6] == "1" && rollers[j][4] == "0")
            {
                kierunek_inicjujacej = "0"; // inicjująca jechała w górę, teraz ALL w dół
                Serial.println("rolety jada w dol");
            }
            else if (rollers[j][6] == "0" && rollers[j][4] == "0")
            {
                kierunek_inicjujacej = "1"; // inicjująca jechała w dół, teraz ALL w górę
                Serial.println("rolety jada w gore");
            }
            break;
        }
    }

    // Teraz włączam wszystkie rolety w systemie w kierunku określonym przez inicjującą
    for (byte k = 0; k < 17; k++)
    {
        if (match_table_output[k][3] == "1") // tylko aktywne MCP
        {
            String output_up_id = match_table_output[k][1];
            String output_down_id = match_table_output[k][2];
            String mcp_number_up = "";
            String mcp_pin_up = "";
            String mcp_number_down = "";
            String mcp_pin_down = "";

            // Szukam MCP i pinów dla wyjść
            for (byte s = 0; s < 32; s++)
            {
                if (output_id[s][0] == output_up_id)
                {
                    mcp_number_up = output_id[s][1].toInt() - 1;
                    mcp_pin_up = output_id[s][2];
                }
                if (output_id[s][0] == output_down_id)
                {
                    mcp_number_down = output_id[s][1].toInt() - 1;
                    mcp_pin_down = output_id[s][2];
                }
            }

            // Dla każdej rolety w rollers dopasowuję i włączam przekaźniki
            for (byte r = 0; r < 17; r++)
            {
                if (rollers[r][0] == match_table_output[k][0] && rollers[r][4] == "0") // nie w ruchu
                {
                    rollers[r][4] = "1"; // ustawiam że pracuje
                    if (kierunek_inicjujacej == "1")
                    {
                        Serial.print("ROLETA ");
                        Serial.print(rollers[r][0]);
                        Serial.println(" JEDZIE W GORE");
                        lcdShowTopTextAdd("JAZDA W GORE: " + rollers[r][0]);
                        rollers[r][6] = "1"; // nowy kierunek w górę

                        // włączam pin w górę i wyłączam w dół (zabezpieczenie)
                        Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
                        mcp_up->digitalWrite(mcp_pin_up.toInt(), HIGH);
                        Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];
                        mcp_down->digitalWrite(mcp_pin_down.toInt(), LOW);
                    }
                    else if (kierunek_inicjujacej == "0")
                    {
                        Serial.print("ROLETA ");
                        Serial.print(rollers[r][0]);
                        Serial.println(" JEDZIE W DOL");
                        lcdShowTopTextAdd("JAZDA W DOL: " + rollers[r][0]);
                        rollers[r][6] = "0"; // nowy kierunek w dół

                        // włączam pin w dół i wyłączam w górę (zabezpieczenie)
                        Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
                        mcp_up->digitalWrite(mcp_pin_up.toInt(), LOW);
                        Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];
                        mcp_down->digitalWrite(mcp_pin_down.toInt(), HIGH);
                    }

                    // ustawiam czas startu
                    time_start_f0r_work[r][0] = millis();
                }
            }
        }
    }

    match_table[i][2] = ""; // czyszczenie akcji po uruchomieniu
}

void writeOutputStates()
{
    // Tutaj dodaj kod do obsługi wyjść (przekaźników) na MCP23008

    for (byte i = 0; i < 17; i++) // petla dla match_table[i][]
    {
        // szukam czy dla danej rolety jest przypisana jakaś akcja
        if (match_table[i][2] != "")
        {
            String messageToLcd2 = "";
            switch (match_table[i][2].toInt())
            {
            case 1:
                Serial.println("AKCJA 1: PRACA POJEDYNCZA");
                messageToLcd2 = "AKCJA 1: PRACA POJEDYNCZA";
                break;
            case 2:
                Serial.println("AKCJA 2: PRACA GRUPOWA");
                messageToLcd2 = "AKCJA 2: PRACA GRUPOWA";
                break;
            case 3:
                Serial.println("AKCJA 3: PRACA WSZYSTKIE");
                messageToLcd2 = "AKCJA 3: PRACA WSZYSTKIE";
                break;
            }
            lcdShowTopTextAdd(messageToLcd2);
            if (match_table[i][2] == "1") // praca pojedyncza
            {
                output_start_single(i);
            }
            else if (match_table[i][2] == "2") // praca grupowa
            {
                output_start_areas(i);
            }
            else if (match_table[i][2] == "3") // praca wszystkich
            {
                output_start_all(i);
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // koniec pracy rolet
    for (byte i = 0; i < 17; i++) // petla dla rollers[i][]
    {
        if (rollers[i][4] == "1")
        {
            if (millis() - time_start_f0r_work[i][0] >= rollers[i][3].toInt())
            {
                Serial.print("ZATRZYMANIE AUTOMATYCZNE ROLETY ");
                Serial.println(rollers[i][0]);
                lcdShowTopTextAdd("ZATRZYMANIE AUTOMATYCZNE");
                output_stop(i);
            }
        }
        if (millis() - time_start_f0r_work[i][0] < rollers[i][3].toInt() && rollers[i][4] == "1")
        {
            // warunek ze czas pracy jeszcze nie minał i roleta pracuje
            for (byte j = 0; j < 17; j++) // petla dla match_table[j][]
            {
                if (match_table[j][2] != "" && match_table[j][2] == "1")
                {
                    Serial.print("ZATRZYMANIE RECZNE ROLETY ");
                    Serial.println(match_table[j][0]);
                    lcdShowTopTextAdd("ZATRZYMANIE RECZNE");
                    match_table[j][2] = ""; // zerowanie akcji
                    output_stop(j);         // przekazuje do stop argument i z rollers[i][]
                }
            }
        }
    }
}
