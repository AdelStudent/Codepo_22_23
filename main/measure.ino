/*
Pour la personne qui va lire ce code:
    Le rôle de ce paquet de fonction est de prendre une succession de mesures et les écrire dans la carte SD.
    C'est donc ici que l'Arduino demande l'heure/date à l'ESP32 au travers de "measure_and_save()" et écrira la data sous
    une forme voulue.

    ATTENTION: La carte SD a un comportement étrange pour les noms. Elle n'accepte pas plus de 7 caractères pour un nom de fichier
      et étrangement, elle n'accepte plus une arborescence de dossier/fichier. Dès lors, une pseudo-arborescence a été crée dans le nom
      même des fichier:
      Les 3 premiers caractères expriment le système dont on s'intéresse.
        -Battery : bat
        -Panneau photovoltaique : ppv
        -Reseau : res
        -Charges : chr

      La valeur suivante permet de savoir quelle mesures nous intéresse:
        -courant : 0
        -tension  : 1
        -puissance : 2
        -temperature : 4

      La valeur suivante permet de savoir si la mesure est entrante/sortante/aucune:
        -aucune : 0
        -entrante : 1
        -sortante : 2

      Enfin, la dernierè valeur est différente de 0 ssi on mesure une ligne de battery particulière:
        -pack de batteries OU pas de battery : 0
        -ligne 1 : 1
        -ligne 2 : 2
        -ligne 3 : 3
        -ligne 4 : 4
                             
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
  
  //String date = send_query_ESP32("getDate",5);
  String date = "__/__/__ __:__";
  
  //Thermistance
  float calculateThermistance_value = calculateThermistance();
  measure_and_save("bat101.txt",date,calculateThermistance_value);


  //Courant
  float output_pack_bat_current = calculateCurrent(A3,A2);
  float network_current = calculateCurrent(A5,A4);
  float pv_generated_current = calculateCurrent(A7,A6);
  measure_and_save("bat020.txt",date,output_pack_bat_current);
  measure_and_save("res020.txt",date,network_current);
  measure_and_save("ppv020.txt",date,pv_generated_current);



  //Tension
  float pack_bat_volt = calculateTension(A11, 910, 220);//ATTENTION!!!! LA PIN A11 CORRESPOND AU DIVISEUR RESISTIF LE PLUS FORT
  float bat_volt_1 = calculateTension(A8, 905, 219.8);
  float bat_volt_2 = calculateTension(A9, 904, 100.1);
  float bat_volt_3 = calculateTension(A10, 900, 74.4);
  //float bat_volt_4 = calculateTension(A11, 900, 55.6);

  measure_and_save("bat101.txt",date,bat_volt_1);
  measure_and_save("bat102.txt",date,bat_volt_2);
  measure_and_save("bat103.txt",date,bat_volt_3);
  measure_and_save("bat104.txt",date,bat_volt_4);


  Serial.println("We finished the measures \n\n");
  

}
void measure_and_save(String filename, String date, float value){
  //Serial.println("Did you call me?_I'm_measure_and_save()");delay(100);
  String line = date+" # "+String(value);
  writeData(filename,line);
  /*
  String str_value = String(value);
  Serial.println("Voila le fichier,la date et la valeur : "+filename+", "+date+", "+str_value);
  */
}

//___________THERMISTANCE
float calculateThermistance() {
  //Output : température
  //Lit la termistance et la convertie en degrée
  
  //Serial.println("Did you call me?_I'm_calculateThermistance()");delay(100);
  int Tsensorvalue = analogRead(Tsensor);
  float Vo = Tsensorvalue * (5.0 / 1023.0);
  float V = Vcc - Vo;
  float I = Vo / 10000;
  float R = V / I;

  float steinhart;
  float T;
  steinhart = 1 / (A + (B * log(R)) + (C * pow((log(R)), 3)));
  T = (steinhart - 273.15); // to convert the temperature into degree
  
  printThermistance(R, T);

  return T;
  
}
//___________CAPTEUR COURANT 
float calculateCurrent(int currentAnalogInputPin, int calibrationPin) {
  //Serial.println("Did you call me?_I'm_calculateCurrent()\n");delay(100);
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

      //if(FinalRMSCurrent <= (625/mVperAmpValue/100) || FinalRMSCurrent > 30) { 
      if(FinalRMSCurrent <= (625/mVperAmpValue/100)) { 
        
        //if the current detected is less than or up to 1%, set current value to 0A
        FinalRMSCurrent =0; 
      }     

      calculateAndPrintCurrent(FinalRMSCurrent);
      
      /*Serial.println(calibrationPin);
      Serial.println(currentAnalogInputPin);
      Serial.print("FinalRMSCurrent : ");
      Serial.println(FinalRMSCurrent);
      Serial.println("__________________________________________");
      */

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

  //print_channels(A,B,C,Vo,Vin);

  return Vin;
}

float calculateTension(int pin, int R1, int R2){
  float Vo = ((analogRead(pin)* Vcc)/1023); 
  float Vin = Vo * (R1 + R2) / R2;
  //condition if a mettre pour le calibrage 
  return Vin;  
}
float* MuxTension() { /* function MuxLED */
  //Puisque la liste measured_value[] n'existe QUE dans cette fonction, c'est plus propre de définir measured_value ici et 
  //après de return la list (Normalement, il suffit de remplacer void par float* et return measured_value)
  //Une fois fait, vaut mieux supprimer la variable global qui porte le même nom (dans all_constant2.h)
    
  for (int i = 0; i <  numOfMuxPins; i++) {
    double Vin = selectChannel(i);

    measured_value[i] = Vin;
    //mesaured_value[i] = analogRead(D);
    delay(200);
    //Serial.print("ith porte : "); Serial.print(i); Serial.print("; measured_value[i] : "); Serial.println(measured_value[i]);
  }
  //Serial.println("________________________________________________________________________________");
  //delay(10000);

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
  //delay(1000);
}
void calculateAndPrintCurrent(float FinalRMSCurrent) {
  Serial.print(currentAnalogInputPin);
  Serial.print(" The Current RMS value is: ");
  Serial.print(FinalRMSCurrent, decimalPrecision);
  Serial.println(" A ");
}

