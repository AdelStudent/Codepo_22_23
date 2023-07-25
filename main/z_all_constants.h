/*
Pour la personne qui va lire ce code:
    Ce header file (.h) permet d'avoir un fichier aillant tous les includes/constantes nécessaires au bon déroulement de notre protoype.
    Cela permet surtout une lecture plus aisée du projet.
*/
#include "all_constant2.h"

#include <SD.h>
#include <SPI.h>
#include "TimeLib.h"
#include "time.h"

#include "RTClib.h" //Downloaded from the follwoing git : https://github.com/adafruit/RTClib
                    //Also needed this one : https://github.com/adafruit/Adafruit_BusIO/tree/master
#include <RTCDue.h>



#include <LiquidCrystal.h>

#include <stdlib.h>



////////////////////////////////////////////////////////////////////
//Initialisation des variables                                    //
////////////////////////////////////////////////////////////////////

//_____________________Kalman Variables___//

//_____________________Multi Threading version Wish___//
unsigned long lastMeasurementTime = 0; // variable to store the last time measurement
unsigned long lastHearingTime = 0; // variable to store the last time we heard Arduino
unsigned long lastReportWriting = 0; // variable to store the last time we wrote into the Arduino
unsigned long lastAskingTime = 0; // variable to store the last time we asked IP address to ESP32
unsigned long lastUpdateFilter = 0; //variable to store the last time Kalman Filter parameters update
unsigned long last_warning_message = 0; //variable to store the last time we send potentially send a Warning Mail



//_____________________Thingstream___________________//
unsigned long mytime; //Permet de connaitre le temps d'attente pour recevoir une réponde du thingStream
int init_flag = 0;  //Permet de savoir si toutes les étapes de l'initialisation du Thingstream sont okay
bool already_publish = false; //Variable tests

//_____________________SD Card______________________//
File myFile;  //Objet permettant l'ouverture de fichiers en accès w et/ou r
File myReport;  //Par souçis de cohérence des parties de codes, on garde ces Files
File file;  //Par soucis de cohérence des parties de codes, on garde les 3 files (myFile/myReport/file)
#define CS_PIN 53 //Pin utilisée pour transmettre la data à la carte SD
int init_flag_SD = 0;


//_____________________ESP32______________________//
String esp32_ip = "";
bool answering_mode = false; //It allows to block send any queries to ESP32 if this mode is activated
unsigned long answering_mode_chrono = 0; // variable to store the time of the last time we asked IP address to ESP32

//_____________________Measures______________________//
// Define the input and output pins for the current sensors
#define INPUT_CURRENT_PIN A0
#define OUTPUT_CURRENT_PIN A1
// Define the sample interval (in milliseconds) and the number of samples to take
#define SAMPLE_INTERVAL 1000
#define NUM_SAMPLES 10
// Define variables to store the input and output currents and the charge flow
float SOC_init = 0.8;

// Define a variable to keep track of the last sample time
unsigned long lastSampleTime = 0;

//_____________________CLOCK________________________//
RTCDue Arduino_rtc(XTAL); //Arduino RTC
RTC_DS3231 rtc; //DS3231 RTC
