void screensaver() {
  //wygaszanie ekranu po okrelonym czasie
  //czas okereslony w screensaver_time
  //po wykryciu ekran ustawia sie w kolor czarny
  //po wykryciu ruchu ekran ustawia sie na wartosciach startowych
  int data_from_sensor = analogRead(34);
  int roznica = 10;
  if (data_from_sensor > roznica) {
    if (screeensaver_lock == 0) {
      tft.fillScreen(TFT_WHITE);
      nav();
      screen_1();
      screeensaver_lock = 1;
    }
    time_to_screen_black = millis();
  }
  if (millis() - time_to_screen_black >= screensaver_time && screeensaver_lock) {
    screeensaver_lock = 0;
    tft.fillScreen(TFT_BLACK);
  }
}
void relay_test() {
  Serial.println("Test przekaznikow:");
  // for (byte i = 0; i <= 7; i++) {
  //   if (i <= 3) {
  //     String stringToWrite = "Ekspander 1:" + String(i2cDevices[0], HEX);
  //     Serial.println(stringToWrite);
  //     MCP_1.write1(i, 1);
  //     delay(1000);
  //     MCP_1.write1(i, 0);
  //     delay(1000);

  //   } else if (i >= 4 && i <= 7) {
  //     String stringToWrite = "Ekspander 2:" + String(i2cDevices[1], HEX);
  //     Serial.println(stringToWrite);
  //     MCP_2.write1(i - 4, 1);
  //     delay(1000);
  //     MCP_2.write1(i - 4, 0);
  //     delay(1000);
  //   }
  // }
}
void led_test() {
  pinMode(16, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(17, OUTPUT);
  delay(1000);
  digitalWrite(16, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(17, HIGH);
  /*
  delay(100);
  digitalWrite(16, LOW);
  delay(100);
  digitalWrite(16, HIGH);
  delay(100);
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(17, LOW);
  delay(100);
  digitalWrite(17, HIGH);

  Serial.print("czujnik");
  Serial.println(analogRead(34));

  tft.fillRect(150, 150, 100, 100, 0x0000);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x000F);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x03E0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x03EF);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x7800);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x780F);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x7BE0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xD69A);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x7BEF);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x001F);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x07E0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x07FF);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xF800);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xF81F);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFFE0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFFFF);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFDA0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xB7E0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFE19);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x9A60);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFEA0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFE19);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x9A60);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFEA0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xC618);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x867D);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x915C);
  delay(500);
  */
}
void (*resetFunc)(void) = 0;