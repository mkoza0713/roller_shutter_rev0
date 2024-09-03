void ramka(int x, int y) {
  uint32_t button_insert_colour = '0x7BEF';
  tft.fillRoundRect(button_2[0], button_2[1], button_2[2], button_2[3], button_2[4], button_insert_colour);
  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
}