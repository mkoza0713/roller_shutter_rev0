uint32_t touch_function() {
  // // Get Touchscreen points

  TS_Point p = touchscreen.getPoint();
  x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
  y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
  z = p.z;


  uint32_t button_insert_colour;
  button_insert_colour = '0x867D';

  if (x >= button_1[0] && x <= button_1[2] + button_1[0] && y >= button_1[1] && y <= button_1[3] + button_1[1]) {
    Serial.println("button 1");
    tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
    return 'button_1';  //id przycisku to moglo by wracac z f()
  } else if (x >= button_2[0] && x <= button_2[2] + button_2[0] && y >= button_2[1] && y <= button_2[3] + button_2[1]) {
    Serial.println("button 2");
    tft.fillRoundRect(button_2[0], button_2[1], button_2[2], button_2[3], button_2[4], button_insert_colour);
    return 'button_2';  //id przycisku to moglo by wracac z f()
  } else {
    return 0;
  }
}