#include <SD.h>
#include <SPI.h>
#include <stdlib.h>
#include <SoftwareSerial.h>

const int CS_PIN = 10;
int init_flag =0;
int init_flag_SD = 0;

int writing = 0;
int reading = 0;

float arr[10];

File myFile;
File myReport;

//String sentences[] = {
//  "Les panneaux solaires ont produit une puissance de : ", 
//  "Les charges ont consommés une puissance de : ",
//  "Le surplus d'énergie produit est donc de : ",
//  "La puissance circulant dans le réseau est de :",
//  "Les batteries sont chargées (état de charge/SOC) à : ",
//  "La température mesurée sur les batteries est de :",
//  "La puissance produite par les batteries est de : "};


float calculateMean(float sum, int count){
  return sum / count;
}

void writeMeanToReport(float sum, int count){

  if (count > 0) {
    float mean = calculateMean(sum, count);
    //Serial.println("Valeur moyenne: ");
    //Serial.println(mean);
    

    // open the report file
    myReport = SD.open("Report.txt", FILE_WRITE);
    
    if (myReport) {
      myReport.print("Valeur moyenne: ");
      myReport.println(mean);
      myReport.close();
      //Serial.println("Rapport ecrit.");
    } else {
      Serial.println("Erreur lors de l'ouverture du rapport.");
    }
  } else {
    Serial.println("Pas de moyenne disponible");
  }
}


void Report(String fileNames[], int numFiles){

  if (!SD.begin(CS_PIN)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialization done.");

  int count = 0;
  float sum = 0.0;


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
  writingReport();
}

void sentences(){
  for (int i = 0; i<3; i++){
    Serial.println(arr[i]);
  }
  float PV_mean = arr[0];
  float Batt_mean = arr[1];
  float Charge_mean = arr[2];

  Serial.print("La puissance moyennes des PV est :");
  Serial.println(PV_mean); 
  
  Serial.print("La puissance moyennes des Batteries est :");
  Serial.println(Batt_mean); 

  Serial.print("La puissance moyenne consommées par les charges est de :");
  Serial.println(Charge_mean); 
  
  //memset(arr, 0, sizeof(arr));
  //nbr_mean = 0;
  //clear array
  //clear nbr_mean
}

void writingReport(){
  myReport = SD.open("Report.txt", FILE_WRITE);
  float PV_mean = arr[0];
  float Batt_mean = arr[1];
  float Charge_mean = arr[2];
  
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

