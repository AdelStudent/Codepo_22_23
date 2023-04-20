void pote(){
  int sensorValue = analogRead(A0);

  int nbr = 0; 

  while (nbr<10) {
    Serial.println(sensorValue);  
    delay(10000); //delay in between reads for stability
    nbr++;
  }
}

void PVEnergyProd(){
  int Rcapt = 10;
  
}