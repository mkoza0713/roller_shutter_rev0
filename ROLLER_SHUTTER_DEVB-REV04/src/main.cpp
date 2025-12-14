#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"

void setup()
{
  psetup();
  mcp_setup();
}

void loop()
{
  inputstateReadTest();   // Test odczytu stanów wejść MCP. Stany zapisywane w input_id[][]
  input_interpretation(); // Funkcja do interpretacji wejść. Zapis działań w match_table[][]
  writeOutputStates();    // Funkcja do obsługi wyjść (przekaźników). Wykonuje działania zapisane w match_table[][]
  lcd_clear();            // Funkcja do czyszczenia ekranu LCD po określonym czasie braku aktywności
  postRequest_loop();     //Funkcja do wysyłania danych na serwer do plików json
  json_readLoop();        //Funkcja do odczytu danych z plików json na serwerze
}
