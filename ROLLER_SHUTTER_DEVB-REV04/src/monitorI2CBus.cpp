#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"
#include <Wire.h>

#define I2C_SDA 27
#define I2C_SCL 22
#define I2C_FREQ 100000

static uint32_t i2cBusySince = 0;

bool i2cBusFree()
{
    pinMode(I2C_SDA, INPUT_PULLUP);
    pinMode(I2C_SCL, INPUT_PULLUP);
    return (digitalRead(I2C_SDA) == HIGH && digitalRead(I2C_SCL) == HIGH);
}

void i2cRecover()
{
    Serial.println("START RESETU MAGITRALI I2C");

    pinMode(I2C_SCL, OUTPUT);
    pinMode(I2C_SDA, INPUT_PULLUP);

    for (uint8_t i = 0; i < 9; i++)
    {
        digitalWrite(I2C_SCL, HIGH);
        delayMicroseconds(5);
        digitalWrite(I2C_SCL, LOW);
        delayMicroseconds(5);
    }

    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(I2C_FREQ);

    Serial.println("RESET MAGITRALI I2C ZAKONCZONY");
    lcdShowTopTextAdd("RESET ZAKONCZONY");
}

void monitorI2CBus(uint32_t timeoutMs)
{
    if (i2cBusFree())
    {
        i2cBusySince = 0;
        return;
    }

    if (i2cBusySince == 0)
    {
        i2cBusySince = millis();
        return;
    }

    // if (millis() - i2cBusySince >= timeoutMs)
    // {
    //     Serial.println("MAGISTRALA I2C ZAJETA - ROZPOCZYNAM RESET");
    //     lcdShowTopTextAdd("RESET MAGISTRALI I2C");

    //     i2cRecover();
    //     i2cBusySince = 0;
    // }
}


