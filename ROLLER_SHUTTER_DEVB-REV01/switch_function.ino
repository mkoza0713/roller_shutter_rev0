void input_switch() {
  /*
    Zalozenia:
      1.Nie mogę blokowac mozliwosci wciskania kilku rolet na raz
      2.Muszę zablokować możliwość wciśniecia dwóch przyciskó na raz: gora i dol
      3. Pętla nie może stanąć na czas działania rolety
        3.1 Dla dzialania automatu z czasem. Uruchamiam funkcje i w millis odczytuje ciagle czy zadany czas uplynał. Taka sama historia jak dla lcd
        3.2 Dla dzialania gdzie trzymam przycisk i roleta jedzie, muszę uwzględnić przypadek, że jedzie kilka rolet na raz...
          Dla tego przypadku nie powinienem zerowac tablicy za kazdym obiegiem petli.

  */
  /*****************odczyt stanow z wejsc programowalnych****************/
  //tworze tablice i wypalniam ja wartosciami domyslnymi, czyli 1. Wartosc 1 to odczytany pullup, 0 to odczytany przycisk
  //tablica w petli jest cały czas zerowana.
  int value_of_input[9][4];
  //zerowanie tablicy tylko raz przy uruchomieniu programu.
  if (value_of_input_lock) {
    for (byte i = 0; i < 9; i++) {
      value_of_input[i][0] = 1;
      value_of_input[i][1] = 1;
      value_of_input[i][2] = 1;
      value_of_input[i][3] = 1;
    }
    value_of_input_lock = false;  //blokuje ponowne zerowanie
  }


  bool is_get_input = false;
  // //odczytuje gdzie wystapil stan 1 dla wszystkich wejsc
  // for (byte i = 4; i < 8; i++) {
  //   if (test_mpc_1) {
  //     bool input_state = MCP_1.digitalRead(i);
  //     value_of_input[1][i - 4] = input_state;
  //     if (!input_state) is_get_input = true;
  //   }
  //   if (test_mpc_2) {
  //     bool input_state = MCP_2.digitalRead(i);
  //     value_of_input[2][i - 4] = input_state;
  //     if (!input_state) is_get_input = true;
  //   }
  //   if (test_mpc_3) {
  //     bool input_state = MCP_3.digitalRead(i);
  //     value_of_input[3][i - 4] = input_state;
  //     if (!input_state) is_get_input = true;
  //   }
  //   if (test_mpc_4) {
  //     bool input_state = MCP_4.digitalRead(i);
  //     value_of_input[4][i - 4] = input_state;
  //     if (!input_state) is_get_input = true;
  //   }
  //   if (test_mpc_5) {
  //     bool input_state = MCP_5.digitalRead(i);
  //     value_of_input[5][i - 4] = input_state;
  //     if (!input_state) is_get_input = true;
  //   }
  //   if (test_mpc_6) {
  //     bool input_state = MCP_6.digitalRead(i);
  //     value_of_input[6][i - 4] = input_state;
  //     if (!input_state) is_get_input = true;
  //   }
  //   if (test_mpc_7) {
  //     bool input_state = MCP_7.digitalRead(i);
  //     value_of_input[7][i - 4] = input_state;
  //     if (!input_state) is_get_input = true;
  //   }
  //   if (test_mpc_8) {
  //     bool input_state = MCP_8.digitalRead(i);
  //     value_of_input[8][i - 4] = input_state;
  //     if (!input_state) is_get_input = true;
  //   }
  // }

  if (is_get_input) {
    for (byte i = 1; i <= 8; i++) {
      //wyswietlam tablice
      for (byte j = 0; j <= 3; j++) {
        // Serial.print(value_of_input[i][j]);
        // Serial.print(value_of_input[i][j]);
        // Serial.print(value_of_input[i][j]);
        // Serial.println(value_of_input[i][j]);
        //zalaczam przekazniki
        if (value_of_input[i][j] == 0) {
          String stringToWrite = "Wyjscie:" + String(i) + "." + String(j + 1) + " rozpoczyna prace";
          Serial.println(stringToWrite);
        }
      }
    }
    Serial.println("----------------");
  }
}
