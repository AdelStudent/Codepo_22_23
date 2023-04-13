

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial2.begin(115200);
}

void loop() {
  // read from port 1, send to port 0:
  Serial2.println("Arduino__Hello World!");
  while (!Serial2.available()) {
    Serial.print(".");
    delay(10000);
  }
  int inByte = Serial2.read();
  Serial.write(inByte);
  delay(5000);

}
