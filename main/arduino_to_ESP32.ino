/*
Pour la personne qui va lire ce code:
    -Tout échange de données avec l'ESP32 se font ici. C'est une communcation UART utilisant Serial2 (Rx2/Tx2) pour envoyer/recevoir la data
    -Pour éviter quelques problèmes d'interprétation des données, nous videons le Serial2 à chaque fois qu'on l'on envoit une requête à ESP32
      Cela permet d'être beaucoup sûr que ce qui est recu soit bel et bien une réponde à notre requête.
    ATTENTION: La carte SD a un comportement étrange pour les noms. Elle n'accepte pas plus de 7 caractères pour un nom de fichier
      et étrangement, elle n'accepte plus une arborescence de dossier/fichier. Dès lors, une pseudo-arborescence a été crée dans le nom
      même des fichier:
      Les 3 premiers caractères expriment le système dont on s'intéresse.
        -Battery : bat
        -Panneau photovoltaique : ppv
        -Reseau : res
        -Charges : chr

      La valeur suivante permet de savoir quelle mesures nous intéresse:
        -courant : 0
        -tension  : 1
        -puissance : 2
        -temperature : 4
        -SOC : 3
        -SOH : 5

      La valeur suivante permet de savoir si la mesure est entrante/sortante/aucune:
        -aucune : 0
        -entrante : 1
        -sortante : 2
        

      Enfin, la dernierè valeur est différente de 0 ssi on mesure une ligne de battery particulière:
        -pack de batteries OU pas de battery : 0
        -ligne 1 : 1
        -ligne 2 : 2
        -ligne 3 : 3
        -ligne 4 : 4
*/

//____________________________USEFULL FUNCTIONS_______________________//
void clean_Serial2_Port() {
  //Knowing sometimes, the serial keep some noisy bits (during manipulation), this funnction allows to
  // clean the Serial just before using it.
  // This function should be useless once we created the PCB and that nobody can get access to the circuits
  while (Serial2.available() > 0) {
    Serial2.read();
  }
}
String send_query_ESP32(String my_query,int waiting_time){
  //Pour rappel, le RX/TX de l'ESP32 est connecté à l'Arduino. Pour communiquer via UART, nous utiliseront
  //Serial1.print(my_querry) et Serial1.readStringUntil('\n')
  //La fonction send_query() est appelée au niveau de asynch_server

  //Serial2.println("Here's my query : "+my_query+"! You have "+String(waiting_time)+" seconds to give me the answer!");
  clean_Serial2_Port();
  Serial2.print(my_query+"\n");

  String answer = check_Anwer_ESP32(my_query,waiting_time);
  answer.trim(); // remove any newline characters at the end of the answer string
  return answer;
}
String return_error_msg(String query){
  if (query=="getDate" || query=="geTime"){
    //Si on ne reçoit rien via RX/TX voici ce que l'on écrit
    return "__/__/__ __:__";
  }else{
    return "No Data";
  }
}
String check_Anwer_ESP32(String my_query,int waiting_time) {
  unsigned long timeInit = millis()*0.001;
  char message[150];
  int count = 0;

  String correct_received_msg = "";
  while(true) {
    // If maximum time (5s) to wait for message reception exceeded
    if(millis()*0.001 - timeInit > waiting_time) { 
      //Serial.print(".");
      return return_error_msg(my_query);
    }
    if (Serial2.available()>0){
      while (Serial2.available()>0){
        String received_msg = Serial2.readStringUntil('\n');
        //correct_received_msg+= analyse_answer(my_query,received_msg);
        correct_received_msg+= received_msg;
        delay(100); // Au cas où la lecture de l'ESP32 soit trop rapide p/r à l'envoie de l'Arduino
      }
      return correct_received_msg;
    }
  }
}

int checkReception_ESP32(){
  //Vérifie quel query l'ESP32 a reçu et la traite
  //Cette fonction est appelée PERIODIQUEMENT contrairement à check_Anwer_ESP32 qui est appelé juste après avoir envoyé une query
  unsigned long timeInit = millis()*0.001;
  char message[150];
  int count = 0;
  
  while(true) {
    // If maximum time (20s) to wait for message reception exceeded
    if(millis()*0.001 - timeInit > 5.0) { 
      //Serial.print(".");
      return 0;
    }
    while (Serial2.available()>0){
      String my_msg = Serial2.readStringUntil('\n');
      //String my_msg = Serial2.readString();
      
      analyse_query(my_msg);
    }
  }
}
void analyse_query(String msg){
  //Lis les querys et partage les datas correspondants
  Serial.println("Le message recu : "+msg);


  //________________Web QUERY_________________//
  if (msg=="get_pv_voltage"){
    read_data_and_send("ESP32","ppv100.txt");
  }
  else if (msg=="get_pv_current"){
    read_data_and_send("ESP32","PPV020.txt");
  }
  else if (msg=="get_battery_voltage"){
    read_data_and_send("ESP32","bat100.txt");
  }
  else if (msg=="get_battery_current"){
    read_data_and_send("ESP32","bat020.txt");
  }
  else if (msg=="get_battery_SOC"){
    read_data_and_send("ESP32","bat400.txt");
  }
  else if (msg=="get_battery_SOH"){
    read_data_and_send("ESP32","bat500.txt");
  }
  else if (msg=="get_battery_temperature"){
    read_data_and_send("ESP32","bat401.txt");
  }
  else if (msg=="get_charge_current"){
    read_data_and_send("ESP32","chr010.txt");
  }

  //________________TEST QUERY_________________//
  if (msg=="getIP"){
    String msg_to_send = "je_ne_sais_pas! \n";
    for(int i=0;i<5;i++){
      Serial2.println(msg_to_send);
    }
    Serial.println("local ip: Hehehe");
  }
  else if (msg=="getDate" ||msg=="getTime" ){
    Serial.println("Hehehe, je sais pas!");
    //Serial.println("il est : "+get_time());
  }
  else if (msg=="easter" ||msg=="egg" ||msg=="easter egg" ){
    
    Serial.println("Oh non tu as découvert cet easter egg!");
    Serial.println("Hehehe, Oue il y a d'autres chose à faire, allez CIAO!");    
  }
  else{
    //Serial.println("Query pas reconnue, voici les options:");
    //Serial.println("  -getIP");
    //Serial.println("  -getDate or getTime");

  }
}



//____________________________TEST_______________________//

int checkReception_PC(){
  //Vérifie quel query l'ESP32 a reçu et la traite
  //Cette fonction est appelée PERIODIQUEMENT contrairement à check_Anwer_PC qui est appelé juste après avoir envoyé
  //une query
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
  if (query=="get_pv_voltage"){
    //read data from SD card and send it in a loop
    read_data_and_send("ESP32","pv.txt");
  }
  if(query=="get_pv_current"){
    //read data from SD card and send it in a loop
  }
  if (query=="get_battery_voltage"){
    //read data from SD card and send it in a loop
  }
  if (query=="get_battery_current"){
    //read data from SD card and send it in a loop
  }
  if (query=="get_charge_current"){
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
