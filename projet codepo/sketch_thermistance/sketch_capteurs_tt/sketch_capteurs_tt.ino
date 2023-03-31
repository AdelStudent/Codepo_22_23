//code pour la tension
float R1 = 907, R2 = 270;//en kohm
float A = 8.79e-03, B = -1.1e-03, C = 6.46e-06;
#define THERMISTOR 10000 // résistance nominale de la thermistor, 10 kOhm

#define sensor A0
#define Vcc 5.0 // tension d'entrée= 5V
#define pinout A2
const int s0Pin = 2; // connect to S0 pin of TMUX1108
const int s1Pin = 3; // connect to S1 pin of TMUX1108
const int s2Pin = 4; // connect to S2 pin of TMUX1108
const int s3Pin = 5; // connect to S3 pin of TMUX1108
#define pinout A2// connect to the Vo pin of TMUX1108
#include <Wire.h>
#include <EmonLib.h>

EnergyMonitor emon1;
int tension = 9.38; //itier la tension (calculer au préalable avec un multimetre)
#define pin_sct A1// pin A1 =connexion au capteur

void setup() {
  Serial.begin(9600);
  emon1.current(pin_sct, 29);
  pinMode(sensor, INPUT);
  pinMode(pinout, INPUT);
  pinMode(s0Pin, OUTPUT);
  pinMode(s1Pin, OUTPUT);
  pinMode(s2Pin, OUTPUT);
  pinMode(s3Pin, OUTPUT);
  pinMode(pinout, INPUT);

  // set initial state for multiplexer pins
  digitalWrite(s0Pin, LOW);
  digitalWrite(s1Pin, LOW);
  digitalWrite(s2Pin, LOW);
  digitalWrite(s3Pin, LOW);
}

void loop() {
  // read Vo from currently selected input
  double Vo = analogRead(pinout) / 1023.0 * 3.3;
  double Vin = Vo * (R1 + R2) / R2;
  Serial.print("vout=");
  Serial.print(Vo);
  Serial.print("V");

  Serial.print("vin=");
  Serial.print(Vin);
  Serial.println("V");
  // select next input
  int s3 = digitalRead(s3Pin);
  int s2 = digitalRead(s2Pin);
  int s1 = digitalRead(s1Pin);
  int s0 = digitalRead(s0Pin);

  if (s3 == LOW && s2 == LOW && s1 == LOW && s0 == LOW) {
    digitalWrite(s0Pin, HIGH);
  } else if (s3 == LOW && s2 == LOW && s1 == LOW && s0 == HIGH) {
    digitalWrite(s0Pin, LOW);
    digitalWrite(s1Pin, HIGH);
  } else if (s3 == LOW && s2 == LOW && s1 == HIGH && s0 == LOW) {
    digitalWrite(s1Pin, LOW);
    digitalWrite(s2Pin, HIGH);
  } else if (s3 == LOW && s2 == LOW && s1 == HIGH && s0 == HIGH) {
    digitalWrite(s2Pin, LOW);
    digitalWrite(s3Pin, HIGH);
  } else if (s3 == LOW && s2 == HIGH && s1 == LOW && s0 == LOW) {
    digitalWrite(s1Pin, HIGH);
    digitalWrite(s2Pin, LOW);
    digitalWrite(s3Pin, LOW);
  } else if (s3 == LOW && s2 == HIGH && s1 == LOW && s0 == HIGH) {
    digitalWrite(s0Pin, HIGH);
    digitalWrite(s2Pin, LOW);
    digitalWrite(s3Pin, LOW);
  } else if (s3 == LOW && s2 == HIGH && s1 == HIGH && s0 == LOW) {
    digitalWrite(s0Pin, LOW);
    digitalWrite(s1Pin, HIGH);
    digitalWrite(s3Pin, LOW);
  } else if (s3 == LOW && s2 == HIGH && s1 == HIGH && s0 == HIGH) {
    digitalWrite(s0Pin, HIGH);
    digitalWrite(s1Pin, HIGH);
    digitalWrite(s2Pin, HIGH);
    digitalWrite(s3Pin, LOW);
  } else if (s3 == HIGH && s2 == LOW && s1 == LOW && s0 == LOW) {
    digitalWrite(s2Pin, HIGH);
    digitalWrite(s1Pin, LOW);
    digitalWrite(s0Pin, LOW);
  } else if (s3 == HIGH && s2 == LOW && s1 == LOW && s0 == HIGH) {
    digitalWrite(s3Pin, LOW);
    digitalWrite(s1Pin, LOW);
    digitalWrite(s0Pin, HIGH);
  } else if (s3 == HIGH && s2 == LOW && s1 == HIGH && s0 == LOW) {
    digitalWrite(s2Pin, HIGH);
    digitalWrite(s0Pin, LOW);
  } else if (s3 == HIGH && s2 == LOW && s1 == HIGH && s0 == HIGH) {
    digitalWrite(s3Pin, LOW);
    digitalWrite(s0Pin, HIGH);
  } else if (s3 == HIGH && s2 == HIGH && s1 == LOW && s0 == LOW) {
    digitalWrite(s3Pin, LOW);
    digitalWrite(s1Pin, HIGH);
  } else if (s3 == HIGH && s2 == HIGH && s1 == LOW && s0 == HIGH) {
    digitalWrite(s2Pin, LOW);
    digitalWrite(s1Pin, HIGH);
    digitalWrite(s0Pin, HIGH);
  } else if (s3 == HIGH && s2 == HIGH && s1 == HIGH && s0 == LOW) {
    digitalWrite(s3Pin, LOW);
    digitalWrite(s2Pin, HIGH);
    digitalWrite(s0Pin, LOW);
  } else if (s3 == HIGH && s2 == HIGH && s1 == HIGH && s0 == HIGH) {
    digitalWrite(s3Pin, HIGH);
  }
  int sensorvalue = analogRead(sensor);
  float Vx = sensorvalue * (5.0 / 1023.0);
  float V = Vcc - Vx;
  float I = Vx / 10000;
  float R = V / I;
  Serial.print("R=");
  Serial.print(R);
  Serial.print("ohm");
  Serial.print(", t=");

  float steinhart;
  float T;
  steinhart = 1 / (A + (B * log(R)) + (C * pow((log(R)), 3)));
  T = steinhart - 273.15; //pour tourner la température en degré
  Serial.print(T);
  Serial.println("°C");
  double Irms = emon1.calcIrms(1480);
  Serial.print("Courant:"); //(en ampère)
  Serial.println(Irms);


  delay(1000);
}

////This code uses digital pins 2-5 to control the select lines of the TMUX1108 multiplexer
////and analog pin A0 to read the Vo from the selected input. The `loop()` function cycles
////through all 16 input channels of the multiplexer, reading the Vo from each one in turn.
////The debounce delay of 10ms helps to reduce noise and stabilize the Vo readings.
