//code de Jeremyrenove
#include <Wire.h>
#include <EmonLib.h>

EnergyMonitor emon1;
int tension=9.3; //itier la tension (calculer au préalable avec un multimetre)
int pin_sct=A1;// pin A1 =connexion au capteur


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  emon1.current(pin_sct, 29);

}

void loop() {
  double Irms= emon1.calcIrms(1480);
  Serial.print("Courant:"); //(en ampère)
  Serial.println(Irms);



   delay(1000);// tt les 1000ms donc tt les secondes
  
}
