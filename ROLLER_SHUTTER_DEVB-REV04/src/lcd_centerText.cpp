#include "Arduino.h"
#include "functions.h"
#include "global_variables.h"

void lcdShowCenterText(String message){
    // Policz liczbę linii
    int lineCount = 1;
    for (int i = 0; i < message.length(); i++) {
        if (message[i] == '\n') lineCount++;
    }

    // Tablica do przechowania linii
    String lines[lineCount];

    // Podział tekstu na linie
    int currentLine = 0;
    int start = 0;
    for (int i = 0; i <= message.length(); i++) {
        if (i == message.length() || message[i] == '\n') {
            lines[currentLine] = message.substring(start, i);
            start = i + 1;
            currentLine++;
        }
    }

    // Obliczenie całkowitej wysokości bloku tekstu
    int lineHeight = tft.fontHeight();
    int totalHeight = lineHeight * lineCount;

    // Startowa pozycja Y dla centrowania pionowego
    int y = (SCREEN_HEIGHT - totalHeight) / 2;

    // Wyczyść ekran i ustaw kolor tekstu
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK);

    // Rysowanie każdej linii
    for (int i = 0; i < lineCount; i++) {
        int x = (SCREEN_WIDTH - tft.textWidth(lines[i])) / 2; // centrowanie poziome
        tft.drawString(lines[i], x, y, 1); // 1 = font numer 1 lub ustawiony FreeFont
        y += lineHeight;
    }
}