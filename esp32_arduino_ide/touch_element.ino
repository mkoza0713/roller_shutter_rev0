String touch_function() {
  // // Get Touchscreen points

  TS_Point p = touchscreen.getPoint();
  x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
  y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
  z = p.z;

  if (x >= button_1[0] && x <= button_1[2] + button_1[0] && y >= button_1[1] && y <= button_1[3] + button_1[1]) {
    // Serial.println("button 1");
    tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
    return "button_1";
  } else if (x >= button_2[0] && x <= button_2[2] + button_2[0] && y >= button_2[1] && y <= button_2[3] + button_2[1]) {
    // Serial.println("button 2");
    tft.fillRoundRect(button_2[0], button_2[1], button_2[2], button_2[3], button_2[4], button_insert_colour);
    return "button_2";
  }


  else if (screen_changer == 1) {  //kafelki
    String output_variable="";
    for (byte i = 0; i < sizeOfArray_object_areas; i++) {
      if (x >= buttons_positions[i][0] && x <= buttons_positions[i][2] + buttons_positions[i][0] && y >= buttons_positions[i][1] && y <= buttons_positions[i][3] + buttons_positions[i][1]) {
        tft.fillRoundRect(buttons_positions[i][0], buttons_positions[i][1], buttons_positions[i][2], buttons_positions[i][3], buttons_positions[i][4], button_insert_colour);
        output_variable=buttons_names[i];
      }
    }
    if(output_variable!="")return output_variable;
    else return "";

  } else if (screen_changer == 2) {
    // Serial.println("TEST POINT FOR screen_ch value 2");
    return "";
  } else if (screen_changer == 31) {
    //for screens generated
  } else if (screen_changer > 10) {
    // Serial.println("TEST POINT FOR screen_ch value >10");
    return "";
  } else return "";
}