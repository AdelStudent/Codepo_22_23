/*
Pour la personne qui va lire ce code:
    Ce fichier en .h ne sera appelé que par le header file "z_all_constantes". Cette méthode nous a permis de travailler en parallèle
    tout en faisant un merge aisé ainsi que nous permettant de nous y retrouver rapidement.
*/

//ECRAN LCD
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C LCD(0x27,16,2);

//PINS
  //A0 -> thermistance 
  //A1 -> mesure courant 
  //A2 -> calibration capteur de courant 
  //A3 -> sortie du multiplexeur 
  //2 -> ENpin du multiplexeur 
  //4 -> Decision de channel du multi
  //7 -> Decision de channel du multi
  //8 -> Decision de channel du multi
//___________________THERMISTANCE___________________//
#define Tsensor A0

float A = 8.79e-03, B =-1.1e-03, C = 6.46e-06; //Coef. permettant de déterminer la température grâce 
#define THERMISTOR 10000 // résistance nominale de la thermistor, 10 kOhm
#define Vcc 5.0 // tension d'entrée= 5V


//_________________Capteur COURANT_________________//
  //AC & DC Current Sensor with LCD By Solarduino 
  //AC & DC current captor -> HSTS016L Hall effect split core current transformer
  //The current measured is the Root Mean Square (RMS) value.

int decimalPrecision = 4; //Precision -> nombre de décimales 

//_________________PINS
int currentAnalogInputPin = A1;    // Pin to measure Current Value -> celle connecté au sensor [JAUNE]
int calibrationPin = A2;         // Pin to calibrate offset middle value -> calibre le senseur [BLANC]

//_________________Variables
float manualOffset = 0;  //0.26 -0.37  0.280    // Key in value to manually offset the initial value -> Pourrait l'utiliser si on arrive vraiment pas à ce qu'on veut 
// pour ajuster manuellement la lecture du courant initiale si nécessaire 
float mVperAmpValue = 31.25; //31.25 -20.83    // mVperAmp = maximum voltage range (in milli volt) / current rating of CT
//Specifie le mV/A puissance du transformateur de courant 
// For a 20A Hall-Effect Current Transformer rated at 20A, 2.5V +/- 0.625V, mVperAmp will be 625 mV / 20A = 31.25mV/A 

float supplyVoltage = 3300;        // Analog input pin maximum supply voltage, Arduino Uno or Mega is 5000mV while Arduino Nano or Node MCU is 3300mV
// Interessant de noter que toutes les données sont en mV
//Maximum tension d'entrée aux pins analogue de l'Arduino  
float offsetSampleRead = 0;        // to read the value of a sample for offset purpose later 
//Pour lire une valeur échantillon pour déterminer le décalage de/par rapport calibration 
float currentSampleRead  = 0;      // to read the value of a sample including currentOffset1 value
//Utiliser pour lire la valeur de courant pour chaque échantillon 
float currentLastSample  = 0;      //to count time for each sample. Technically 1 milli second 1 sample is taken 
//Pour tracker le temps depuis que le dernier échantillon a été pris 
float currentSampleSum   = 0;      // accumulation of sample readings 
//Accumulate les valeurs échantillons 
float currentSampleCount = 0;      // to count number of sample. 
float currentMean ;                // to calculate the average value from all samples, in analog values
float RMSCurrentMean ;             // square roof of currentMean, in analog values  
float FinalRMSCurrent ;            // the final RMS current

//Du capteur de l'année passée 
int nbSamples = 100;
double mvPerI_20 = 31.25;
double offset_20 = 0.36;
double mvPerI_100 = 6.25;
double offset_100 = 1.6;
double mvPerI_30 = 20.83;
double offset_30 = 0.65; //0.65

//_____CAPTEUR DE TENSION/MULTIPLEXEUR___________//
  // basé sur le code https://www.aranacorp.com/fr/utilisation-dun-multiplexer-avec-arduino/
  
//_________________CONSTANTS
#define number_of_mux 1 //définition du nombre de multiplexeur
#define numOfMuxPins number_of_mux * 8 //définition du nombre de pins totals (en fonction du nombre de multiplexeur)

//_________________PINS
  //Pins qui indique les portes à ouvrir sur l'Arduino
#define enPin 2 //Quand cette pin est high, tous les switchs sont off 
#define channelA0 4 //pin A0 du mult (11 sur mult) -> pin 4 digital de l'Arduino
#define channelA1 7 //pin A1 du mult (10 sur mult) -> pin 7 digital de l'Arduino
#define channelA2 8 // pin A2 du mult (9 sur mult) -> pin 8 digital de l'Arduino

//Tension de sortie que l'on veut mesuré après le montage avec diviseur résistif 
#define pinout A3  // pin analogue A1

float measured_value[] = {0,0,0,0,0,0,0,0}; //vecteur qui prend les valeurs 
//i ème position du vecteur sera égale à la valeur mesuré sur la ième porte 

//Paramètre
const int D  = 3; //Drain pin, allows to send/receive signals. Connecté selon les indications du site

//_________________PARAMETRES PROTOTYPE
float R1 = 913, R2 = 280;//en kohm 
// à corriger avec ce qui est lu par le multimètre : pas 907 et 270 mais 913 et 280

//#define Vcc 5.0 // tension d'entrée= 5.0V
//=> Déjà définie pour la thermistance
