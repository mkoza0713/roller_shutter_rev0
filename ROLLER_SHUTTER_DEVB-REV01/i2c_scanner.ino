void i2c_scanner() {
  Wire.begin();
  byte error, address;
  int nDevices;

  //Serial.println("Scanning i2c devices...");
  Serial.println("Magistrala I2C:");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C znalezione pod adresem: 0x");
      if (address < 16)Serial.print("0");
      Serial.println(address, HEX);
      i2cDevices[nDevices]=address;  //tablica ze znalezionymi adresami

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("koniec\n");
  countOfI2cDevices = nDevices;

}