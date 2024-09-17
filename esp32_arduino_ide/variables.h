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

byte cn_object_areas = 2;
String object_areas[6][2]{
  {"AREA_1", "PARTER POM. MIESZKALNE"},
  {"AREA_2", "PARTER POM. TECHNICZNE"},
  {"AREA_3", "PIETRO POM. MIESZKALNE"},
  {"AREA_4", "PIETRO POM. TECHNICZNE"},
  {"AREA_5", "TEST 1"},
  {"AREA_6", "TEST 2"}
};
int sizeOfArray_object_areas = (sizeof(object_areas) / sizeof(object_areas[0][0])) / cn_object_areas;

//tablica obiektów typu roleta
byte cn_rollers = 5;
String rollers[6][5]{
  { "1", "Roleta 1", "AREA_1", "0", "15" },
  { "2", "Roleta 2", "AREA_2", "0", "16" },
  { "3", "Roleta 3", "AREA_1", "0", "17" },
  { "4", "Roleta 4", "AREA_1", "0", "12" },
  { "5", "Roleta 5", "AREA_1", "0", "12" },
  { "6", "Roleta 6", "AREA_1", "0", "12" }
};
int sizeOfArray_rollers = (sizeof(rollers) / sizeof(rollers[0][0])) / cn_rollers;
