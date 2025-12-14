#ifndef FUNCTIONS_H 
#define FUNCTIONS_H 

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

#endif