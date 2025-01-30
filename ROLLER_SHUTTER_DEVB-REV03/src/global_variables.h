#ifndef GLOBAL_VARIABLES_H 
#define GLOBAL_VARIABLES_H 

#define int_pin_esp 35
extern bool test_mpc_1;
extern bool test_mpc_2;
extern bool test_mpc_3;
extern bool test_mpc_4;
extern bool test_mpc_5;
extern bool test_mpc_6;
extern bool test_mpc_7;
extern bool test_mpc_8;

//adresy I2C
#define MCP1_ADDRESS 0x20
#define MCP2_ADDRESS 0x21
#define MCP3_ADDRESS 0x22
#define MCP4_ADDRESS 0x23
#define MCP5_ADDRESS 0x24
#define MCP6_ADDRESS 0x25
#define MCP7_ADDRESS 0x26
#define MCP8_ADDRESS 0x27

extern int value_of_input[9][4];
extern String rollers[12][6];
extern String input_paar[6][4];
extern unsigned long startTimeForShutter[17];
#endif