void psetup() {
  Serial.begin(9600);
  /***********HTML**************/
  String ssid_read_1 = deviceData[0];
  String pass_read_1 = deviceData[1];
  int str_1_len = ssid_read_1.length() + 1;
  int str_2_len = pass_read_1.length() + 1;
  char ssid_eeprom_read[str_1_len];
  char pass_eeprom_read[str_2_len];
  ssid_read_1.toCharArray(ssid_eeprom_read, str_1_len);
  pass_read_1.toCharArray(pass_eeprom_read, str_2_len);

  const char* ssid_client = ssid_eeprom_read;
  const char* password_client = pass_eeprom_read;
  int connection_time = 0;
  WiFi.begin(ssid_client, password_client);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (connection_time >= 20) {
      wifiConnectionStatus = 0;
      break;
    }
    Serial.println(connection_time);
    connection_time++;
  }
  if (wifiConnectionStatus) {
    wifiConnectionStatus = 1;  //polaczono
    Serial.print("IP:");
    Serial.println(WiFi.localIP());
  }
  /***********HTML**************/

  /***********LCD+TFT**************/
  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
  touchscreen.setRotation(3);
  // Start the tft display
  tft.init();
  // Set the TFT display rotation in landscape mode
  tft.setRotation(3);
  tft.invertDisplay(true);  //odwrocenie kolorow

  // Clear the screen before writing to it
  tft.fillScreen(TFT_WHITE);
  // tft.setTextColor(TFT_WHITE, TFT_BLACK, 1);
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setFreeFont(&FreeSans9pt7b);

  int centerX = SCREEN_WIDTH / 2;
  int centerY = SCREEN_HEIGHT / 2;
  /***********LCD+TFT**************/
  /***********MPC**************/
  Wire.begin();
  // inicjalizacja mcp23008 pod katem biblioteki adafruit
  test_mpc_1 = MCP_1.begin(MCP1_ADDRESS);
  test_mpc_2 = MCP_2.begin(MCP2_ADDRESS);
  test_mpc_3 = MCP_3.begin();
  test_mpc_4 = MCP_4.begin();
  test_mpc_5 = MCP_5.begin();
  test_mpc_6 = MCP_6.begin();
  test_mpc_7 = MCP_7.begin();
  test_mpc_8 = MCP_8.begin();

  Serial.print("ekspander 1:");
  if (test_mpc_1) Serial.println("polaczono");
  else (Serial.println("nie polaczono"));
  Serial.print("ekspander 2:");
  if (test_mpc_2) Serial.println("polaczono");
  else (Serial.println("nie polaczono"));
  Serial.print("ekspander 3:");
  if (test_mpc_3) Serial.println("polaczono");
  else (Serial.println("nie polaczono"));
  Serial.print("ekspander 4:");
  if (test_mpc_4) Serial.println("polaczono");
  else (Serial.println("nie polaczono"));
  Serial.print("ekspander 5:");
  if (test_mpc_5) Serial.println("polaczono");
  else (Serial.println("nie polaczono"));
  Serial.print("ekspander 6:");
  if (test_mpc_6) Serial.println("polaczono");
  else (Serial.println("nie polaczono"));
  Serial.print("ekspander 7:");
  if (test_mpc_7) Serial.println("polaczono");
  else (Serial.println("nie polaczono"));
  Serial.print("ekspander 8:");
  if (test_mpc_8) Serial.println("polaczono");
  else (Serial.println("nie polaczono"));

  for (int pin = 4; pin <= 7; pin++) {
    if (test_mpc_1) MCP_1.pinMode(pin, INPUT);
    if (test_mpc_2) MCP_2.pinMode(pin, INPUT);
    if (test_mpc_3) MCP_3.pinMode(pin, INPUT);
    if (test_mpc_4) MCP_4.pinMode(pin, INPUT);
    if (test_mpc_5) MCP_5.pinMode(pin, INPUT);
    if (test_mpc_6) MCP_6.pinMode(pin, INPUT);
    if (test_mpc_7) MCP_7.pinMode(pin, INPUT);
    if (test_mpc_8) MCP_8.pinMode(pin, INPUT);
  }
  for (int pin = 0; pin <= 3; pin++) {
    if (test_mpc_1) MCP_1.pinMode(pin, OUTPUT);
    if (test_mpc_2) MCP_2.pinMode(pin, OUTPUT);
    if (test_mpc_3) MCP_3.pinMode(pin, OUTPUT);
    if (test_mpc_4) MCP_4.pinMode(pin, OUTPUT);
    if (test_mpc_5) MCP_5.pinMode(pin, OUTPUT);
    if (test_mpc_6) MCP_6.pinMode(pin, OUTPUT);
    if (test_mpc_7) MCP_7.pinMode(pin, OUTPUT);
    if (test_mpc_8) MCP_8.pinMode(pin, OUTPUT);
  }
  /***********MPC**************/

  /***********interrupts*****************/

  //   // Konfiguracja MCP1
  //   writeRegister(MCP1_ADDRESS, 0x00, 0xF0); // IODIR: Piny GP4-GP7 jako wejścia
  //   writeRegister(MCP1_ADDRESS, 0x06, 0xF0); // GPPU: Włącz podciąganie dla GP4-GP7
  //   writeRegister(MCP1_ADDRESS, 0x04, 0xF0); // GPINTEN: Włącz przerwania na pinach GP4-GP7
  //   writeRegister(MCP1_ADDRESS, 0x02, 0xF0); // DEFVAL: Wartość domyślna HIGH
  //   writeRegister(MCP1_ADDRESS, 0x03, 0xF0); // INTCON: Porównuj z DEFVAL
  //   writeRegister(MCP1_ADDRESS, 0x05, 0x00); // IOCON: INT jako otwarty dren, aktywny niski
  //   // Konfiguracja MCP2
  //   writeRegister(MCP2_ADDRESS, 0x00, 0xF0); // IODIR: Piny GP4-GP7 jako wejścia
  //   writeRegister(MCP2_ADDRESS, 0x06, 0xF0); // GPPU: Włącz podciąganie dla GP4-GP7
  //   writeRegister(MCP2_ADDRESS, 0x04, 0xF0); // GPINTEN: Włącz przerwania na pinach GP4-GP7
  //   writeRegister(MCP2_ADDRESS, 0x02, 0xF0); // DEFVAL: Wartość domyślna HIGH
  //   writeRegister(MCP2_ADDRESS, 0x03, 0xF0); // INTCON: Porównuj z DEFVAL
  //   writeRegister(MCP2_ADDRESS, 0x05, 0x00); // IOCON: INT jako otwarty dren, aktywny niski


  // //inicjacja pinu w esp32 do reakcji na przerwanie przychodzace z mcp23008
  // pinMode(MCP23008_INT_PIN, INPUT_PULLUP);

  // //przerwanie w ESP32. Funkcja wykonawcza interruptFunction.
  // attachInterrupt(digitalPinToInterrupt(MCP23008_INT_PIN), interruptFunction, RISING);
}