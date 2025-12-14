#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"

/***********WIFI**************/
#include "WiFi.h"
#include "HTTPClient.h"
#include <ArduinoJson.h>

// Funkcja tworząca JSON do wysłania na serwer
String createJSON()
{
    StaticJsonDocument<8192> doc;

    // Tworzymy obiekt główny z DEVICE_ID jako kluczem
    JsonObject root = doc.to<JsonObject>();
    JsonObject deviceObj = root.createNestedObject(DEVICE_ID);

    // Rollers
    JsonObject rollersObj = deviceObj.createNestedObject("rollers");
    for (int i = 0; i < 17; i++)
    {
        JsonObject roller = rollersObj.createNestedObject(rollers[i][0]);
        roller["timestamp"] = getCurrentTimestamp();
        roller["name"] = rollers[i][1];
        roller["area"] = rollers[i][2];
        roller["position"] = rollers[i][3].toInt();
        roller["min"] = rollers[i][4].toInt();
        roller["max"] = rollers[i][5].toInt();
        roller["status"] = rollers[i][6].toInt();
    }

    // Job table
    JsonObject matchObj = deviceObj.createNestedObject("job_todo");
    for (int i = 0; i < 17; i++)
    {
        JsonObject match = matchObj.createNestedObject(match_table[i][0]);
        match["name"] = match_table[i][1];
        match["job"] = match_table[i][2].toInt();
    }

    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

// Funkcja wysyłająca JSON na serwer
void sendData()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        String jsonData = createJSON();

        http.begin(HOST_NAME + PHP_FILE_NAME);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonData);

        if (httpResponseCode > 0)
        {
            String response = http.getString();
            // Serial.println("Response: " + response);
        }
        else
        {
            Serial.println("Error on sending POST: " + String(httpResponseCode));
        }

        http.end();
    }
    else
    {
        Serial.println("WiFi not connected");
    }
}

// Funkcja loop wysyłająca dane co określony interwał
void postRequest_loop()
{
    static unsigned long lastTime = 0;
    unsigned long currentTime = millis();
    const unsigned long interval = 10000; // co 10 sekund

    if (currentTime - lastTime >= interval)
    {
        lastTime = currentTime;
        sendData();
    }
}
