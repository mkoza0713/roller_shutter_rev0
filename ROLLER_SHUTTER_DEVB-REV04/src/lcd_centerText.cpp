#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"

int lcd_current_y = 0;  // zapamiętuje, gdzie ma się pojawić następny wiersz

void lcdShowCenterText(String message) {
    // Czyszczenie ekranu i reset pozycji
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);

    int lineHeight = tft.fontHeight();
    int topMargin = 10; // odstęp od górnej krawędzi ekranu
    lcd_current_y = topMargin;

    // Podział tekstu na linie (obsługa \n)
    int start = 0;
    for (int i = 0; i <= message.length(); i++) {
        if (i == message.length() || message[i] == '\n') {
            String line = message.substring(start, i);

            // Centrowanie w poziomie
            int x = (SCREEN_WIDTH - tft.textWidth(line)) / 2;
            tft.drawString(line, x, lcd_current_y);

            // Przesunięcie do następnej linii
            lcd_current_y += lineHeight;
            start = i + 1;
        }
    }
}

void lcdShowTopTextAdd(String message) {
    tft.setTextColor(TFT_WHITE);
    int lineHeight = tft.fontHeight();

    // Podział tekstu na linie (obsługa \n)
    int start = 0;
    for (int i = 0; i <= message.length(); i++) {
        if (i == message.length() || message[i] == '\n') {
            String line = message.substring(start, i);

            // Centrowanie w poziomie
            int x = (SCREEN_WIDTH - tft.textWidth(line)) / 2;
            tft.drawString(line, x, lcd_current_y);

            // Następna linia niżej
            lcd_current_y += lineHeight;
            start = i + 1;
        }
    }
}
