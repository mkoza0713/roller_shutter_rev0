void psetup() {
  Serial.begin(115200);
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

}