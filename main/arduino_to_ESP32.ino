//Le module ESP32 utilise les pin Rx2/Tx2 pour communquer (par extension =>Serial2)

void send_hello(){
    Serial2.println("AT+SEND=hello\r"); //envoie hello au module thingstream
}
void receive(){
  if (Serial2.available()) {
      //String data = Serial2.readStringUntil('\r');
      String data = Serial2.readString();
      Serial.println(data);
  }
}

void parse_query(String query){
  //compare the query to PV current/ PV voltage/ PV power/current used/current generated/SOC/SOH
  if (query=="PV current"){
    //read data from SD card and send it in a loop
    readData("PvCurrent.txt");
  }
  if(query=="PV voltage"){
    //read data from SD card and send it in a loop
  }
  if (query=="PV power"){
    //read data from SD card and send it in a loop
  }
  if (query=="current used"){
    //read data from SD card and send it in a loop
  }
  if (query=="current generated"){
    //read data from SD card and send it in a loop
  }
  if(query=="SOC"){
    //read data from SD card and send it in a loop
  }
  if(query=="SOH"){
    //read data from SD card and send it in a loop
  }
  Serial.println("parse_query called");
}
