//Pour retrouver toutes les constantes, veuillez ouvrir le ficher "all_constants.h"
#include "z_all_constants.h"



void setup() {
  //Permet l'affichage dans le terminal
  Serial.begin(9600);
  Serial.println("STAAAAAAAAAAAAAAAAAAAAAAART!!!");

  //Initialise les pins permettant de prendre les mesures
  setup_measure_pins();


  //Initialise la carte SD
  pinMode(CS_PIN, OUTPUT);
  SD_init(&init_flag_SD);
  /*
    String value = "04/04/23 15:30 # 67";  
    writeData("pvCurGener.txt", value);
    read_data_and_send("PC","pvCurrentGenerated.txt");

    writeData("test.txt", value);
    read_data_and_send("PC","test.txt");
    delete_file("test.txt");
    
    //Serial1 permettant de communiquer avec ThingStream
    Serial1.begin(115200);
    //initThingstream(&init_flag);
  */

  
  Serial2.begin(115200); //Serial2 permettant de communiquer avec ESP32
  //initESP32(&init_flag);
    

}

void loop() {
  taking_measures();
  /*
  // check if it's time to take a measurement
  if (millis() - lastMeasurementTime >= 15 * 60 * 1000) {
    taking_measures();
    lastMeasurementTime = millis();// update the last measurement time
  }

  if (millis() - lastHearingTime >= 1 * 1 * 1000) {
    Serial.println("HEHEHE!!");
    checkReception_ESP32();
    lastHearingTime = millis();// update the last measurement time
  }
  */
  delay(10000);
}



