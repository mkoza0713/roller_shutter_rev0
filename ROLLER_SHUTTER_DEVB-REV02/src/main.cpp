#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"


void setup() {
  psetup();
  mcp_setup();
}

void loop() {
  if(interrupt_flag) main_handleInterrupt();//wejscie w przerwanie
  if(interrupt_flag) shutter_work();
}
