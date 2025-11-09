#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <Arduino.h>
#include "Adafruit_MCP23008.h"

extern Adafruit_MCP23008 MCP_1;
extern Adafruit_MCP23008 MCP_2;
extern Adafruit_MCP23008 MCP_3;
extern Adafruit_MCP23008 MCP_4;
extern Adafruit_MCP23008 MCP_5;
extern Adafruit_MCP23008 MCP_6;
extern Adafruit_MCP23008 MCP_7;
extern Adafruit_MCP23008 MCP_8;

// Definicje pinów i adresów I2C MCP23008
#define int_pin_esp 35
#define MCP1_ADDRESS 0x20
#define MCP2_ADDRESS 0x21
#define MCP3_ADDRESS 0x22
#define MCP4_ADDRESS 0x23
#define MCP5_ADDRESS 0x24
#define MCP6_ADDRESS 0x25
#define MCP7_ADDRESS 0x26
#define MCP8_ADDRESS 0x27

// Flagi obecności MCP
extern bool test_mpc_1;
extern bool test_mpc_2;
extern bool test_mpc_3;
extern bool test_mpc_4;
extern bool test_mpc_5;
extern bool test_mpc_6;
extern bool test_mpc_7;
extern bool test_mpc_8;

extern Adafruit_MCP23008 *MCPs[8];
extern bool *test_mpc_flags[8];

// Tablica stanów wejść (9 mpc, 4 wejścia na mpc)
extern int value_of_input[9][4];

// Dane rolet: id, nazwa, strefa, czas cyklu, open stage (1=open, 0=close), poziom otwarcia (0-otwarty, 100-zamknięty)
extern String rollers[17][6];

// Czas startu dla rolet (milisekundy)
extern unsigned long startTimeForShutter[17];

#endif
