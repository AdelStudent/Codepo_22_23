

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  String files[] = {"data1.txt", "data2.txt", "data3.txt"}; 
  int numFiles = sizeof(files) / sizeof(String);

  Report(files, numFiles);

  //Lire ce qu'il y a dans le rapport 
  String fileName = "Report.txt";
  File myFile = SD.open(fileName, FILE_READ);

  if (myFile) {
    Serial.println("Lecture des données du fichier Report.txt : ");
    char buffer[40];
    while (myFile.available()) {
      myFile.readBytesUntil('\n', buffer, sizeof(buffer));
      Serial.println(buffer);
    }
    myFile.close();
  } else {
    Serial.println("Erreur lors de l'ouverture du fichier.");
  }
  //sentences();
  pote();
}

void loop() {
}