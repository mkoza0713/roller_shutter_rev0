#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"


void setup() {
  psetup();
  mcp_setup();
}

void loop() {
  Serial.println("test");
  inputStateRead();
  work_time_measure();
}
