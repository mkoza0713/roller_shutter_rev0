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
    if(connection_time>=20){
      wifiConnectionStatus=0;
      break;
    }
    Serial.println(connection_time);
    connection_time++;
  }
  if(wifiConnectionStatus){
    wifiConnectionStatus=1;  //polaczono
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
  bool test_mpc_1 = MCP_1.begin();
  bool test_mpc_2 = MCP_2.begin();

  Serial.print("ekspander 1:");if(test_mpc_1)Serial.println("polaczono");else(Serial.println("nie polaczono"));
  Serial.print("ekspander 2:");if(test_mpc_2)Serial.println("polaczono");else(Serial.println("nie polaczono"));

  for (int pin = 4; pin <= 7; pin++)
  {
    MCP_1.pinMode1(pin, INPUT);
    MCP_2.pinMode1(pin, INPUT);
  }
  for (int pin = 0; pin <= 3; pin++)
  {
    MCP_1.pinMode1(pin, OUTPUT);
    MCP_2.pinMode1(pin, OUTPUT);
  }
  /***********MPC**************/

  
}