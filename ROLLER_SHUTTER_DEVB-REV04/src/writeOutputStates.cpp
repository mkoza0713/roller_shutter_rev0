#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"

void output_stop(byte i)
{
    String output_up_id = "";
    String output_down_id = "";
    String mcp_number_up = "";
    String mcp_pin_up = "";
    String mcp_number_down = "";
    String mcp_pin_down = "";

    Serial.print("KONIEC PRACY ROLETY ");
    Serial.println(rollers[i][0]);
    rollers[i][4] = "0"; // ustawiam że nie pracuje

    for (byte j = 0; j < 17; j++)
    {
        if (match_table_output[j][0] == rollers[i][0])
        {
            output_up_id = match_table_output[j][1];
            output_down_id = match_table_output[j][2];
        }
    }

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

    Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
    Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];

    // bezpieczny zapis do MCP
    safeMcpWrite(mcp_up, mcp_pin_up.toInt(), LOW);
    safeMcpWrite(mcp_down, mcp_pin_down.toInt(), LOW);
}

void output_start_single(byte i)
{
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
            output_up_id = match_table_output[j][1];
            output_down_id = match_table_output[j][2];

            for (byte k = 0; k < 32; k++)
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

            String messageToLcd = "WYJSCIA: " + match_table[i][0] +
                                  " \nGORA MCP: 0x2" + mcp_number_up +
                                  " Pin: " + mcp_pin_up +
                                  " \nDOL MCP: 0x2" + mcp_number_down +
                                  " Pin: " + mcp_pin_down;
            lcdShowTopTextAdd(messageToLcd);

            for (byte s = 0; s < 17; s++)
            {
                if (rollers[s][0] == match_table[i][0] && rollers[s][4] == "0")
                {
                    Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
                    Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];

                    if (rollers[s][6] == "1") // jechała w górę → teraz w dół
                    {
                        Serial.print("ROLETA JEDZIE W DOL ");
                        Serial.println(rollers[s][0]);
                        lcdShowTopTextAdd("JAZDA W DOL");
                        rollers[s][6] = "0";
                        rollers[s][4] = "1";

                        safeMcpWrite(mcp_up, mcp_pin_up.toInt(), LOW);
                        safeMcpWrite(mcp_down, mcp_pin_down.toInt(), HIGH);
                    }
                    else // jechała w dół → teraz w górę
                    {
                        Serial.print("ROLETA JEDZIE W GORE ");
                        Serial.println(rollers[s][0]);
                        lcdShowTopTextAdd("JAZDA W GORE");
                        rollers[s][6] = "1";
                        rollers[s][4] = "1";

                        safeMcpWrite(mcp_down, mcp_pin_down.toInt(), LOW);
                        safeMcpWrite(mcp_up, mcp_pin_up.toInt(), HIGH);
                    }

                    time_start_f0r_work[s][0] = millis();
                    match_table[i][2] = "";
                }
            }
        }
    }
}

void output_start_areas(byte i)
{
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
        return;

    for (byte j = 0; j < 17; j++)
    {
        if (rollers[j][2] == clickedArea && rollers[j][4] == "0")
        {
            String kierunek_inicjujacej = (rollers[j][6] == "1") ? "0" : "1";

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

                    rollers[j][4] = "1";
                    Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
                    Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];

                    if (kierunek_inicjujacej == "1")
                    {
                        rollers[j][6] = "1";
                        safeMcpWrite(mcp_down, mcp_pin_down.toInt(), LOW);
                        safeMcpWrite(mcp_up, mcp_pin_up.toInt(), HIGH);
                    }
                    else
                    {
                        rollers[j][6] = "0";
                        safeMcpWrite(mcp_up, mcp_pin_up.toInt(), LOW);
                        safeMcpWrite(mcp_down, mcp_pin_down.toInt(), HIGH);
                    }

                    time_start_f0r_work[j][0] = millis();
                }
            }
        }
    }

    match_table[i][2] = "";
}

void output_start_all(byte i)
{
    String kierunek_inicjujacej = "";

    for (byte j = 0; j < 17; j++)
    {
        if (rollers[j][0] == match_table[i][0] && rollers[j][4] == "0")
        {
            kierunek_inicjujacej = (rollers[j][6] == "1") ? "0" : "1";
            break;
        }
    }

    for (byte k = 0; k < 17; k++)
    {
        if (match_table_output[k][3] == "1")
        {
            String output_up_id = match_table_output[k][1];
            String output_down_id = match_table_output[k][2];
            String mcp_number_up = "";
            String mcp_pin_up = "";
            String mcp_number_down = "";
            String mcp_pin_down = "";

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

            for (byte r = 0; r < 17; r++)
            {
                if (rollers[r][0] == match_table_output[k][0] && rollers[r][4] == "0")
                {
                    rollers[r][4] = "1";
                    Adafruit_MCP23008 *mcp_up = MCPs[mcp_number_up.toInt()];
                    Adafruit_MCP23008 *mcp_down = MCPs[mcp_number_down.toInt()];

                    if (kierunek_inicjujacej == "1")
                    {
                        rollers[r][6] = "1";
                        safeMcpWrite(mcp_up, mcp_pin_up.toInt(), HIGH);
                        safeMcpWrite(mcp_down, mcp_pin_down.toInt(), LOW);
                    }
                    else
                    {
                        rollers[r][6] = "0";
                        safeMcpWrite(mcp_up, mcp_pin_up.toInt(), LOW);
                        safeMcpWrite(mcp_down, mcp_pin_down.toInt(), HIGH);
                    }

                    time_start_f0r_work[r][0] = millis();
                }
            }
        }
    }

    match_table[i][2] = "";
}

void writeOutputStates()
{
    for (byte i = 0; i < 17; i++)
    {
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

            if (match_table[i][2] == "1") output_start_single(i);
            else if (match_table[i][2] == "2") output_start_areas(i);
            else if (match_table[i][2] == "3") output_start_all(i);
        }
    }

    for (byte i = 0; i < 17; i++)
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
            for (byte j = 0; j < 17; j++)
            {
                if (match_table[j][2] != "" && match_table[j][2] == "1")
                {
                    Serial.print("ZATRZYMANIE RECZNE ROLETY ");
                    Serial.println(match_table[j][0]);
                    lcdShowTopTextAdd("ZATRZYMANIE RECZNE");
                    match_table[j][2] = "";
                    output_stop(j);
                }
            }
        }
    }
}
