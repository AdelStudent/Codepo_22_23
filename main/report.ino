/*
Pour la personne qui va lire ce code:
    Ici, nous déposons toutes les fonctions permettant de d'écrire un rapport et de l'envoyer à l'equipe de la CAMESKIN.
    On y traite les données sauvegardées afin de les transmettre sous le bon format.
*/

//____________________________USEFULL FUNCTIONS_______________________//
void Report(String fileNames[], int numFiles){

  if (!SD.begin(CS_PIN)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialization done.");

  int count = 0;
  float sum = 0.0;
  float arr[10];

  delete_file("Report.txt");

  for (int i=0; i < numFiles; i++){
    
    String file = fileNames[i];
    
    myFile = SD.open(file);

    if(myFile){
    
      //Serial.print(file);
      //Serial.println(":");
    
      char buffer[40];


      while(myFile.available()){
        myFile.readBytesUntil('\n', buffer, sizeof(buffer));
        buffer[sizeof(buffer)-1] = '\0';

        //Recherche du "#"
        int pos = -1;
        for (int i = 0; i < strlen(buffer); i++) {
          if (buffer[i] == '#') {
            pos = i;
            break;
          }
        }

        if (pos != -1) {
          char substring[strlen(buffer) - pos];
          for (int i = pos + 1; i < strlen(buffer); i++) {
            substring[i - pos - 1] = buffer[i];
          }
          substring[strlen(buffer) - pos - 1] = '\0';
          //Serial.println(substring);

          //Transformation de la valeur après le "#" en float
          float value = atof(substring);
          //Serial.println(value);

          count++;
          sum += value;

        } else {
          Serial.println("N'a pas trouvé la valeur (associé avec la data, après le #");
        }

      }

    //writeMeanToReport(sum, count);
    

    float mean2 = calculateMean(sum, count);
    arr[i] = mean2;
    //nbr_mean ++;
    myFile.close();
    //for (int i = 0; i < 3; i++) {
    //Serial.println(arr[i]);
    //}

    } else {
      Serial.println("Erreur dans la lecture de:");
      Serial.println(file);
    }
    
  }    
  writingReport(arr);
}
float calculateMean(float sum, int count){
  return sum / count;
}
void writingReport(float arr[]){
  myReport = SD.open("Report.txt", FILE_WRITE);
  float PV_mean = arr[0];
  float Batt_mean = arr[1];
  float Charge_mean = arr[2];
  int getArrayLength = sizeof(arr) / sizeof(float);

  if (myReport) {
    myReport.print("La puissance moyennes des PV est :"); myReport.print(PV_mean); 
    delay(100);
    myReport.print("La puissance moyennes des batteries est de :"); myReport.print(Batt_mean);
    delay(100);
    myReport.print("La puissance consommée par les charges est de :");myReport.print(Charge_mean);
    Serial.println("Rapport ecrit.");
    myReport.close();
  } else {
    Serial.println("Erreur lors de l'ouverture du rapport.");
  }
}



