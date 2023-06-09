#include"z_all_constants.h"
/*
Pour la personne qui va lire ce code:
  Le code a été rangé par paquet de rôle (gestion du SPIFFS/Temps/Server/Communication)
  Le header file (.h) permet d'avoir toutes les constantes à un seul endroit ce qui allège la lecture
  Il faut utiliser le module "NodeMCU-32s" pour être reconnu par l'IDE Arduino
*/

void setup(){
  Serial.begin(9600); // Start the Serial communication to send messages to the computer
  Serial2.begin(115200); // Start the Serial2 communication to send messages to the Arduino  

  pinMode(led, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(led, HIGH);
  setup_ESP32();
  
}
void loop(){

  checkReception_Arduino(2);
  checkReception_PC(2);
  esp_task_wdt_reset();

  if (millis() - lastWifiChecking >= 5 * 60 * 1000) {
    check_Wifi();
    lastWifiChecking = millis();// update the last report writing time
  }
}   
