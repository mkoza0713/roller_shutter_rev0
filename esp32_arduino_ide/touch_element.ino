String touch_function() {
  // // Get Touchscreen points

  TS_Point p = touchscreen.getPoint();
  x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
  y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
  z = p.z;


  uint32_t button_insert_colour;
  button_insert_colour = '0x867D';
  if (x >= button_1[0] && x <= button_1[2] + button_1[0] && y >= button_1[1] && y <= button_1[3] + button_1[1]) {
    // Serial.println("button 1");
    tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
    return "button_1";  //id przycisku to moglo by wracac z f()
  } else if (x >= button_2[0] && x <= button_2[2] + button_2[0] && y >= button_2[1] && y <= button_2[3] + button_2[1]) {
    // Serial.println("button 2");
    tft.fillRoundRect(button_2[0], button_2[1], button_2[2], button_2[3], button_2[4], button_insert_colour);
    return "button_2";  //id przycisku to moglo by wracac z f()
  }

  else if (screen_changer == 1) {  //kafelki
    if (x >= button_3[0] && x <= button_3[2] + button_3[0] && y >= button_3[1] && y <= button_3[3] + button_3[1]) {
      //Serial.println("button 3");
      tft.fillRoundRect(button_3[0], button_3[1], button_3[2], button_3[3], button_3[4], button_insert_colour);
      return "button_3";
    } else if (x >= button_4[0] && x <= button_4[2] + button_4[0] && y >= button_4[1] && y <= button_4[3] + button_4[1]) {
      //Serial.println("button 4");
      tft.fillRoundRect(button_4[0], button_4[1], button_4[2], button_4[3], button_4[4], button_insert_colour);
      return "button_4";
    } else if (x >= button_5[0] && x <= button_5[2] + button_5[0] && y >= button_5[1] && y <= button_5[3] + button_5[1]) {
      //Serial.println("button 5");
      tft.fillRoundRect(button_5[0], button_5[1], button_5[2], button_5[3], button_5[4], button_insert_colour);
      return "button_5";
    } else if (x >= button_6[0] && x <= button_6[2] + button_6[0] && y >= button_6[1] && y <= button_6[3] + button_6[1]) {
      //Serial.println("button 6");
      tft.fillRoundRect(button_6[0], button_6[1], button_6[2], button_6[3], button_6[4], button_insert_colour);
      return "button_6";
    }else{
      return "";
    }
  } else if (screen_changer == 2) {
    // Serial.println("TEST POINT FOR screen_ch value 2");
    return "";
  } else if (screen_changer > 10) {
    // Serial.println("TEST POINT FOR screen_ch value >10");
    return "";
  } else return "";
}