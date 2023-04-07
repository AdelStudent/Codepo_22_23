#include "z_all_constants.h" 
//Pour retrouver toutes les constantes, veuillez ouvrir le ficher "all_constants.h"

void setup() {
  //Permet l'affichage dans le terminal
  Serial.begin(9600);
  Serial.println("STAAAAAAAAAAAAAAAAAAAAAAART!!!");

  //Initialise la carte SD
  pinMode(CS_PIN, OUTPUT);
  SD_init(&init_flag_SD);
  
  String value = "04/04/23 15:30 # 67";  
//  writeData("PV_Current_Generated.txt", value);
//  readData("PV_Current_Generated.txt");

  writeData("test.txt", value);
  readData("test.txt");
  delete_file("test.txt");
  
  //Serial1 permettant de communiquer avec ThingStream
  Serial1.begin(115200);
  //initThingstream(&init_flag);
  
  //Serial2 permettant de communiquer avec ESP32
  Serial2.begin(115200);
  //initESP32(&init_flag);

  
  //Pin permettant la mesure des courants entrées/sorties des batteries
  //pinMode(INPUT_CURRENT_PIN, INPUT);  
  //pinMode(OUTPUT_CURRENT_PIN, OUTPUT);
}

void loop() {
  //determine_SOC();
  //publish_test(&init_flag);
  //saveSD("test.txt", "Hello World! from main");
  
}



void print_variable_float(char* variable_name, float value){
  char sentence[100] = "Voici la valeur de ";
  strcat(sentence, variable_name);
  strcat(sentence, " : ");
  char buffer[64];
  snprintf(buffer, sizeof buffer, "%f", value);
  strcat(sentence, buffer);
  Serial.println(sentence);
}
void print_variable_int(char* variable_name, int value){
  char sentence[100] = "Voici la valeur de ";
  strcat(sentence, variable_name);
  strcat(sentence, " : ");
  char buffer[64];
  snprintf(buffer, sizeof buffer, "%i", value);
  strcat(sentence, buffer);
  Serial.println(sentence);
}