#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "global_variables.h"
#include "functions.h"

void writeOutputStates(){
    // Tutaj dodaj kod do obsługi wyjść (przekaźników) na MCP23008
    for(byte i=0; i<32; i++){
        if(input_id[i][1] == "1"){
            // Przykładowa akcja: włącz przekaźnik lub wykonaj inną operację
            Serial.print("Input ID ");
            if(i>0 && i<=3){
                // MCP1 piny 0-3
                Serial.println(i);
            }
            else if(i>=4 && i<=7){
                // MCP2 piny 0-3
                Serial.println(i-4);
            }
            else if(i>=8 && i<=11){
                // MCP3 piny 0-3
                Serial.println(i-8);
            }
            else if(i>=12 && i<=15){
                // MCP4 piny 0-3
                Serial.println(i-12);
            }
            else if(i>=16 && i<=19){
                // MCP5 piny 0-3
                Serial.println(i-16);
            }
            else if(i>=20 && i<=23){
                // MCP6 piny 0-3
                Serial.println(i-20);
            }
            else if(i>=24 && i<=27){
                // MCP7 piny 0-3
                Serial.println(i-24);
            }
            else if(i>=28 && i<=31){
                // MCP8 piny 0-3
                Serial.println(i-28);
            }
        }
    }

}