//code pour la tension
float R1 = 907, R2 = 270;//en kohm
#define Vcc 5.0 // tension d'entrée= 5V
#define pinout A0

void setup() {
  Serial.begin(9600);
  pinMode(pinout, INPUT);
   
}

void loop() {
  // read Vo from currently selected input
  double Vo = (analogRead(pinout) / 1023.0) * 3.3;
  double Vin = Vo * (R1 + R2) / R2;
  Serial.print("vout=");
  Serial.print(Vo);
  Serial.print("V ");

  Serial.print("vin=");
  Serial.print(Vin);
  Serial.println("V");


  delay(1000);
}





////This code uses digital pins 2-5 to control the select lines of the TMUX1108 multiplexer
////and analog pin A0 to read the Vo from the selected input. The `loop()` function cycles
////through all 16 input channels of the multiplexer, reading the Vo from each one in turn.
////The debounce delay of 10ms helps to reduce noise and stabilize the Vo readings.
