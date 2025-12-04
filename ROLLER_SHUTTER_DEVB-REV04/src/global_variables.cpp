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
// Dane rolet: id (0), nazwa (1), strefa(2), czas cyklu ms(3), 
//stan: 1 pracuje 0 nie pracuje(4), poziom otwarcia % 100% otwarta(5),
//poprzedni kierunek: 1-góra, 0-dół (6)
// ---------------------------
String rollers[17][7] = {
  {"id0", "n/d", "n/d", "n/d", "n/d", "n/d", "n/d"},
  {"id1", "Kuchnia", "AREA_1", "9000", "0", "100", "1"},
  {"id2", "Jadalnia 1", "AREA_1", "16000", "0", "100", "1"},
  {"id3", "Jadalnia 2", "AREA_1", "10000", "0", "100", "1"},
  {"id4", "Salon 1", "AREA_1", "6000", "0", "100", "1"},
  {"id5", "Salon 2", "AREA_1", "5000", "0", "100", "1"},
  {"id6", "Lazienka dol", "AREA_2", "2000", "0", "100", "1"},
  {"id7", "Gabinet", "AREA_3", "12000", "0", "100", "1"},
  {"id8", "Kotlownia", "AREA_4", "10000", "0", "100", "1"},
  {"id9", "Garaz", "AREA_4", "10000", "0", "100", "1"},
  {"id10", "Strych", "AREA_4", "5000", "0", "100", "1"},
  {"id11", "Lazienka gora", "AREA_5", "12000", "0", "100", "1"},
  {"id12", "Pokoj Oskara", "AREA_5", "12000", "0", "100", "1"},
  {"id13", "Pokoj roddzicow", "AREA_5", "12000", "0", "100", "1"},
  {"id14", "Okno n schodami", "AREA_6", "12000", "0", "100", "1"},
  {"id15", "Roleta 15", "AREA_7", "12000", "0", "100", "1"},
  {"id16", "Roleta 16", "AREA_7", "12000", "0", "100", "1"}
};

//czasy start do pracy rolet
//0 - czas startu otwierania
unsigned long time_start_f0r_work[17][1];

//id wejscia; 
//stan wejścia (0/1/puste) 0 - puszczono, 1 - wciśnięto, puste - brak akcji
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

//id wyjscia;
//numer mcp
//adres wyjścia na MCP23008
String output_id[32][3]= {
  {"out1_1", "1", "0"},
  {"out1_2", "1", "1"},
  {"out1_3", "1", "2"},
  {"out1_4", "1", "3"},
  {"out2_1", "2", "0"},
  {"out2_2", "2", "1"},
  {"out2_3", "2", "2"},
  {"out2_4", "2", "3"},
  {"out3_1", "3", "0"},
  {"out3_2", "3", "1"},
  {"out3_3", "3", "2"},
  {"out3_4", "3", "3"},
  {"out4_1", "4", "0"},
  {"out4_2", "4", "1"},
  {"out4_3", "4", "2"},
  {"out4_4", "4", "3"},
  {"out5_1", "5", "7"},
  {"out5_2", "5", "1"},
  {"out5_3", "5", "2"},
  {"out5_4", "5", "3"},
  {"out6_1", "6", "7"},
  {"out6_2", "6", "1"},
  {"out6_3", "6", "2"},
  {"out6_4", "6", "3"},
  {"out7_1", "7", "7"},
  {"out7_2", "7", "1"},
  {"out7_3", "7", "2"},
  {"out7_4", "7", "3"},
  {"out8_1", "8", "7"},
  {"out8_2", "8", "1"},
  {"out8_3", "8", "2"},
  {"out8_4", "8", "3"}
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

//id rolety;
//id wyjscia 1 - otwieranie
//id wyjscia 2 - zamykanie
//info czy podpiete mcp
String match_table_output[17][4] = {
  {"id0", "", "",""},
  {"id1", "out1_1", "out1_2",""},
  {"id2", "out1_3", "out1_4",""},
  {"id3", "out2_1", "out2_2",""},
  {"id4", "out2_3", "out2_4",""},
  {"id5", "out3_1", "out3_2",""},
  {"id6", "out3_3", "out3_4",""},
  {"id7", "out4_1", "out4_2",""},
  {"id8", "out4_3", "out4_4",""},
  {"id9", "out5_1", "out5_2",""},
  {"id10", "out5_3", "out5_4",""},
  {"id11", "out6_1", "out6_2",""},
  {"id12", "out6_3", "out6_4",""},
  {"id13", "out7_1", "out7_2",""},
  {"id14", "out7_3", "out7_4",""},
  {"id15", "out8_1", "out8_2",""},
  {"id16", "out8_3", "out8_4",""}
};

// ---------------------------
// Czas startu dla rolet (inicjalizacja 0)
// ---------------------------
unsigned long startTimeForShutter[17] = {0};


// ---------------------------
// odmierzanie czasu przyciskow (inicjalizacja 0)
// ---------------------------
unsigned long buttonPressTime[32] = {0};



/***********WIFI**************/
// const char ssid[] = "UPC7AA1BAF";
// const char password[] = "Ra5xvvsxcpdj";
const char ssid[] = "T-Mobile-ZTE MF286-83954E";
const char password[] = "Maniek104";


String HOST_NAME = "https://srv97872.seohost.com.pl";  // REPLACE WITH YOUR PC's IP ADDRESS
String PHP_FILE_NAME = "/connectEspRollerShutter.php";         //REPLACE WITH YOUR PHP FILE NAME
String server = "";


/***********WIFI**************/

/***********LCD**************/
unsigned long last_action_time;
unsigned long lcd_clear_timeout = 30000; // czas w s po którym ekran się wyczyści
/***********LCD**************/