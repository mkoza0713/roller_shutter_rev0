#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

int x, y, z;
int lock_key_1 = 1;      //zmienna dotyku przyciskow
int screen_changer = 1;  //zmienna kolejnych ekranów w menu
int screen_sum = 3;      //zmienna kolejnych ekranów w menu - suma max

byte fontHeigh = 10;  //dodałem wiecej aby zrobic padding pom tekstem
uint32_t button_colour = '0x7BEF';
uint32_t button_insert_colour = '0x867D';
uint32_t empty_colour = 'TFT_WHITE';


byte cn_object_areas = 3;//columns
String object_areas[6][3]{  //area/name of area/ no of rollers in area (counted by f())
  { "AREA_1", "PARTER POM. MIESZKALNE",  "0"},
  { "AREA_2", "PARTER POM. TECHNICZNE",  "0"},
  { "AREA_3", "PIETRO POM. MIESZKALNE",  "0"},
  { "AREA_4", "PIETRO POM. TECHNICZNE",  "0"},
  { "AREA_5", "TEST 1", "0"},
  { "AREA_6", "TEST 2",  "0"}
};
int sizeOfArray_object_areas = (sizeof(object_areas) / sizeof(object_areas[0][0])) / cn_object_areas;  //liczba wierszy

//tablica obiektów typu roleta
byte cn_rollers = 9;  //columns
String rollers[11][9]{  //id, name, area, start time ms, stop time ms, if checkbox checked, open/close stage(1 open 0 close), poziom otwarcia 0 otwarty,100, zamkniety,pozycja na ekranie
  { "1", "Roleta 1", "AREA_1", "0", "9000", "0" , "1", "0", "0"},
  { "2", "Roleta 2", "AREA_2", "0", "16000", "0" , "0", "100", "0"},
  { "3", "Roleta 3", "AREA_1", "0", "10000", "0" , "0", "100", "0"},
  { "4", "Roleta 4", "AREA_1", "0", "6000", "0" , "0", "100", "0"},
  { "5", "Roleta 5", "AREA_1", "0", "5000", "0" , "1", "0", "0"},
  { "6", "Roleta 6", "AREA_1", "0", "2000", "0" , "0", "100", "0"},
  { "7", "Roleta 7", "AREA_3", "0", "12000", "0" , "0", "100", "0"},
  { "8", "Roleta 8", "AREA_3", "0", "12000", "0" , "0", "100", "0"},
  { "9", "Roleta 9", "AREA_4", "0", "12000", "0" , "1", "0", "0"},
  { "10", "Roleta 10", "AREA_4", "0", "12000", "0" , "0", "100", "0"},
  { "11", "Roleta 11", "AREA_5", "0", "12000", "0" , "1", "0", "0"}
};

int sizeOfArray_rollers = (sizeof(rollers) / sizeof(rollers[0][0])) / cn_rollers;  //liczba wierszy

unsigned long start_millis_time=0;  //start odliczania czasu do dzaialnia przekaznika
