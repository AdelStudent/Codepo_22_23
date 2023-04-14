/*
Pour la personne qui va lire ce code:
  Le rôle de ces fonctions est de communiquer avec l'Arduino en interprétant le texte reçu ainsi que de lui répondre s'il le faut
  C'est donc ici que l'Arduino demande l'heure qu'il est tout comme c'est ici que l'ESP32 demande à l'Arduino les Data qu'il doit afficher
  sur le site.
*/

//____________________________USEFULL FUNCTIONS_______________________//
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
void analyse_query(String msg){
  //Lis les querys et partage les datas correspondants
  
  Serial.println("Le message recu : "+msg);
  if (msg=="getIP"){
    Serial.print("local ip: ");
    Serial.println(WiFi.localIP());
  }
  else if (msg=="getDate" ||msg=="getTime" ){
    Serial.println("il est : "+get_time());
  }
  else{
    Serial.println("Query pas reconnue, voici les options:");
    Serial.println("  -getIP");
    Serial.println("  -getDate or getTime");

  }
}

//____________________________TEST FUNCTIONS__________________________//
int checkReception_PC() {
  unsigned long timeInit = millis()*0.001;
  char message[150];
  int count = 0;
  
  while(true) {
    // If maximum time (20s) to wait for message reception exceeded
    if(millis()*0.001 - timeInit > 5.0) { 
      //Serial.print(".");
      return 0;
    }
    while (Serial.available()>0){
      String my_msg = Serial.readStringUntil('\n');
      analyse_query(my_msg);
    }
  }
}
int checkReception_easy(){
  //Read the whole received message and put it in a String
  while(!Serial1.available()){
    Serial.print(".");
    delay(1000);
  }
  String message = Serial1.readString();
  Serial.println("Voici ce que j'ai recu = "+message);
  
  return 0;
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
