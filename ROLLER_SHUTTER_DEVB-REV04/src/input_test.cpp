/* Funkcja odczytuje wejścia z MCP oraz zapisuje aktualne stany w tablicy input_id[][] */

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include "global_variables.h"
#include "functions.h"

void inputstateReadTest()
{
    static byte blokada_1 = 1;
    // 1. Przechodzimy po wszystkich 8 modułach MCP
    for (byte mcp_index = 0; mcp_index < 8; mcp_index++)
    {

        // Sprawdzamy flagę obecności (używamy Twojej tablicy wskaźników)
        if (*test_mpc_flags[mcp_index])
        {
            Adafruit_MCP23008 *mcp = MCPs[mcp_index];

            // SZYBKOŚĆ: Pobieramy stan wszystkich 8 pinów jednym zapytaniem I2C.
            // Odczyt rejestru GPIO automatycznie czyści przerwanie (INT) w module.
            uint8_t gpioState = mcp->readGPIO();

            if (blokada_1)
            {
                for (byte pin = 0; pin < 8; pin++)
                {
                    bool isInput = false;
                    // Logika PCB: Adresy 0-3 (0x20-23) vs 4-7 (0x24-27)
                    if (mcp_index >= 0 && mcp_index <= 3)
                    {
                        if (pin >= 4 && pin <= 7)
                            isInput = true;
                    }
                    else if (mcp_index >= 4 && mcp_index <= 7)
                    {
                        // Zamiana pinu 7 na pin 0 zgodnie z Twoim PCB
                        if (pin == 0 || pin == 4 || pin == 5 || pin == 6)
                            isInput = true;
                    }

                    if (isInput)
                    {
                        byte pin_correct = 0;
                        int state = (gpioState >> pin) & 0x01;
                        if (state == 0)
                        {
                            if (mcp_index >= 0 && mcp_index <= 3)
                            {
                                pin_correct = pin - 4;
                            }
                            else if (mcp_index >= 4 && mcp_index <= 7)
                            {
                                if (pin == 0)
                                    pin_correct = 3;
                                else
                                    pin_correct = pin - 4;
                            }
                            input_id[mcp_index * 4 + pin_correct][1] = "0"; // Wciśnięty, mapuję tak jak powinno byc
                            blokada_1 = 0;
                            delay(200);
                        }
                    }
                }
            }
        }
    }
    blokada_1=1;
}