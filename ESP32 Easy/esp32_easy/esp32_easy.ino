#include"z_all_constants.h"


const int led = 2;

void setup(){
  Serial.begin(9600); // Start the Serial communication to send messages to the computer
  Serial1.begin(115200); // Start the Serial1 communication to send messages to the Arduino
  
  pinMode(led, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(led, HIGH);
  setup_ESP32();
  
}
void loop(){
  //server.handleClient();
  
  //printLocalTime();
  //delay(1000);
  //checkReception_ESP32();

}   