#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"

 
void setup() {
  psetup();
  mcp_setup();
}

void loop() {
  inputstateReadTest();  // Test odczytu stanów wejść MCP
}
