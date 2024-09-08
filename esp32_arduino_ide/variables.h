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