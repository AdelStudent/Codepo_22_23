//Pour retrouver toutes les constantes, veuillez ouvrir le ficher "z_all_constants.h"
#include "z_all_constants.h"



void setup() {
  
  Serial.begin(9600);//Permet l'affichage dans le terminal
  Serial.println("STAAAAAAAAAAAAAAAAAAAAAAART!!!");
  
  setup_arduino_rtc();
  
  
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
  //initThingstream(&init_flag);
  

  //Serial2 permettant de communiquer avec ESP32
  Serial2.begin(115200);
  
  
  LCD_init();
  delay(500);
  //esp32_ip = send_query_ESP32("getIP",3);
  //LCD_print_IP(esp32_ip);
  LCD_print_IP(get_date_arduino_rtc());

  //Initialisation de Kalman 
  creationParametreKalman();
  
  Serial.println("___________________________________________________________________");
}

void loop() {
  /*
  // check if it's time to take a measurement
  if (millis() - lastMeasurementTime >= 15 * 60 * 1000) {
    taking_measures();
    FiltreKALMAN();
    lastMeasurementTime = millis();// update the last measurement time
  }
    
  if (millis() - lastHearingTime >= 1 * 2 * 1000) {
    checkReception_ESP32();
    lastHearingTime = millis();// update the last Hearing time
  }

  if (millis() - lastReportWriting >= 30 * 60 * 1000) {
    writingReport();
    lastReportWriting = millis();// update the last report writing time
  }
  
  if (millis() - lastAskingTime >= 5 * 60 * 1000) {
    esp32_ip = send_query_ESP32("getIP",3);
    //A priori, esp32_ip = 192.168.1.127
    LCD_print_IP(esp32_ip);
    lastAskingTime = millis();// update the last Hearing time
  }

  
  if (millis() - answering_mode_chrono >= 1 * 30 * 1000) {
    //With that, we're sure that after some time, answering_mode = false and we'll be able to send query again
    answering_mode = false;
    answering_mode_chrono = millis();// update the last Hearing time
    //Serial.println("Hey I turned OFF the mode to answering_mode via the loop");
    
  }
  delay(100);
  */
  /*
  if (millis() - lastMeasurementTime >= 1 * 60 * 1000) {
    publish_SOC_warning(20.7,&init_flag_SD);
    lastMeasurementTime = millis();// update the last measurement time
  }
  */

  
}



