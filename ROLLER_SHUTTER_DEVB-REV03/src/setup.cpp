#include "Arduino.h"

void psetup()
{
    Serial.begin(115200);
    delay(5000);
    Serial.println("start programu");
}