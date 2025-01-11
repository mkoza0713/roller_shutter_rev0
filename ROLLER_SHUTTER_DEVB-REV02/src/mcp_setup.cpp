#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "functions.h"
#include "global_variables.h"

Adafruit_MCP23008 MCP_1;
Adafruit_MCP23008 MCP_2;
Adafruit_MCP23008 MCP_3;
Adafruit_MCP23008 MCP_4;
Adafruit_MCP23008 MCP_5;
Adafruit_MCP23008 MCP_6;
Adafruit_MCP23008 MCP_7;
Adafruit_MCP23008 MCP_8;

void mcp_setup()
{
    // Inicjalizacja MCP23008
    test_mpc_1 = MCP_1.begin(MCP1_ADDRESS);
    test_mpc_2 = MCP_2.begin(MCP2_ADDRESS);
    test_mpc_3 = MCP_3.begin(MCP3_ADDRESS);
    test_mpc_4 = MCP_4.begin(MCP4_ADDRESS);
    test_mpc_5 = MCP_5.begin(MCP5_ADDRESS);
    test_mpc_6 = MCP_6.begin(MCP6_ADDRESS);
    test_mpc_7 = MCP_7.begin(MCP7_ADDRESS);
    test_mpc_8 = MCP_8.begin(MCP8_ADDRESS);

    // Ustawienie pinów 4-7 jako wejścia i włączenie podciągania rezystorów
    for (byte i = 4; i < 8; i++)
    {
        if (test_mpc_1)
        {
            MCP_1.pinMode(i, INPUT);
            MCP_1.pullUp(i, HIGH);
        }
        if (test_mpc_2)
        {
            MCP_2.pinMode(i, INPUT);
            MCP_2.pullUp(i, HIGH);
        }
        if (test_mpc_3)
        {
            MCP_3.pinMode(i, INPUT);
            MCP_3.pullUp(i, HIGH);
        }
        if (test_mpc_4)
        {
            MCP_4.pinMode(i, INPUT);
            MCP_4.pullUp(i, HIGH);
        }
        if (test_mpc_5)
        {
            MCP_5.pinMode(i, INPUT);
            MCP_5.pullUp(i, HIGH);
        }
        if (test_mpc_6)
        {
            MCP_6.pinMode(i, INPUT);
            MCP_6.pullUp(i, HIGH);
        }
        if (test_mpc_7)
        {
            MCP_7.pinMode(i, INPUT);
            MCP_7.pullUp(i, HIGH);
        }
        if (test_mpc_8)
        {
            MCP_8.pinMode(i, INPUT);
            MCP_8.pullUp(i, HIGH);
        }
    }
    // ustawiam piny  0-3 jako wyjscia dla przekaznikow
    for (byte i = 0; i < 4; i++)
    {
        if (test_mpc_1)
        {
            MCP_1.pinMode(i, OUTPUT);
            MCP_1.digitalWrite(i, LOW);
        }
        if (test_mpc_2)
        {
            MCP_2.pinMode(i, OUTPUT);
            MCP_2.digitalWrite(i, LOW);
        }
        if (test_mpc_3)
        {
            MCP_3.pinMode(i, OUTPUT);
            MCP_3.digitalWrite(i, LOW);
        }
        if (test_mpc_4)
        {
            MCP_4.pinMode(i, OUTPUT);
            MCP_4.digitalWrite(i, LOW);
        }
        if (test_mpc_5)
        {
            MCP_5.pinMode(i, OUTPUT);
            MCP_5.digitalWrite(i, LOW);
        }
        if (test_mpc_6)
        {
            MCP_6.pinMode(i, OUTPUT);
            MCP_6.digitalWrite(i, LOW);
        }
        if (test_mpc_7)
        {
            MCP_7.pinMode(i, OUTPUT);
            MCP_7.digitalWrite(i, LOW);
        }
        if (test_mpc_8)
        {
            MCP_8.pinMode(i, OUTPUT);
            MCP_8.digitalWrite(i, LOW);
        }
    }

    // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
    if (test_mpc_1)
    {
        String messageToPrint = "MCP23008 with address:" + String(MCP1_ADDRESS) + " connected";
        Serial.println(messageToPrint);
        Wire.beginTransmission(MCP1_ADDRESS);
        Wire.write(0x02); // MCP23008_GPINTEN
        Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
        Wire.endTransmission();
        Serial.println("GPINTEN configured");

        Wire.beginTransmission(MCP1_ADDRESS);
        Wire.write(0x04); // MCP23008_INTCON
        Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
        Wire.endTransmission();
        Serial.println("INTCON configured");

        Wire.beginTransmission(MCP1_ADDRESS);
        Wire.write(0x03); // MCP23008_DEFVAL
        Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
        Wire.endTransmission();
        Serial.println("DEFVAL configured");
    }
    if (test_mpc_2)
    {
        // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
        String messageToPrint = "MCP23008 with address:" + String(MCP2_ADDRESS) + " connected";
        Serial.println(messageToPrint);
        Wire.beginTransmission(MCP2_ADDRESS);
        Wire.write(0x02); // MCP23008_GPINTEN
        Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
        Wire.endTransmission();
        Serial.println("GPINTEN configured");

        Wire.beginTransmission(MCP2_ADDRESS);
        Wire.write(0x04); // MCP23008_INTCON
        Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
        Wire.endTransmission();
        Serial.println("INTCON configured");

        Wire.beginTransmission(MCP2_ADDRESS);
        Wire.write(0x03); // MCP23008_DEFVAL
        Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
        Wire.endTransmission();
        Serial.println("DEFVAL configured");
    }
    if (test_mpc_3)
    {
        // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
        String messageToPrint = "MCP23008 with address:" + String(MCP3_ADDRESS) + " connected";
        Serial.println(messageToPrint);
        Wire.beginTransmission(MCP3_ADDRESS);
        Wire.write(0x02); // MCP23008_GPINTEN
        Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
        Wire.endTransmission();
        Serial.println("GPINTEN configured");

        Wire.beginTransmission(MCP3_ADDRESS);
        Wire.write(0x04); // MCP23008_INTCON
        Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
        Wire.endTransmission();
        Serial.println("INTCON configured");

        Wire.beginTransmission(MCP3_ADDRESS);
        Wire.write(0x03); // MCP23008_DEFVAL
        Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
        Wire.endTransmission();
        Serial.println("DEFVAL configured");
    }
    if (test_mpc_4)
    {
        // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
        String messageToPrint = "MCP23008 with address:" + String(MCP4_ADDRESS) + " connected";
        Serial.println(messageToPrint);
        Wire.beginTransmission(MCP4_ADDRESS);
        Wire.write(0x02); // MCP23008_GPINTEN
        Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
        Wire.endTransmission();
        Serial.println("GPINTEN configured");

        Wire.beginTransmission(MCP4_ADDRESS);
        Wire.write(0x04); // MCP23008_INTCON
        Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
        Wire.endTransmission();
        Serial.println("INTCON configured");

        Wire.beginTransmission(MCP4_ADDRESS);
        Wire.write(0x03); // MCP23008_DEFVAL
        Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
        Wire.endTransmission();
        Serial.println("DEFVAL configured");
    }
    if (test_mpc_5)
    {
        // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
        String messageToPrint = "MCP23008 with address:" + String(MCP5_ADDRESS) + " connected";
        Serial.println(messageToPrint);
        Wire.beginTransmission(MCP5_ADDRESS);
        Wire.write(0x02); // MCP23008_GPINTEN
        Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
        Wire.endTransmission();
        Serial.println("GPINTEN configured");

        Wire.beginTransmission(MCP5_ADDRESS);
        Wire.write(0x04); // MCP23008_INTCON
        Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
        Wire.endTransmission();
        Serial.println("INTCON configured");

        Wire.beginTransmission(MCP5_ADDRESS);
        Wire.write(0x03); // MCP23008_DEFVAL
        Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
        Wire.endTransmission();
        Serial.println("DEFVAL configured");
    }
    if (test_mpc_6)
    {
        // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
        String messageToPrint = "MCP23008 with address:" + String(MCP6_ADDRESS) + " connected";
        Serial.println(messageToPrint);
        Wire.beginTransmission(MCP6_ADDRESS);
        Wire.write(0x02); // MCP23008_GPINTEN
        Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
        Wire.endTransmission();
        Serial.println("GPINTEN configured");

        Wire.beginTransmission(MCP6_ADDRESS);
        Wire.write(0x04); // MCP23008_INTCON
        Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
        Wire.endTransmission();
        Serial.println("INTCON configured");

        Wire.beginTransmission(MCP6_ADDRESS);
        Wire.write(0x03); // MCP23008_DEFVAL
        Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
        Wire.endTransmission();
        Serial.println("DEFVAL configured");
    }
    if (test_mpc_7)
    {
        // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
        String messageToPrint = "MCP23008 with address:" + String(MCP7_ADDRESS) + " connected";
        Serial.println(messageToPrint);
        Wire.beginTransmission(MCP7_ADDRESS);
        Wire.write(0x02); // MCP23008_GPINTEN
        Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
        Wire.endTransmission();
        Serial.println("GPINTEN configured");

        Wire.beginTransmission(MCP7_ADDRESS);
        Wire.write(0x04); // MCP23008_INTCON
        Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
        Wire.endTransmission();
        Serial.println("INTCON configured");

        Wire.beginTransmission(MCP7_ADDRESS);
        Wire.write(0x03); // MCP23008_DEFVAL
        Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
        Wire.endTransmission();
        Serial.println("DEFVAL configured");
    }
    if (test_mpc_8)
    {
        // Konfiguracja przerwań MCP23008 tylko dla pinów 4-7
        String messageToPrint = "MCP23008 with address:" + String(MCP7_ADDRESS) + " connected";
        Serial.println(messageToPrint);
        Wire.beginTransmission(MCP8_ADDRESS);
        Wire.write(0x02); // MCP23008_GPINTEN
        Wire.write(0xF0); // Włączenie przerwań na pinach 4-7 (bity 4-7 ustawione na 1)
        Wire.endTransmission();
        Serial.println("GPINTEN configured");

        Wire.beginTransmission(MCP8_ADDRESS);
        Wire.write(0x04); // MCP23008_INTCON
        Wire.write(0x00); // Ustawienie przerwań na zmianę stanu
        Wire.endTransmission();
        Serial.println("INTCON configured");

        Wire.beginTransmission(MCP8_ADDRESS);
        Wire.write(0x03); // MCP23008_DEFVAL
        Wire.write(0x00); // Domyślna wartość dla porównań (nieistotna przy INTCON = 0x00)
        Wire.endTransmission();
        Serial.println("DEFVAL configured");
    }

    // Konfiguracja przerwania na Arduino
    pinMode(int_pin_esp, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(int_pin_esp), handleInterrupt, FALLING);
    Serial.println("Interrupt attached");
}