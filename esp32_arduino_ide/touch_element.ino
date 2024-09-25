String touch_function() {
  // // Get Touchscreen points
  TS_Point p = touchscreen.getPoint();
  x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
  y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
  z = p.z;

  /***********************************************************/
  int screen_changer_position;
  if (screen_changer >= 10 && screen_changer <= 15) {  //zmienna okreslajaca polozenie w struktorze menu. screen_changer_position = Area
    screen_changer_position = screen_changer - 10;
    //zabezpieczenie;
    if (screen_changer_position < 0) screen_changer_position = 0;
    else if (screen_changer_position > 5) screen_changer_position = 5;
  }
  /***********************************************************/

  if (x >= button_1[0] && x <= button_1[2] + button_1[0] && y >= button_1[1] && y <= button_1[3] + button_1[1]) {
    tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_insert_colour);
    for (byte i = 0; i < sizeOfArray_rollers; i++) rollers[i][5] = "0";  //tutaj trzeba wyzerowac dane w tablicy zaznaczoncyh checkboxow
    return "button_1";
  } else if (x >= button_2[0] && x <= button_2[2] + button_2[0] && y >= button_2[1] && y <= button_2[3] + button_2[1]) {
    tft.fillRoundRect(button_2[0], button_2[1], button_2[2], button_2[3], button_2[4], button_insert_colour);
    return "button_2";
  }


  else if (screen_changer == 1) {  //nasłuchuję na kafelkach
    String output_variable = "";
    for (byte i = 0; i < sizeOfArray_object_areas; i++) {
      if (x >= buttons_positions[i][0] && x <= buttons_positions[i][2] + buttons_positions[i][0] && y >= buttons_positions[i][1] && y <= buttons_positions[i][3] + buttons_positions[i][1]) {
        tft.fillRoundRect(buttons_positions[i][0], buttons_positions[i][1], buttons_positions[i][2], buttons_positions[i][3], buttons_positions[i][4], button_insert_colour);
        output_variable = buttons_names[i];
      }
    }
    if (output_variable != "") return output_variable;
    else return "";

  } else if (screen_changer >= 10 && screen_changer <= 15) {
    //check boxy
    cb_y1 = 70;  //zeruje zmienna
    //trzeba ograniczyc sizeofarray_roller
    for (byte i = 0; i < sizeOfArray_rollers; i++) {
      if (rollers[i][2] == object_areas[screen_changer_position][0]) {
        if (x >= 10 && x <= 100 && y > cb_y1 && y <= cb_y1 + frame1) {
          if (rollers[i][5] == "checked") rollers[i][5] = "0";
          else rollers[i][5] = "checked";
        }
        cb_y1 = cb_y1 + cb_row_space;  //tutaj przesuwam sie o jedne wiersz nizej
      }
    }

    //przyciski gora/dol
    if (x >= button_up[0] && x <= button_up[0] + button_up[2] && y >= button_up[1] && y <= button_up[1] + button_up[3]) {
      tft.fillRoundRect(button_up[0], button_up[1], button_up[2], button_up[3], button_up[4], button_insert_colour);
      //teraz tak. Musze wiedziec ktore checkboxy mam zaznaczone i czekam az sie wszystkie pootwieraja
      Serial.println("Przycisk UP");
      // object_areas[screen_changer_position][0];  //obszar jaki obecenie mamy na ekranie
      //int lower_work_time = 500;  ////////////////////////UWAGA UWAGA - zmienić albo zabezpieczyc!
      int higher_work_time = 0;
      for (byte i = 0; i < sizeOfArray_rollers; i++) {
        if (rollers[i][5] == "checked") {  //stad mam zaznaczone rolety do pracy
          //tutaj dam digitalWrite(przekaznik, HIGH);
          //szukam najwiekszego czasu dzialania
          if (rollers[i][4].toInt() > higher_work_time) higher_work_time = rollers[i][4].toInt();
        }
      }
      Serial.print("Najwiekszy czas działania to: ");
      Serial.println(higher_work_time);

      start_millis_time = millis();
      while (millis() <= start_millis_time + higher_work_time) {  //petla bedzie dzialala zgodnie z najdluzszym czasem dzialnia zaznacoznej rolety
        //tutaj przechodze po wszystkich roletach, czy czas juz został przekroczony
        for (byte i = 0; i < sizeOfArray_rollers; i++) {
          if (rollers[i][5] == "checked") {  //stad mam zaznaczone rolety do pracy
            if(millis() >= start_millis_time+rollers[i][4].toInt()){
              //tutaj dam digitalWrite(przekaznik, LOw)
              Serial.print("Przekaznik od rolety: ");
              Serial.print(rollers[i][1]);
              Serial.println(" zakonczyl prace.");
            }
          }
        }

      }
    }

















    if (x >= button_down[0] && x <= button_down[0] + button_down[2] && y >= button_down[1] && y <= button_down[1] + button_down[3]) {
      tft.fillRoundRect(button_down[0], button_down[1], button_down[2], button_down[3], button_down[4], button_insert_colour);
      Serial.println("Przycisk DOWN");
    }


    return "";
  } else return "";
}