void input_switch() {
  byte mnoznik = 1;  //do lokalizowania ekspandera
  for (int i = 4; i <= 7; i++) {
    int val1 = MCP_1.read1(i);
    int val2 = MCP_2.read1(i);
    if(!val1 || !val2){
      if(!val1){
        mnoznik=1;
        MCP_1.write1(i-4, 1);
      }
      else if(!val2){
        mnoznik=2;
        MCP_2.write1(i-4, 1);
      }

      String stringToWrite = "Ekspander: "+String(mnoznik)+", input:"+String(i);
      Serial.println(stringToWrite);


    }
    else{
        MCP_1.write1(i-4, 0);
        MCP_2.write1(i-4, 0);
    }
  }
}