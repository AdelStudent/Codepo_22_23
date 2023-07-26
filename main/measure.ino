/*
Pour la personne qui va lire ce code:
    Le rôle de ce paquet de fonction est de prendre une succession de mesures et les écrire dans la carte SD.
    C'est donc ici que l'Arduino demande l'heure/date à l'ESP32 au travers de "measure_and_save()" et écrira la data sous
    une forme voulue. (Ex: 13/07/2023 11:10:02 # 27.76)
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
  
  //String date = "__/__/__ __:__";
  String date = send_query_ESP32("getDate",5);
  //String date = get_date_arduino_rtc();
  
  
  
  //Thermistance
  float calculateThermistance_value = calculateThermistance();
  measure_and_save("bat400.txt",date,calculateThermistance_value);


  //Courant
  
  double grid_current = ACCurrent(nbSamples, offset_30_res020, mvPerI_30, A5, A4);
  double pv_generated_current = measureCurrent(nbSamples, offset_30_ppv020, mvPerI_30, A7, A6);
  double output_pack_bat_current = measureCurrent(nbSamples, offset_30_bat020, mvPerI_30, A3, A2);

  double input_pack_bat_current = grid_current + pv_generated_current;
  double pack_SOC = determine_SOC(input_pack_bat_current, output_pack_bat_current);


  //measure_and_save("bat500.txt", date, pack_SOC);
  measure_and_save("bat020.txt", date, output_pack_bat_current);
  measure_and_save("res020.txt", date, grid_current);
  measure_and_save("ppv020.txt", date, pv_generated_current);


  //Tension
  //float pack_bat_volt = calculateTension(A11, 910, 220);//ATTENTION!!!! LA PIN A11 CORRESPOND AU DIVISEUR RESISTIF LE PLUS FORT
  float bat_volt_1 = calculateTension(A8, 900, 220.8);//905, 219.8
  float bat_volt_2 = (calculateTension(A9, 904, 101)-calculateTension(A8, 900, 220.8));//904, 100.1
  float bat_volt_3 = (calculateTension(A10,903, 75 )-calculateTension(A9, 904, 101));//900, 74.4
  float bat_volt_4 = (calculateTension(A11,903, 57.8 )- calculateTension(A10,903, 75) );//900, 55.6
  //measure_and_save("bat100.txt",date,pack_bat_volt);

  
  measure_and_save("bat101.txt",date,bat_volt_1);
  measure_and_save("bat102.txt",date,bat_volt_2);
  measure_and_save("bat103.txt",date,bat_volt_3);
  measure_and_save("bat104.txt",date,bat_volt_4);



  update_kalman_vector(bat_volt_1,bat_volt_2,bat_volt_3,bat_volt_4,output_pack_bat_current,pv_generated_current,grid_current);

  measure_and_save("bat501.txt", date, SOC_12);
  measure_and_save("bat502.txt", date, SOC_24);
  measure_and_save("bat503.txt", date, SOC_36);
  measure_and_save("bat504.txt", date, SOC_48);
  
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
void verify_danger(float temperature, double pack_soc, double output_pack_bat_current,float bat_volt_1,float bat_volt_2,float bat_volt_3,float bat_volt_4){
  float max_temp = 40;
  double min_pack_soc = 0.50; //A checker : Si le SOC est bien en % ou en valeur absolue
  double max_pack_soc = 0.90;
  
  double max_pack_current = 60;

  float min_battery_voltage = 11.5;
  float max_battery_voltage = 14.5;
  
  
  if(!already_publish){
    if(temperature>max_temp){
      publish_temperature_warning(temperature,&init_flag);
      already_publish = true;
    }
    else if(pack_soc<min_pack_soc || max_pack_soc<pack_soc){
      publish_SOC_warning(pack_soc,&init_flag);
      already_publish = true;
    }
    else if(output_pack_bat_current<- max_pack_current || max_pack_current<output_pack_bat_current){
      publish_current_warning(output_pack_bat_current,&init_flag);
      already_publish = true;
    }
    else if(bat_volt_1<min_battery_voltage || max_battery_voltage<bat_volt_1 ){
      publish_voltage_warning(bat_volt_1,&init_flag);
      already_publish = true;
    }
    else if(bat_volt_2<min_battery_voltage || max_battery_voltage<bat_volt_2){
      publish_voltage_warning(bat_volt_2,&init_flag);
      already_publish = true;
    }
    else if(bat_volt_3<min_battery_voltage || max_battery_voltage<bat_volt_3){
      publish_voltage_warning(bat_volt_3,&init_flag);
      already_publish = true;
    }
    else if(bat_volt_4<min_battery_voltage || max_battery_voltage<bat_volt_4){
      publish_voltage_warning(bat_volt_4,&init_flag);
      already_publish = true;
    }
    else{
      already_publish = false;
    }
  }
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
double measureCurrent(int nbSamples, double offset, double mvPerI, int pinCurrent, int pinVcc) {
  //PinVCC = Pin de calibration
  double sumCur = 0.0;
  double Vref = 3300; // tension de reference de l'arduino
  int counter = 0;
  double currentTime = 0.0;
  //double I = 0.0;
  double FinalRMSCurrent = 0.0;
  double RMSCurrent;
  //Get nbSamples sumCur  
  while(counter < nbSamples) {
    if(micros() >= currentTime + 200) {
      int meas = analogRead(pinCurrent)-analogRead(pinVcc);
      sumCur = sumCur + meas;  // Add sumCur together
      currentTime = micros();
      counter = counter + 1;
    }
  }
  sumCur = sumCur / nbSamples; //Taking Average of sumCur
  //I = ((sumCur * (Vref / 1023.0)) / mvPerI) + offset;
  // Application d'un threshold sur le courant
  //RMSCurrent = sqrt(-sumCur); 
  FinalRMSCurrent = ((sumCur * (Vref / 1023.0)) / mvPerI) + offset; //Au lieu de + offset
  //return I;
  if(FinalRMSCurrent < 0.3 && FinalRMSCurrent > -0.3) { // A adapter 
    //I = 0.0;
    FinalRMSCurrent = 0.0;
  }  
  return FinalRMSCurrent;
}
float ACCurrent(int nbSamples, double offset, double mvPerI, int pinCurrent, int pinVcc) {
  //Serial.println("Did you call me?_I'm_calculateCurrent()\n");delay(100);
  double sumCur = 0;
  double Vref = 3300.0;       
  int counter = 0; 
  double currentTime = 0.0; 
  double FRMSCurrent = 0.0;
  double RMSCurrent;        
  while(counter < nbSamples){
    if (millis() >= currentTime + 0.2) { 
    // -> Pour que l'analogue input soit lue toutes les 0.2 millisec                 
      int meas = analogRead(pinCurrent) - analogRead(pinVcc); //Lit la valeur et soustrait la valeur de la calibration
      sumCur = sumCur + sq(meas);  //Accumulation des valeurs racine de meas                    
      counter = counter + 1;                   
      currentTime = millis(); //Reset -> Pour que l'échantillon soit pris au bon moment
      Serial.println(sumCur);                                   
    }
          
    if (counter == 80) { 
      //regarde si le compte d'échantillon a atteint 4000 -> fait le code tous les 0.8 secondes                      
      sumCur = sumCur / nbSamples;
      Serial.println(sumCur);         
      RMSCurrent = sqrt(sumCur);   //RMS : Root mean square -> racine carré  
      Serial.println(RMSCurrent);          
      FRMSCurrent = ((RMSCurrent* (Vref / 1023.0)) /20.83) - offset;

      //if(FinalRMSCurrent <= (625/mVperAmpValue/100) || FinalRMSCurrent > 30) { 
      if(FRMSCurrent <= (625/mVperAmpValue/100)) { 
        
        //if the current detected is less than or up to 1%, set current value to 0A
        FRMSCurrent =0; 
      }     

      calculateAndPrintCurrent(FRMSCurrent);

      return FRMSCurrent;
    }
  }
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
  float Vo = ((analogRead(pin)* 3.3)/1023); 
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


