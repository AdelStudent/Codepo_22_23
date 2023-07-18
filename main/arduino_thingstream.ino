//Le module thingstream click utilise les pin Rx1/Tx1 pour communquer (par extension =>Serial1)
/*
Pour la personne qui va lire ce code:
*/

//___________SETUP

int initThingstream(int *flag_init) {
  *flag_init = 0;
  delay(5000); // wait for the modem to initialize
  if (*flag_init == 0 ){
    // ERROR : reset the Thingstream click
    Serial.println("DEBUG");
    Serial1.println("AT+IOTDEBUG=0");
    if(checkReception() == 1) { 
      *flag_init = 1; 
        Serial.println("Debug : success");
      } else {
        Serial.println("Debug : fail");
      }
  }
  if(*flag_init == 1){
    Serial.println("CREATE");
    Serial1.println("AT+IOTCREATE");  
    if(checkReception() == 1) { 
        *flag_init = 2; 
        Serial.println("Create : success");
     } else {
        Serial.println("Create : fail");
     }
  }
  if(*flag_init == 2){
    Serial.println("CONNECT");
    Serial1.println("AT+IOTCONNECT=true"); 
    if(checkReception() == 1) { 
        *flag_init = 3; 
        Serial.println("Connect : success");
    } else {
        Serial.println("Connect : fail");
    }
  }
  if(*flag_init == 3) {
    Serial.println("SUBSCRIBE");
    Serial1.println("AT+IOTSUBSCRIBE=\"TEST1\",1");
    if(checkReception() == 1) { 
        *flag_init = 4; 
        Serial.println("Subscribe : success");
    } else {
        Serial.println("Subscribe : fail");
    }
  }
}
//____________________________USEFULL FUNCTIONS_______________________//

void publish_SOC_warning(double SOC_lvl,int *flag_init){
  char my_msg[500];
  sprintf(my_msg, "ERROR, L'etat de charge des batteries est de : %lf. Nous pensons que cela peut poser problème.", SOC_lvl);
  publish_message(my_msg,flag_init);
  memset(my_msg, 0, sizeof(my_msg));
}
void publish_temperature_warning(float temperature,int *flag_init){
  char my_msg[500];
  sprintf(my_msg, "ERROR, La température des batteries est de : %f. Nous pensons que cela peut poser problème.", temperature);
  publish_message(my_msg,flag_init);
  memset(my_msg, 0, sizeof(my_msg));
}

void publish_message(char* msg,int *flag_init){
  if(*flag_init==4){
    char message[10000] = "\0";
    char message_to_send[500];

    sprintf(message_to_send, "AT+IOTPUBLISH=\"TEST1\",1,\"%s\"", msg);
    strcat(message, message_to_send);

    Serial.print("message : ");Serial.println(message); 
    Serial1.println(message);//COMMUNICATION to Thingstream
  }else{
    Serial.println("Thingstream Error : initThingstream didn't end well");
  }
}


int checkReception() {
  unsigned long timeInit = millis()*0.001;
  char message[150];
  int count = 0;

  while(true) {
    // If maximum time (20s) to wait for message reception exceeded
    if(millis()*0.001 - timeInit > 20.0) { 
      Serial.println("To Long Time");
      return 0;
     }
    // If not yet exceeded
    //Serial.println(Serial1.available());
    //delay(500);
    
    if (Serial1.available()){
        char st = Serial1.read();
        message[count] = st;  
        message[count+1] = '\0';  
        count += 1;
        
        if(message[count-1] == '\n'){
          Serial.print("Le message recu : ");          
          Serial.print(String(message));  //Affiche le message recu
          if (analyse(message) ==  1) {
            return 1;
          } else {
            return 0;
          }
        }
     }
  }
}

int analyse (String st) {
  // Arret de la publication si le mot STOP est reçu par le Click

  //Serial.println("Analyse has been called");
  int res = 1;  
  if(st.indexOf("GO") > 0 || st.indexOf("SUCCESS") > 0) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

//____________________________TEST FUNCTIONS_______________________//
int ask_info_thingstream() {
  delay(1000); // wait for the modem to initialize

  // ERROR : reset the Thingstream click
  Serial.println("Asking Info to Thingstream");
  Serial1.println("AT+IOTINFO");
  checkReception();
}


void test_thingstream(){
  delay(1000); // wait for the modem to initialize

  // ERROR : reset the Thingstream click
  Serial.println("Complete Thingstream Test");
  Serial1.println("AT+IOTTEST");
  if(checkReception() == 1) { 
      Serial.println("Test : success");
  } else {
    Serial.println("Test : fail");
  }
}