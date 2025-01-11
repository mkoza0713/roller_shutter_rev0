#include "Arduino.h"
bool interrupt_flag = false;
//sprawdzanie ilosci urzadzec i2c
bool test_mpc_1 = false;
bool test_mpc_2 = false;
bool test_mpc_3 = false;
bool test_mpc_4 = false;
bool test_mpc_5 = false;
bool test_mpc_6 = false;
bool test_mpc_7 = false;
bool test_mpc_8 = false;

//tablica stanow przyciskow
int value_of_input[9][4];

//id// name// area// start time ms// cycle time ms// open/close stage(1 open 0 close)/ poziom otwarcia 0 otwarty,100, zamkniety/pozycja na ekranie
/*
ID
name
area name
cycle time
open stage (1 - close)
open progres (0 - open, 100 - close)
mpc id
 */
String rollers[11][9]{  
  { "1", "Roleta 1", "AREA_1", "9000", "1", "0"},
  { "2", "Roleta 2", "AREA_2", "16000", "0", "100"},
  { "3", "Roleta 3", "AREA_1", "10000", "0", "100"},
  { "4", "Roleta 4", "AREA_1", "6000", "0", "100"},
  { "5", "Roleta 5", "AREA_1", "5000", "1", "0"},
  { "6", "Roleta 6", "AREA_1", "2000", "0", "100"},
  { "7", "Roleta 7", "AREA_3", "12000", "0", "100"},
  { "8", "Roleta 8", "AREA_3", "12000", "0", "100"},
  { "9", "Roleta 9", "AREA_4", "12000", "1", "0"},
  { "10", "Roleta 10", "AREA_4", "12000", "0", "100"},
  { "11", "Roleta 11", "AREA_5", "12000", "1", "0"}
};

//Pary wejsc ktorw nie moga byc wcisniete na raz
String input_paar[16][2]{
    {"1.1", "1.2"},
    {"1.3", "1.4"},
    {"2.1", "2.2"},
    {"2.3", "2.4"},
    {"3.1", "3.2"},
    {"3.3", "3.4"},
    {"4.1", "4.2"},
    {"4.3", "4.4"},
    {"5.1", "5.2"},
    {"5.3", "5.4"},
    {"6.1", "6.2"},
    {"6.3", "6.4"},
    {"7.1", "7.2"},
    {"7.3", "7.4"},
    {"8.1", "8.2"},
    {"8.3", "8.4"}
};