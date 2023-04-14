#include"z_all_constants.h"
/*
Pour la personne qui va lire ce code:
  Le code a été rangé par paquet de rôle (gestion du SPIFFS/Temps/Server/Communication)
  Le header file (.h) permet d'avoir toutes les constantes à un seul endroit ce qui allège la lecture
*/

void setup(){
  Serial.begin(9600); // Start the Serial communication to send messages to the computer
  Serial1.begin(115200); // Start the Serial1 communication to send messages to the Arduino
  
  pinMode(led, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(led, HIGH);
  
  setup_ESP32();
  
}
void loop(){
  //checkReception_ESP32();
  checkReception_PC();

}   