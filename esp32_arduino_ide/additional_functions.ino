void screensaver(){
  int data_from_sensor = analogRead(34);
}

void led_test() {
  pinMode(16, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(17, OUTPUT);
  delay(1000);
  digitalWrite(16, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(17, HIGH);

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
}