// MOSI/MISO/SCK pin => centre de l'Arduino
// CS pin => 53

void SD_init(int *init_flag_SD){
  //print_variable("CS_PIN",CS_PIN);
  if(SD.begin(CS_PIN)==true){
    //Serial.println("La carte SD a bien démarrée");
    *init_flag_SD = 1;
  }
  else{
    Serial.println("La carte SD n'a PAS ete trouve!");
  }
}
void writeData(String filename, String data){
  //Cette fonction sert à écrire, dans un ficher de la carte SD, les valeurs voulues
  if(init_flag_SD==1){
    file = SD.open(filename,FILE_WRITE);
    if(!file){
      Serial.println("CARE I COULDN'T OPEN THE FILE: "+filename+" FOR WRITING");
    }
    else{
      Serial.println("WRITING TO THE FILE: "+filename);
      file.println(data);
      file.close();
    }
  }
}

void readData(String filename){
  //Cette fonction sert à lire dans la carte SD
  //Pour l'instant, on lit TOUTES les donnés (à voir si c'est logique)

  if(init_flag_SD==1){
    delay(100); //Au cas où l'on enchaine écriture et lecture, on laisse le temps de terminer l'ecriture
    file = SD.open(filename);
    String current_data;
    if(!file){
      Serial.println("CARE I COULDN'T OPEN THE FILE: "+filename+" FOR READING");
    }
    else{
      Serial.println("READING FROM THE FILE: "+filename);
      char buffer[128];
      while (file.available()) {
        memset(buffer, '\0', sizeof(buffer)); // clear the buffer      
        file.readBytesUntil('\n', buffer, sizeof(buffer));
        Serial.println(buffer);
        
        send_data("ESP_truc",String(buffer));
        
        memset(buffer, '\0', sizeof(buffer)); // clear the buffer
      }
      //Serial2.write(file.read());//Envoie la data à l'ESP par Serial2
      //Serial2.println(current_data);//Envoie la data à l'ESP par Serial2

      file.close();
    }
  }
}
void send_data(String target,String data){
  if(!verify_parsed_text(data)){
    return;
  }
  Serial.println("Le texte lu est correctement écrit :"+data);

  if(target=="ThingStream"){
    Serial1.println(data);
  }
  else if(target=="ESP32"){
    Serial2.println(data);
  }
  else{
    Serial.println("Je fais semblant d'envoyer la data : "+data);
  }
}

void delete_file(String filename){
  //Si le file existe, on le supprime (utile pour les tests)
  if(verify_file_existing(filename)){
    SD.remove(filename);
    Serial.println("Le file a été delete");
  }
}
bool verify_file_existing(String filename){
  //Si le file existe, on le supprime (utile pour les tests)
  if(SD.exists(filename)){
    Serial.println("Le file existe!");
    return true;
  }else{
    Serial.println("Le file n'existe pas, tout n'était qu'une imagination collective hehe!");
    return false;
  }
}
bool verify_parsed_text(String str) {
    // Check the length of the string

    Serial.println("Here's the read string :"+str);
    print_variable_int("str.length()",str.length());
    if (str.length() <= 17 || 22 <= str.length()) {
        Serial.println("Invalid string length.");
        return 0;
    }

    // Check the format of the string
    if (str[2] != '/' || str[5] != '/' || str[8] != ' ' || str[11] != ':'
        || str[14] != ' '|| str[15] != '#' || str[16] != ' '|| str[17] < '0' || str[17] > '9'|| str[18] < '0' || str[18] > '9') {
        Serial.println("Invalid string format.");
        return 0;
    }

    // Extract the day, month, year, hour, minute, and number
    int day = str.substring(0, 2).toInt();
    int month = str.substring(3, 5).toInt();
    int year = str.substring(6, 8).toInt();
    int hour = str.substring(9, 11).toInt();
    int minute = str.substring(12, 14).toInt();
    int value = str.substring(17, 19).toInt();

    // Check the validity of the day, month, year, hour, and minute
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0
        || hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        Serial.println("Invalid date or time.");
        return 0;
    }

    // Print the parsed values
    print_variable_int("day",day);
    print_variable_int("month",month);
    print_variable_int("year",year);
    print_variable_int("hour",hour);
    print_variable_int("minute",minute);
    print_variable_int("value",value);

    return 1;
}



/*_____________________________________COMMENTARY_____________________________________*/
int initializeSD(){
  if(is_SD_ready() != 1){
    return 0;
  }
  if(createFileRead("test.txt") != 1){
    return 0;
  }
  writeToFile("Hello World! from moduleSD");

  char mon_text[8000];
  readFile(mon_text);
  closeFile();
  return 1;
}
int is_SD_ready(){
  Serial.println("Initializing SD card...");
  

  if (SD.begin(4)) {
    Serial.println("SD card is ready to use.");
    return 1;
  } else {
    Serial.println("SD card initialization failed");
    return 0;
  }
}
int createFileWrite(const char *filename){
  file = SD.open(filename, FILE_WRITE);
  if(file){
    Serial.println("File created successfully.");
    return 1;
  }else{
    Serial.println("Error while creating file.");
    return 0;
  }
}
int createFileRead(const char *filename){
  file = SD.open(filename);

  if(file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}
int writeToFile(char *text){
  if (file) {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

int readFile(char *text) {
  if (file) {
    const char *res;
    while (file.available()) {
      res = file.readString().c_str();
      Serial.print("Reading file: ");
      Serial.println(res);
    }
    sprintf(text, "\0");
    strcat(text, res); //Concatener
    
    return 1;
  } else {
    Serial.println("Couldn't read file");
    return 0;
  }
}
void readDataFromFile(char *text){
}
void closeFile(){
  if(file)
  {
    file.close();
    Serial.println("File closed");
  }
}
void saveSD(const char *filename, char* text) {
  char input[800];
  sprintf(input, text);
  SD.remove(filename);
  if(createFileWrite(filename)) {
      writeToFile(input);
      closeFile();
  }
}
void ReadSD(char *input, const char *filename) {
  if(createFileRead(filename)) {
    readFile(input);
    closeFile();
  }
}


