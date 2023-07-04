#include <SD.h>
#include <SPI.h>


#include <Wire.h>
#include "RTClib.h"


////////////////////////////////////////////////////////////////////
//Initialisation des variables                                    //
////////////////////////////////////////////////////////////////////
// Define values for debugging/
unsigned long mytime;
int init_flag = 0;
bool already_publish = false;
// Define SD module pin
#define CS_PIN 4
// Allows to create/modify files
File file;
int SD_pin = 10; //Pin arbitraire 
File myFile;

// Define the input and output pins for the current sensors
#define INPUT_CURRENT_PIN A0
#define OUTPUT_CURRENT_PIN A1
// Define the sample interval (in milliseconds) and the number of samples to take
#define SAMPLE_INTERVAL 1000
#define NUM_SAMPLES 10


// Define variables to store the input and output currents and the charge flow
float inputCurrent = 0;
float outputCurrent = 0;
float chargeFlow = 0;

// Define a variable to keep track of the last sample time
unsigned long lastSampleTime = 0;

// Define the RTC DS3231 object to keep the hour tracking  
RTC_DS3231 rtc;