#include "global_variables.h"

// Flagi obecności MCP (na start wszystkie false)
bool test_mpc_1 = false;
bool test_mpc_2 = false;
bool test_mpc_3 = false;
bool test_mpc_4 = false;
bool test_mpc_5 = false;
bool test_mpc_6 = false;
bool test_mpc_7 = false;
bool test_mpc_8 = false;

// Tablica stanów wejść - 9 MPC, 4 wejścia każdy
int value_of_input[9][4] = {0};

// Dane rolet
String rollers[17][6] = {
  {"id0", "n/d", "n/d", "n/d", "n/d", "n/d"},
  {"id1", "Roleta 1", "AREA_1", "9000", "1", "0"},
  {"id2", "Roleta 2", "AREA_2", "16000", "0", "16000"},
  {"id3", "Roleta 3", "AREA_1", "10000", "1", "0"},
  {"id4", "Roleta 4", "AREA_1", "6000", "1", "0"},
  {"id5", "Roleta 5", "AREA_1", "5000", "1", "0"},
  {"id6", "Roleta 6", "AREA_1", "2000", "0", "2000"},
  {"id7", "Roleta 7", "AREA_3", "12000", "0", "12000"},
  {"id8", "Roleta 8", "AREA_3", "12000", "0", "12000"},
  {"id9", "Roleta 9", "AREA_4", "12000", "1", "0"},
  {"id10", "Roleta 10", "AREA_4", "12000", "0", "12000"},
  {"id11", "Roleta 11", "AREA_5", "12000", "1", "0"},
  {"id12", "Roleta 12", "AREA_5", "12000", "1", "0"},
  {"id13", "Roleta 13", "AREA_5", "12000", "1", "0"},
  {"id14", "Roleta 14", "AREA_5", "12000", "1", "0"},
  {"id15", "Roleta 15", "AREA_5", "12000", "1", "0"},
  {"id16", "Roleta 16", "AREA_5", "12000", "1", "0"}
};

// Czas startu dla rolet (inicjalizacja 0)
unsigned long startTimeForShutter[17] = {0};
