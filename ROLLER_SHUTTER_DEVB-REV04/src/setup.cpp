#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"
#include "time.h" //do pobrania timestampa z serwera NTP

/*TFT_eSPI file to change drom folder*/
#define XPT2046_IRQ 36  // T_IRQ
#define XPT2046_MOSI 32 // T_DIN
#define XPT2046_MISO 39 // T_OUT
#define XPT2046_CLK 25  // T_CLK
#define XPT2046_CS 33   // T_CS

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include <XPT2046_Touchscreen.h>
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

/***********WIFI**************/
#include "WiFi.h"
#include "HTTPClient.h"
const char *ntpServer = "pool.ntp.org"; // serwer NTP
const long gmtOffset_sec = 3600;        // Polska = +1h
const int daylightOffset_sec = 0;       // zmiana czasu letniego

// funkcja do pobierania aktualnego czasu z serwera NTP
time_t getCurrentTimestamp()
{
    time_t now  =time(nullptr);// zwraca epoch (sekundy od 1970)
    if(now < 1000000000){
        return 0; // błąd pobierania czasu
    }else{
        return now;
    }
}


void psetup()
{
    Serial.begin(115200);
    delay(5000);
    Serial.println("Start programu");

    /***********LCD+TFT**************/

    // Start the SPI for the touchscreen and init the touchscreen
    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);
    // Set the Touchscreen rotation in landscape mode
    // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
    touchscreen.setRotation(3);
    // Start the tft display
    tft.init();
    // Set the TFT display rotation in landscape mode
    tft.setRotation(3);
    tft.invertDisplay(true); // odwrocenie kolorow

    // Clear the screen before writing to it
    tft.fillScreen(TFT_WHITE);
    // tft.setTextColor(TFT_WHITE, TFT_BLACK, 1);
    tft.setTextColor(TFT_BLACK, TFT_BLACK);
    tft.setFreeFont(&FreeSans9pt7b);

    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;

    /***********LCD+TFT**************/

    /***********WIFI**************/
    byte timeout = 0;
    WiFi.begin(ssid, password);
    lcdShowCenterText("WIFI connecting");
    Serial.println("WIFI connecting");
    while (WiFi.status() != WL_CONNECTED && timeout < 10)
    {
        delay(500);
        lcdShowTopTextAdd(".");
        Serial.print(".");
        timeout++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        String messageToLcd = "\nConnected, IP:" + WiFi.localIP().toString() + "\n SSID:" + ssid;
        lcdShowTopTextAdd(messageToLcd);
        Serial.print("Polaczono! IP:");
        Serial.println(WiFi.localIP());
        delay(5000);

        /***********NTP**************/
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

        // Czekamy na synchronizację NTP
        time_t nowTime = 0;
        int attempts = 0;
        Serial.println("NTP connecting");
        while ((nowTime = time(nullptr)) < 1000000000 && attempts < 20)
        { // max 10 sekund
            delay(500);
            Serial.print(".");
            attempts++;
        }
        Serial.println();
        if (nowTime < 1000000000)
        {
            Serial.println("Nie udało się zsynchronizować NTP");
        }
        else
        {
            Serial.print("NTP Polaczono! epoch:");
            Serial.println(nowTime);
        }

        /***********NTP**************/
    }
    else
    {
        String messageToLcd = "\nBrak polaczenia z siecia WIFI";
        lcdShowCenterText(messageToLcd);
        Serial.println("Nie polaczono z WIFI");
        delay(5000);
    }
    /***********WIFI**************/
}