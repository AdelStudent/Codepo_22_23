

// basé sur le code https://www.aranacorp.com/fr/utilisation-dun-multiplexer-avec-arduino/
//Constants
#define number_of_mux 1
#define numOfMuxPins number_of_mux * 8
#define enPin 2
#define channelA0 4 //pin digital A0
#define channelA1 7 // pin digital A1
#define channelA2 8 // pin digital A2
#define pinout A1  // pin analogue A1
//Parameters
const int D  = 3;
float R1 = 907, R2 = 270;//en kohm
#define Vcc 5.0 // tension d'entrée= 5V

void setup() {
  //Init Serial USB
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  //Init CD4051B
  pinMode(channelA0, OUTPUT);
  pinMode(channelA1, OUTPUT);
  pinMode(channelA2, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(pinout, INPUT);
  // intitialisation des pin digital a l'état bas
  digitalWrite(channelA0, LOW);
  digitalWrite(channelA1, LOW);
  digitalWrite(channelA2, LOW);
  digitalWrite(enPin, LOW);
}

void loop() {
  MuxTension();
}

void selectChannel(int chnl) { /* function selectChannel */
  //// Select channel of the multiplexer
  int A = bitRead(chnl, 0); //Take first bit from binary value of i channel.
  int B = bitRead(chnl, 1); //Take second bit from binary value of i channel.
  int C = bitRead(chnl, 2); //Take third bit from value of i channel.
  digitalWrite(channelA0, A);
  digitalWrite(channelA1, B);
  digitalWrite(channelA2, C);
  
  int Vo = (analogRead(pinout) / 1023.0) * 3.3;
  double Vin = Vo * (R1 + R2) / R2;
  
  Serial.print(F("channel ")); Serial.print(chnl); Serial.print(F(" : "));
  Serial.print(C);
  Serial.print(F(","));
  Serial.print(B);
  Serial.print(F(","));
  Serial.print(A);
  Serial.println();
  Serial.print("vout=");
  Serial.print(Vo);
  Serial.print("V ");

  Serial.print("vin=");
  Serial.print(Vin);
  Serial.println("V");
}

void MuxTension() { /* function MuxLED */
  
  //// A1link leds
  for (int i = 0; i <  numOfMuxPins; i++) {
    selectChannel(i);
    Serial.print(F("Batterie ")); Serial.print(i); Serial.println(F(" HIGH"));
    analogWrite(D, 200);
    delay(200);
    Serial.print(F("Batterie ")); Serial.print(i); Serial.println(F(" LOW"));
    analogWrite(D, 0);
  }
}




























////code pour la tension
//float R1 = 907, R2 = 270;//en kohm
//#define Vcc 5.0 // tension d'entrée= 5V
//#define pinout A0
//
//void setup() {
//  Serial.begin(9600);
//  pinMode(pinout, INPUT);
//   
//}
//
//void loop() {
//  // read Vo from currently selected input
//  double Vo = (analogRead(pinout) / 1023.0) * 3.3;
//  double Vin = Vo * (R1 + R2) / R2;
//  Serial.print("vout=");
//  Serial.print(Vo);
//  Serial.print("V ");
//
//  Serial.print("vin=");
//  Serial.print(Vin);
//  Serial.println("V");
//
//
//  delay(1000);
//}
