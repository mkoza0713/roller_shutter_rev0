#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"

void writeOutputStates(){
    // Tutaj dodaj kod do obsługi wyjść (przekaźników) na MCP23008
    for(byte i=0; i<32; i++){
        Serial.println("Input ID: " + input_id[i][0] + " State: " + input_id[i][1]);
    }

}