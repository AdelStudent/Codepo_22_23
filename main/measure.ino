/*
Pour la personne qui va lire ce code:
    Le rôle de ce paquet de fonction est de prendre une succession de mesures et les écrire dans la carte SD.
    C'est donc ici que l'Arduino demande l'heure/date à l'ESP32 au travers de "measure_and_save()" et écrira la data sous
    une forme voulue.
*/

//____________________________USEFULL FUNCTIONS_______________________//

//___________SETUP
void setup_measure_pins() {
  pinMode(Tsensor, INPUT);
  
  //Multiplexeur 

  //Initialement pour le multiplexeur
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
//___________TAKING MEASURES
void taking_measures() {
    //Il faut encore créer une liste de mesures, à partir de là on écrira tout d'un coup dans la carte SD
    //ATTENTION A MODIFIER POUR OPTIMISER
  
  String date = send_query_ESP32("getDate",5);
  //Thermistance 
  calculateThermistance();
  measure_and_save("battery/battery/temperature.txt",date,calculateThermistance());

  //Courant
  measure_and_save("battery/thirdline/voltage.txt",date,calculateCurrent("battery/firstline/voltage.txt",A1,A2));
  measure_and_save("battery/foruthline/voltage.txt",date,calculateCurrent("battery/firstline/voltage.txt",A3,A4));

  
  //Tension
  MuxTension();

}
void measure_and_save(String filename, String date, float value){
  String line = date+" # "+String(value);
  writeData(filename,line);
}

//___________THERMISTANCE
float calculateThermistance() {
  //Output : température
  //Lit la termistance et la convertie en degrée
  
  int Tsensorvalue = analogRead(Tsensor);
  float Vo = Tsensorvalue * (5.0 / 1023.0);
  float V = Vcc - Vo;
  float I = Vo / 10000;
  float R = V / I;

  float steinhart;
  float T;
  steinhart = 1 / (A + (B * log(R)) + (C * pow((log(R)), 3)));
  T = (steinhart - 273.15) + 30; // to convert the temperature into degree
  
  //measure_and_save("thermistance/value.txt",T);
  printThermistance(R, T);
  
}
//___________CAPTEUR COURANT 
float calculateCurrent(String filename, int currentAnalogInputPin, int calibrationPin) {
  currentSampleSum = 0;               
  currentSampleCount = 0;          
  while(true){
    if (micros() >= currentLastSample + 200) { 
    // -> Pour que l'analogue input soit lue toutes les 0.2 millisec                 
      currentSampleRead = analogRead(currentAnalogInputPin) - analogRead(calibrationPin); //Lit la valeur et soustrait la valeur de la calibration  
      currentSampleSum = currentSampleSum + sq(currentSampleRead);  //Accumulation des valeurs racine de currentSampleRead                     
      currentSampleCount = currentSampleCount + 1;                   
      currentLastSample = micros(); //Reset -> Pour que l'échantillon soit pris au bon moment                                   
    }
          
    if (currentSampleCount == 4000) { 
      //regarde si le compte d'échantillon a atteint 4000 -> fait le code tous les 0.8 secondes                      
      currentMean = currentSampleSum / currentSampleCount;         
      RMSCurrentMean = sqrt(currentMean);   //RMS : Root mean square -> racine carré                    
      FinalRMSCurrent = (((RMSCurrentMean / 1023) * supplyVoltage) / mVperAmpValue) - manualOffset;

      if(FinalRMSCurrent <= (625/mVperAmpValue/100)) || (FinalRMSCurrent >30)){ //c'est aussi une erreur vu les capacités du courant 
        //if the current detected is less than or up to 1%, set current value to 0A
        FinalRMSCurrent =0; 
      }     

      calculateAndPrintCurrent(FinalRMSCurrent);
      return FinalRMSCurrent;
    }
  }
}
//___________CAPTEUR TENSION/MULTIPLEXEUR  
double selectChannel(int chnl) { 
  //Selection des channels/portes pour savoir quel passage faire pour la tension
  //si chnl = 5 => binaire = 101 => Voir le schéma de sélection des pins 
  //// Select channel of the multiplexer
  //Nous transformons le int en sa version binaire et nous transferont ces bits aux portes logiques du MUX
  int A = bitRead(chnl, 0); //Take first bit from binary value of i channel.
  int B = bitRead(chnl, 1); //Take second bit from binary value of i channel.
  int C = bitRead(chnl, 2); //Take third bit from value of i channel.
  //Les chiffres 0,1,2 sont des sélection de positions dans le mots en bits 
  digitalWrite(channelA0, A); //Envoie dans la pin de l'Arduino le 0 ou 1 trouvé dans le bit
  digitalWrite(channelA1, B);
  digitalWrite(channelA2, C);
  
  //Convertissement de la valeur numérique en tension
  // Tension = (valeur lue* tension d'alimentation)/1024  
  float Vo = ((analogRead(pinout)* Vcc)/1023); //-2.18
  // Pour retrouver la tension initiale (réelle) avant le diviseur résistif 
  // Vérifier que la tension d'alimentation sera de 3.3 
  //double Vin = (Vo * (R1 + R2) / R2);
  float Vin = Vo * (R1 + R2) / R2;

  print_channels(A,B,C,Vo,Vin);

  return Vin;
}
void MuxTension() { /* function MuxLED */
  //Puisque la liste measured_value[] n'existe QUE dans cette fonction, c'est plus propre de définir measured_value ici et 
  //après de return la list (Normalement, il suffit de remplacer void par float* et return measured_value)
  //Une fois fait, vaut mieux supprimer la variable global qui porte le même nom (dans all_constant2.h)
    
  for (int i = 0; i <  numOfMuxPins; i++) {
    double Vin = selectChannel(i);

    measured_value[i] = Vin;
    //mesaured_value[i] = analogRead(D);
    delay(200);
    Serial.print("ith porte : "); Serial.print(i); Serial.print("; measured_value[i] : "); Serial.println(measured_value[i]);
  }
  Serial.println("________________________________________________________________________________");
  delay(10000);

}



//____________________________TEST FUNCTIONS_______________________//
void print_channels(int A,int B,int C,float Vo,float Vin){
  //Serial.print(F("channel ")); Serial.print(chnl); Serial.print(F(" : "));
  Serial.print(C);
  Serial.print((","));
  Serial.print(B);
  Serial.print((","));
  Serial.print(A);Serial.println();

  Serial.print("Vp=");Serial.print(Vo);Serial.print("V ");
  //Valeur lue sur la pin de l'Arduino

  Serial.print("Vin="); Serial.print(Vin); Serial.println("V du generateur/batterie.");
  //Valeur réelle de la batterie

}
void printThermistance(float R, float T) {
  Serial.print("R=");
  Serial.print(R);
  Serial.print("ohm");
  Serial.print(", t=");
  Serial.print(T);
  Serial.println("°C");
  delay(1000);
}
void calculateAndPrintCurrent(float FinalRMSCurrent) {
  Serial.print(currentAnalogInputPin);
  Serial.print(" The Current RMS value is: ");
  Serial.print(FinalRMSCurrent, decimalPrecision);
  Serial.println(" A ");
}
/*void read_mutex_to_save(float* measured_value){
  //Un peu cracra mais ça fonctionne bien
  measure_and_save("battery/firstline/voltage.txt",measured_value[0]);
  measure_and_save("battery/secondline/voltage.txt",measured_value[1]);
  measure_and_save("battery/thirdline/voltage.txt",measured_value[2]);
  measure_and_save("battery/fourthline/voltage.txt",measured_value[3]);
    
}*/
