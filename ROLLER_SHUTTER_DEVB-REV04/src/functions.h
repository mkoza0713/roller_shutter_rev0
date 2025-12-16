#ifndef FUNCTIONS_H 
#define FUNCTIONS_H 
#include <Adafruit_MCP23008.h>

void psetup(); 
void mcp_setup();
void inputstateReadTest();
void lcdShowCenterText(String message);
void lcdShowTopTextAdd(String message);
void lcd_clear();
void writeOutputStates();
void input_interpretation();
String createJSON();
void postRequest_loop();
void json_readLoop();
time_t getCurrentTimestamp();
void monitorI2CBus(uint32_t timeoutMs);
bool safeMcpWrite(Adafruit_MCP23008 *mcp, uint8_t pin, bool state);

#endif