// funcja do sterowania wyjściami na podstawie tablicy match_table
// wykonuje działanie przypisane do danej rolety. Jeśli jechała w gore to stop,
// jeśli stała to w gore, jeśli jechała w dół to stop itd.
// konieeczne zapisanie poprzedniego stanu pracy aby zachowac logikę
// do każdej rolety zmatchować wyjścia na MCP23008, nalezy wykonać osobną tablicę do wyjść

#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"

void writeOutputStates()
{
    // Tutaj dodaj kod do obsługi wyjść (przekaźników) na MCP23008
    String output_up_id = "";
    String output_down_id = "";
    String mcp_number_up = "";
    String mcp_pin_up = "";
    String mcp_number_down = "";
    String mcp_pin_down = "";

    for (byte i = 0; i < 17; i++)
    {
        if (match_table[i][2] != "")
        {
            String messageToLcd2 = "";
            switch (match_table[i][2].toInt())
            {
            case 1:
                messageToLcd2 = "AKCJA: PRACA POJEDYNCZA";
                break;
            case 2:
                messageToLcd2 = "AKCJA: PRACA GRUPOWA";
                break;
            case 3:
                messageToLcd2 = "AKCJA: PRACA WSZYSTKIE";
                break;
            }
            lcdShowTopTextAdd(messageToLcd2);

            // szukam adresu wyjscia dla danego id rolety
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
                                    Serial.println("ROLETA JEDZIE W DOL");
                                    rollers[s][6] = "0"; // zmieniam poprzedni kieunek
                                    rollers[s][4] = "1"; // ustawiam ze pracuje
                                    Adafruit_MCP23008 *mcp = MCPs[mcp_number_up.toInt()];
                                    mcp->digitalWrite(mcp_pin_down.toInt(), HIGH);
                                    time_start_f0r_work[s][0] = millis(); // ustawiam czas startu
                                }
                                else if (rollers[s][6] == "0")
                                { // jechała w dol
                                    Serial.println("ROLETA JEDZIE W GORE");
                                    rollers[s][6] = "0";
                                    rollers[s][4] = "1"; // ustawiam ze pracuje
                                    Adafruit_MCP23008 *mcp = MCPs[mcp_number_up.toInt()];
                                    mcp->digitalWrite(mcp_pin_up.toInt(), HIGH);
                                    time_start_f0r_work[s][0] = millis(); // ustawiam czas startu
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (byte i = 0; i < 17; i++)
    {
        if (rollers[i][4] == "1")
        { // znak ze pracuje
            // czas pracy minał
            if (millis() - time_start_f0r_work[i][0] >= rollers[i][3].toInt())
            {
                // koniec pracy
                Serial.println("KONIEC PRACY ROLETY");
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
            if(match_table[i][2] != "" && millis() - time_start_f0r_work[i][0] < rollers[i][3].toInt()){ //ponowne wcisniecie przycisku podczas pracy
                Serial.println("PONOWNE WCIŚNIĘCIE PRZYCISKU - ZMIANA KIERUNKU");
                //DOKONCZCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
        }
    match_table[i][2] = "";
    }
}
