/*
Pour la personne qui va lire ce code:
    -Ici, la méthode de Coulomb Couting a été choisie. Il est toute fois possible de changer cet algo par un autre plus fin comme
      le filtre de Kalman.
*/

//____________________________USEFULL FUNCTIONS_______________________//
void determine_SOC(){

  float SOC_variation = 0;
  float SOC_init = 0.8;
  float SOC = 0;
  // Check if it's time to take another sample
  if (millis() - lastSampleTime >= SAMPLE_INTERVAL) {
  lastSampleTime = millis(); // Reset the last sample time

  // Paramètres initiaux
  float battery_capacity = 200; //unité : [Ah]
  // Prise des échantillons pour en déterminer la moyenne
  float inputCurrentTotal = 0;
  float outputCurrentTotal = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    inputCurrentTotal += analogRead(INPUT_CURRENT_PIN);
    outputCurrentTotal += analogRead(OUTPUT_CURRENT_PIN);
  }
  inputCurrent = inputCurrentTotal / NUM_SAMPLES;
  outputCurrent = outputCurrentTotal / NUM_SAMPLES;

  // Calculate the charge flow as the integral of the difference between the input and output currents
  chargeFlow += ((inputCurrent - outputCurrent) * SAMPLE_INTERVAL) / 1000.0;
  SOC_variation = chargeFlow/battery_capacity;
  SOC_init = 0.8;
  SOC = verify_SOC(SOC_init,SOC_variation);
  // Print the input and output currents and the charge flow for debugging
  print_things(inputCurrent,outputCurrent,chargeFlow,SOC_variation);
  }
}
float verify_SOC(float SOC_init,float SOC_variation){
  float SOC=0;
  if(SOC_init+SOC_variation>=1){
    Serial.println("Attention, le SOC calculé vaut 1");
    SOC = 1;
  }else{
    SOC = SOC_init + SOC_variation;
  }
  return SOC;
}

//________________________________TEST_______________________________//
void print_things(float inputCurrent,float outputCurrent,float chargeFlow,float SOC_variation){
  Serial.print("Input current: ");
  Serial.print(inputCurrent);
  Serial.print(" mA\nOutput current: ");
  Serial.print(outputCurrent);
  Serial.print(" mA\nCharge flow: ");
  Serial.print(chargeFlow);
  Serial.println("mAh\nSOC variation: ");
  Serial.print(SOC_variation);
}