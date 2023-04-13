int checkReception_easy(){
  while(!Serial1.available()){
    Serial.print(".");
    delay(1000);
  }
  String message = Serial1.readString();
  Serial.println("Voici ce que j'ai recu = "+message);
  
  return 0;
}

int checkReception_ESP32() {
  unsigned long timeInit = millis()*0.001;
  char message[150];
  int count = 0;
  
  while(true) {
    // If maximum time (20s) to wait for message reception exceeded
    if(millis()*0.001 - timeInit > 5.0) { 
      Serial.println("To Long Time");
      return 0;
     }
    if (Serial1.available()){
        char st = Serial1.read();
        message[count] = st;  
        message[count+1] = '\0';  
        count += 1;
        
        if(message[count-1] == '\n'){
          Serial.print("Le message recu : ");          
          Serial.println(String(message));  //Affiche le message recu
          if (analyse_ESP32(message) ==  1) {
            return 1;
          } else {
            return 0;
          }
        }
     }
  }
}

int analyse_ESP32(String st) {
  // Arret de la publication si le mot STOP est reçu par le Click

  //Serial.println("Analyse has been called");
  int res = 1;  
  if(st.indexOf("TIME") > 0 || st.indexOf("SUCCESS") > 0) {
    Serial.println("Yes il y a TIME dans le message!");
    res = 1;
  } else {
    res = 0;
  }
  return res;
}