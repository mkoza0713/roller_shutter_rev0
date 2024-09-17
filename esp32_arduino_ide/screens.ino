void nav() {
  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_colour);
  tft.drawCentreString(button_label_1, button_1[0] + (button_1[2] / 2), button_1[1] + (button_1[3] / 2) - fontHeigh / 2, 1);

  byte x1 = 136 + (12 * screen_changer);
  tft.drawCircle(148, 15, 4, button_colour);
  tft.drawCircle(160, 15, 4, button_colour);
  tft.drawCircle(172, 15, 4, button_colour);
  tft.fillCircle(x1, 15, 4, button_colour);

  tft.fillRoundRect(button_2[0], button_2[1], button_2[2], button_2[3], button_2[4], button_colour);
  tft.drawCentreString(button_label_2, button_2[0] + (button_2[2] / 2), button_2[1] + (button_2[3] / 2) - fontHeigh / 2, 1);
}
void screen_1() {
  tft.drawCentreString("Obszary budynku:", 160, 60 - fontHeigh, 1);

  for (byte i = 0; i < sizeOfArray_object_areas; i++) {  //tu mam ile mam miec przyciskow - obszarów
    String pomocnicza1 = object_areas[i][1];
    //********************************tutaj mam rozbicie nazwy na przycisku na dwa wiersze
    String text_row_1 = "";
    String text_row_2 = "";
    if (pomocnicza1.length() >= 10) {
      for (byte j = 0; j < 11; j++) {
        text_row_1 = text_row_1 + pomocnicza1[j];  //iteracja po ciagu znaków
      }
      for (byte j = 11; j < pomocnicza1.length(); j++) {
        text_row_2 = text_row_2 + pomocnicza1[j];  //iteracja po ciagu znaków
      }
    } else {
      text_row_1 = pomocnicza1;
      text_row_2 = "";
    }
    /**********************************************/
    //********************************tutaj mam ukladanie kafelkow w petli for
    tft.fillRoundRect(buttons_positions[i][0], buttons_positions[i][1], buttons_positions[i][2], buttons_positions[i][3], buttons_positions[i][4], button_colour);  //0
    tft.drawCentreString(text_row_1, buttons_positions[i][0] + (buttons_positions[i][2] / 2), buttons_positions[i][1] + (buttons_positions[i][3] / 2) - (fontHeigh + fontHeigh / 2), 1);
    tft.drawCentreString(text_row_2, buttons_positions[i][0] + (buttons_positions[i][2] / 2), buttons_positions[i][1] + (buttons_positions[i][3] / 2), 1);
  }

}
void screen_2() {
  tft.drawCentreString("Dane z serwera:", 160, 60 - fontHeigh, 1);
}
void screen_3() {
  tft.drawCentreString("Ustawienia:", 160, 60 - fontHeigh, 1);
}
void standard_back_button() {
  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_colour);
  tft.drawCentreString(button_label_1, button_1[0] + (button_1[2] / 2), button_1[1] + (button_1[3] / 2) - fontHeigh / 2, 1);
}

//ekranay do przerobki
void screen_31() {
  standard_back_button();
  tft.drawCentreString(object_areas[0][1], 160, 60 - fontHeigh, 1);

  cb_y1 = 70;  //zeruje zmienna
  //Serial.println(sizeOfArray_rollers);
  for (int i = 0; i < sizeOfArray_rollers; i++) {
    if (rollers[i][2] == "AREA_1") {
      tft.drawRect(10, cb_y1, frame1, frame1, button_colour);
      tft.drawString(rollers[i][1], 35, cb_y1 + 2);
      cb_y1 = cb_y1 + cb_row_space;
    }
  }
}
void screen_41() {
  standard_back_button();
  tft.drawCentreString(object_areas[1][1], 160, 60 - fontHeigh, 1);

  cb_y1 = 70;  //zeruje zmienna
  //Serial.println(sizeOfArray_rollers);
  for (int i = 0; i < sizeOfArray_rollers; i++) {
    if (rollers[i][2] == "AREA_2") {
      tft.drawRect(10, cb_y1, frame1, frame1, button_colour);
      tft.drawString(rollers[i][1], 35, cb_y1 + 2);
      cb_y1 = cb_y1 + cb_row_space;
    }
  }
}
void screen_51() {
  standard_back_button();
  tft.drawCentreString(object_areas[2][1], 160, 60 - fontHeigh, 1);
}
void screen_61() {
  standard_back_button();
  tft.drawCentreString(object_areas[3][1], 160, 60 - fontHeigh, 1);
}
void screen_71(){
  standard_back_button();
  tft.drawCentreString(object_areas[4][1], 160, 60 - fontHeigh, 1);
}
void screen_81(){
  standard_back_button();
  tft.drawCentreString(object_areas[5][1], 160, 60 - fontHeigh, 1);
}

//fonts
// tft.setFreeFont(&FreeMono9pt7b);
// tft.setCursor(1, 60, 1);
// tft.println("Wybierz obszar budynku: test tekstu");
// tft.setFreeFont(&FreeMonoOblique9pt7b);
// tft.println("Wybierz obszar\n budynku:");
// tft.setFreeFont(&FreeSans9pt7b);
// tft.println("Wybierz obszar\n budynku:");
// tft.setFreeFont(&FreeSerif9pt7b);
// tft.println("Wybierz obszar\n budynku:");
// tft.setFreeFont(&TomThumb);
// tft.println("Wybierz obszar\n budynku:");
