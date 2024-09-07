void nav() {
  uint32_t button_insert_colour = '0x7BEF';
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setFreeFont(&FreeSans9pt7b);
  byte fontHeigh = 10;  //dodałem wiecej aby zrobic padding pom tekstem

  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
  tft.drawCentreString(button_label_1, button_1[0] + (button_1[2] / 2), button_1[1] + (button_1[3] / 2) - fontHeigh / 2, 1);

  tft.fillRoundRect(button_2[0], button_2[1], button_2[2], button_2[3], button_2[4], button_insert_colour);
  tft.drawCentreString(button_label_2, button_2[0] + (button_2[2] / 2), button_2[1] + (button_2[3] / 2) - fontHeigh / 2, 1);
}

void screen_1() {
  uint32_t button_insert_colour = '0x7BEF';
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setFreeFont(&FreeSans9pt7b);
  byte fontHeigh = 10;  //dodałem wiecej aby zrobic padding pom tekstem

  /*********************************/
  tft.drawCentreString("Obszary budynku:", 160, 60 - fontHeigh, 1);

  tft.fillRoundRect(button_3[0], button_3[1], button_3[2], button_3[3], button_3[4], button_insert_colour);
  tft.drawCentreString(button_label_3_1, button_3[0] + (button_3[2] / 2), button_3[1] + (button_3[3] / 2) - (fontHeigh + fontHeigh / 2), 1);
  tft.drawCentreString(button_label_3_2, button_3[0] + (button_3[2] / 2), button_3[1] + (button_3[3] / 2), 1);

  tft.fillRoundRect(button_4[0], button_4[1], button_4[2], button_4[3], button_4[4], button_insert_colour);
  tft.drawCentreString(button_label_4_1, button_4[0] + (button_4[2] / 2), button_4[1] + (button_4[3] / 2) - (fontHeigh + fontHeigh / 2), 1);
  tft.drawCentreString(button_label_4_2, button_4[0] + (button_4[2] / 2), button_4[1] + (button_4[3] / 2), 1);

  tft.fillRoundRect(button_5[0], button_5[1], button_5[2], button_5[3], button_5[4], button_insert_colour);
  tft.drawCentreString(button_label_5_1, button_5[0] + (button_5[2] / 2), button_5[1] + (button_5[3] / 2) - (fontHeigh + fontHeigh / 2), 1);
  tft.drawCentreString(button_label_5_2, button_5[0] + (button_5[2] / 2), button_5[1] + (button_5[3] / 2), 1);

  tft.fillRoundRect(button_6[0], button_6[1], button_6[2], button_6[3], button_6[4], button_insert_colour);
  tft.drawCentreString(button_label_6_1, button_6[0] + (button_6[2] / 2), button_6[1] + (button_6[3] / 2) - (fontHeigh + fontHeigh / 2), 1);
  tft.drawCentreString(button_label_6_2, button_6[0] + (button_6[2] / 2), button_6[1] + (button_6[3] / 2), 1);
}
void screen_2() {
  tft.drawCentreString("Tu będą dane z serwera nt pogody", 160, 120, 1);
}
void screen_31() {
  uint32_t button_insert_colour = '0x7BEF';
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setFreeFont(&FreeSans9pt7b);
  byte fontHeigh = 10;  //dodałem wiecej aby zrobic padding pom tekstem
  //back
  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
  tft.drawCentreString(button_label_1, button_1[0] + (button_1[2] / 2), button_1[1] + (button_1[3] / 2) - fontHeigh / 2, 1);

  /*********************************/
  tft.drawCentreString(button_label_3_1 + button_label_3_2, 160, 60 - fontHeigh, 1);
  //tu ma byc lista rolet. Check-box i dwa przyciski do otwierania i zamykania
}
void screen_41() {
  uint32_t button_insert_colour = '0x7BEF';
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setFreeFont(&FreeSans9pt7b);
  byte fontHeigh = 10;  //dodałem wiecej aby zrobic padding pom tekstem
  //back
  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
  tft.drawCentreString(button_label_1, button_1[0] + (button_1[2] / 2), button_1[1] + (button_1[3] / 2) - fontHeigh / 2, 1);

  /*********************************/
  tft.drawCentreString(button_label_4_1 + button_label_4_2, 160, 60 - fontHeigh, 1);
}
void screen_51() {
  uint32_t button_insert_colour = '0x7BEF';
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setFreeFont(&FreeSans9pt7b);
  byte fontHeigh = 10;  //dodałem wiecej aby zrobic padding pom tekstem
  //back
  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
  tft.drawCentreString(button_label_1, button_1[0] + (button_1[2] / 2), button_1[1] + (button_1[3] / 2) - fontHeigh / 2, 1);

  /*********************************/
  tft.drawCentreString(button_label_5_1 + button_label_5_2, 160, 60 - fontHeigh, 1);
}
void screen_61() {
  uint32_t button_insert_colour = '0x7BEF';
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setFreeFont(&FreeSans9pt7b);
  byte fontHeigh = 10;  //dodałem wiecej aby zrobic padding pom tekstem
  //back
  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
  tft.drawCentreString(button_label_1, button_1[0] + (button_1[2] / 2), button_1[1] + (button_1[3] / 2) - fontHeigh / 2, 1);

  /*********************************/
  tft.drawCentreString(button_label_6_1 + button_label_6_2, 160, 60 - fontHeigh, 1);
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
