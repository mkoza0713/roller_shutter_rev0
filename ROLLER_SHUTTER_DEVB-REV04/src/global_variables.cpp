#include "global_variables.h"

// ---------------------------
// Definicje obiektów MCP23008
// ---------------------------
Adafruit_MCP23008 MCP_1;
Adafruit_MCP23008 MCP_2;
Adafruit_MCP23008 MCP_3;
Adafruit_MCP23008 MCP_4;
Adafruit_MCP23008 MCP_5;
Adafruit_MCP23008 MCP_6;
Adafruit_MCP23008 MCP_7;
Adafruit_MCP23008 MCP_8;

// ---------------------------
// Flagi obecności MCP (na start wszystkie false)
// ---------------------------
bool test_mpc_1 = false;
bool test_mpc_2 = false;
bool test_mpc_3 = false;
bool test_mpc_4 = false;
bool test_mpc_5 = false;
bool test_mpc_6 = false;
bool test_mpc_7 = false;
bool test_mpc_8 = false;

// ---------------------------
// Tablica wskaźników do MCP
// ---------------------------
Adafruit_MCP23008* MCPs[8] = { 
  &MCP_1, &MCP_2, &MCP_3, &MCP_4, 
  &MCP_5, &MCP_6, &MCP_7, &MCP_8 
};

// ---------------------------
// Tablica wskaźników do flag testowych
// ---------------------------
bool* test_mpc_flags[8] = { 
  &test_mpc_1, &test_mpc_2, &test_mpc_3, &test_mpc_4,
  &test_mpc_5, &test_mpc_6, &test_mpc_7, &test_mpc_8 
};

// ---------------------------
// Tablica stanów wejść - 9 MCP, 4 wejścia każdy
// ---------------------------
int last_state[8][8];                 
unsigned long last_change_time[8][8]; 

int debonuce_time = 200; // czas drgania styków w ms

// ---------------------------
// Dane rolet: id, nazwa, strefa, czas cyklu, stan: 1 otwarta 0 zamknieta, poziom otwarcia
// ---------------------------
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

//id wejscia; stan wejścia (0/1/puste)
String input_id[32][2] = {
  {"inp1_1", ""},
  {"inp1_2", ""},
  {"inp1_3", ""},
  {"inp1_4", ""},
  {"inp2_1", ""},
  {"inp2_2", ""},
  {"inp2_3", ""},
  {"inp2_4", ""},
  {"inp3_1", ""},
  {"inp3_2", ""},
  {"inp3_3", ""},
  {"inp3_4", ""},
  {"inp4_1", ""},
  {"inp4_2", ""},
  {"inp4_3", ""},
  {"inp4_4", ""},
  {"inp5_1", ""},
  {"inp5_2", ""},
  {"inp5_3", ""},
  {"inp5_4", ""},
  {"inp6_1", ""},
  {"inp6_2", ""},
  {"inp6_3", ""},
  {"inp6_4", ""},
  {"inp7_1", ""},
  {"inp7_2", ""},
  {"inp7_3", ""},
  {"inp7_4", ""},
  {"inp8_1", ""},
  {"inp8_2", ""},
  {"inp8_3", ""},
  {"inp8_4", ""}
};

//id rolety; 
//id wejscia; 
//działanie do wykonania (1,2,3 - krótkie, długie, bardzo długie wcisniecie)
String match_table[17][3] = {
  {"id0", "", ""},
  {"id1", "inp1_1", ""},
  {"id2", "inp1_2", ""},
  {"id3", "inp2_1", ""},
  {"id4", "inp2_2", ""},
  {"id5", "inp3_1", ""},
  {"id6", "inp3_2", ""},
  {"id7", "inp4_1", ""},
  {"id8", "inp4_2", ""},
  {"id9", "inp5_1", ""},
  {"id10", "inp5_2", ""},
  {"id11", "inp6_1", ""},
  {"id12", "inp6_2", ""},
  {"id13", "inp7_1", ""},
  {"id14", "inp7_2", ""},
  {"id15", "inp8_1", ""},
  {"id16", "inp8_2", ""}
};

// ---------------------------
// Czas startu dla rolet (inicjalizacja 0)
// ---------------------------
unsigned long startTimeForShutter[17] = {0};


// ---------------------------
// odmierzanie czasu przyciskow (inicjalizacja 0)
// ---------------------------
unsigned long buttonPressTime[32] = {0};