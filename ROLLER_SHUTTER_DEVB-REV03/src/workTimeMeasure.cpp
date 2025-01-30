#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"
#include "Adafruit_MCP23008.h"

// Declare MCP variables
extern Adafruit_MCP23008 MCP_1;
extern Adafruit_MCP23008 MCP_2;
extern Adafruit_MCP23008 MCP_3;
extern Adafruit_MCP23008 MCP_4;
extern Adafruit_MCP23008 MCP_5;
extern Adafruit_MCP23008 MCP_6;
extern Adafruit_MCP23008 MCP_7;
extern Adafruit_MCP23008 MCP_8;


void work_time_measure()
{
  for (int i = 1; i < 17; i++)
  {
    if (startTimeForShutter[i] != 0)
    {

      //Serial.println(millis() - startTimeForShutter[i]);
      if (millis() - startTimeForShutter[i] >= rollers[i][3].toInt())
      {
        String string_to_print = "Roleta: " + rollers[i][1] + " zakończyła pracę";
        Serial.println(string_to_print);
        startTimeForShutter[i] = 0;
        if(rollers[i][4]=="0")rollers[i][4]="1";
        else if(rollers[i][4]=="1")rollers[i][4]="0";

        switch (i)
        {
        case 1:
          MCP_1.digitalWrite(0, LOW);
          MCP_1.digitalWrite(1, LOW);
          break;
        case 2:
          MCP_1.digitalWrite(2, LOW);
          MCP_1.digitalWrite(3, LOW);
          break;
        case 3:
          MCP_2.digitalWrite(0, LOW);
          MCP_2.digitalWrite(1, LOW);
          break;
        case 4:
          MCP_2.digitalWrite(2, LOW);
          MCP_2.digitalWrite(3, LOW);
          break;
        case 5:
          MCP_3.digitalWrite(0, LOW);
          MCP_3.digitalWrite(1, LOW);
          break;
        case 6:
          MCP_3.digitalWrite(2, LOW);
          MCP_3.digitalWrite(3, LOW);
          break;
        case 7:
          MCP_4.digitalWrite(0, LOW);
          MCP_4.digitalWrite(1, LOW);
          break;
        case 8:
          MCP_4.digitalWrite(2, LOW);
          MCP_4.digitalWrite(3, LOW);
          break;
        case 9:
          MCP_5.digitalWrite(0, LOW);
          MCP_5.digitalWrite(1, LOW);
          break;
        case 10:
          MCP_5.digitalWrite(2, LOW);
          MCP_5.digitalWrite(3, LOW);
          break;
        case 11:
          MCP_6.digitalWrite(0, LOW);
          MCP_6.digitalWrite(1, LOW);
          break;
        case 12:
          MCP_6.digitalWrite(2, LOW);
          MCP_6.digitalWrite(3, LOW);
          break;
        case 13:
          MCP_7.digitalWrite(0, LOW);
          MCP_7.digitalWrite(1, LOW);
          break;
        case 14:
          MCP_7.digitalWrite(2, LOW);
          MCP_7.digitalWrite(3, LOW);
          break;
        case 15:
          MCP_8.digitalWrite(0, LOW);
          MCP_8.digitalWrite(1, LOW);
          break;
        case 16:
          MCP_8.digitalWrite(2, LOW);
          MCP_8.digitalWrite(3, LOW);
          break;
        }
      }
    }
  }
}