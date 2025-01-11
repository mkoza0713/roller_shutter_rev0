#include <Arduino.h>
#include "functions.h"
#include "global_variables.h"


void setup() {
  psetup();
}

void loop() {
  if(interrupt_flag) main_handleInterrupt();//wejscie w przerwanie
}
