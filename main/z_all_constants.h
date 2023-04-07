#include <SD.h>
#include <SPI.h>

#include <LiquidCrystal.h>


////////////////////////////////////////////////////////////////////
//Initialisation des variables                                     //
////////////////////////////////////////////////////////////////////
// /

//Thingstream variables
unsigned long mytime;
int init_flag = 0;
bool already_publish = false;

// SD Carde variables
File file;
#define CS_PIN 53
int init_flag_SD = 0;

// ESP32


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