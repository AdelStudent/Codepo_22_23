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
  
  //delete_all_files(); //Permet de nettoyer les fichiers facilement
  //print_filenames();
  
  
  
  //Serial1 permettant de communiquer avec ThingStream
  Serial1.begin(115200);
  //ask_info_thingstream();
  //test_thingstream();
  initThingstream(&init_flag);
  

  
  Serial2.begin(115200); //Serial2 permettant de communiquer avec ESP32
  //initESP32(&init_flag);
  

  LCD_init();
  LCD_print_IP("197.87.17.16");
  Serial.println("___________________________________________________________________");
}

void loop() {
  

  /*
  // check if it's time to take a measurement
  if (millis() - lastMeasurementTime >= 1 * 1 * 1000) {
    taking_measures();
    //determine_SOC();
    lastMeasurementTime = millis();// update the last measurement time
  }
    
  if (millis() - lastHearingTime >= 1 * 1 * 1000) {
    checkReception_ESP32();
    lastHearingTime = millis();// update the last Hearing time
  }

  if (millis() - lastReportWriting >= 1 * 60 * 1000) {
    writing_report();
    lastReportWriting = millis();// update the last report writing time
  }
   
  delay(100);
  */
  
}



