//code pour la thermistance
float A = 8.79e-03, B =-1.1e-03, C = 6.46e-06;
#define THERMISTOR 10000 // résistance nominale de la thermistor, 10 kOhm
#define Vcc 5.0 // tension d'entrée= 5V
 
#define sensor A0
 
void setup() {
    Serial.begin(9600);
    pinMode(sensor, INPUT);
}
 
void loop() {
    int sensorvalue = analogRead(sensor);
    float Vo = sensorvalue * (5.0 / 1023.0);
    float V = Vcc - Vo;
    float I = Vo / 10000;
    float R = V / I;
    Serial.print("R=");
    Serial.print(R);
    Serial.print("ohm");
    Serial.print(", t=");
 
    float steinhart;
    float T;
    steinhart = 1/(A + (B * log(R)) + (C * pow((log(R)),3)));
    T = steinhart - 273.15; //pour tourner la température en degré
    Serial.print(T);
    Serial.println("°C");
    delay(1000);
}
