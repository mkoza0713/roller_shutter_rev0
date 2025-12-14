#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

void json_readLoop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        /*******************************************JSON_1***************************************** */
        String url = HOST_NAME + JSON_FILE_1;
        HTTPClient http_1;
        http_1.begin(url); // adres pliku JSON
        int httpResponseCode = http_1.GET();
        if (httpResponseCode > 0)
        {
            String payload = http_1.getString();                        // playload zawiera cały plik json ale jako tekst
            StaticJsonDocument<8192> doc;                               // Tworzymy dokument JSON, rozmiar dopasuj do swojego JSONa
            DeserializationError error = deserializeJson(doc, payload); // Parsowanie Stringa do JSON
            if (error)
            {
                Serial.print("Błąd parsowania JSON: ");
                Serial.println(error.c_str());
            }
            else
            {
                JsonObject root = doc.as<JsonObject>(); // JSON sparsowany, teraz możemy odczytywać dane

                // Przykład: odczytanie danych dla naszego DEVICE_ID
                // if (root.containsKey(DEVICE_ID)) // szukam po id mojego urzadzenia
                // {
                //     JsonObject deviceObj = root[DEVICE_ID]; // Odczyt tabeli rollers
                //     if (deviceObj.containsKey("rollers"))
                //     {
                //         JsonObject rollers = deviceObj["rollers"];
                //         for (JsonPair p : rollers)
                //         {
                //             String rollerID = p.key().c_str();
                //             JsonObject roller = p.value().as<JsonObject>();
                //             Serial.print("Roller ID: ");
                //             Serial.println(rollerID);
                //             Serial.print("Name: ");
                //             Serial.println(roller["name"].as<const char*>());
                //             Serial.print("Timestamp: ");
                //             Serial.println(roller["timestamp"].as<long>());
                //         }
                //     }
                // }
            }
        }
        else
        {
            Serial.println("Błąd HTTP GET: " + String(httpResponseCode));
        }

        http_1.end(); // zamyka połączenie
        /*******************************************JSON_1***************************************** */

        delay(10000); // opóźnienie między kolejnymi odczytami
    }
}