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
                            Serial.println("ROLETA JEDZIE W DOL");
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
                            Serial.println("ROLETA JEDZIE W GORE");
                            lcdShowTopTextAdd("JAZDA W GORE");
                            rollers[s][6] = "0";
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
    // szukam wszystkich wyjsc z takim AREA jakie kliknieto
    // to co kliknieto
    String clickedArea = "";
    for (byte j = 0; j < 17; j++)
    {
        if (match_table[i][0] == rollers[j][0])
            clickedArea = rollers[j][2];
    }

    // szukam id z takim samym AREA Po tym muszę znaleźć ID wyjść do wysterowania
    for(byte j = 0; j < 17; j++){
        if(rollers[j][2]==clickedArea){
            //tutaj mam id wszystkich rolet ze strefy rollers[j][0]
            for(byte k=0; k<17;k++){
                //tutaj dla kazdego ID szukam id outow    
                if(rollers[j][0]==match_table_output[k][0]){
                    //tutaj mam id wyjsc i musze je od razu włączyc/wylaczyc
                    //musze jescze ograniczyc do id ktore mam podpiete do systemu
                    //DOKONCZYCYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYC
                    output_start_single(k);  //uruchamiam procedure jak dla single  - do testu nie wiem czy działa
                }
            }
        }
    }
    
    match_table[i][2] = "";

}
void writeOutputStates()
{
    // Tutaj dodaj kod do obsługi wyjść (przekaźników) na MCP23008

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
            if (match_table[i][2] == "1")
                output_start_single(i);

            else if (match_table[i][2] == "2")
            {
                output_start_areas(i);
            }
        }
    }
    for (byte i = 0; i < 17; i++)
    {
        if (rollers[i][4] == "1")
        {
            if (millis() - time_start_f0r_work[i][0] >= rollers[i][3].toInt())
            {
                Serial.print("ZATRZYMANIE AUTOMATYCZNE");
                lcdShowTopTextAdd("ZATRZYMANIE AUTOMATYCZNE");
                output_stop(i);
            }
        }

        if (match_table[i][2] != "" && match_table[i][2] == "1" && millis() - time_start_f0r_work[i][0] < rollers[i][3].toInt())
        { // ponowne wcisniecie przycisku podczas pracy tylko dla trybu podstawowego
            Serial.print("ZATRZYMANIE RECZNE");
            lcdShowTopTextAdd("ZATRZYMANIE RECZNE");
            output_stop(i);
            match_table[i][2] = ""; // zerowanie akcji
        }
    }
}
