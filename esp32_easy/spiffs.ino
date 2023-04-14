/*
Pour la personne qui va lire ce code:
  Le SPIFFS est un gestionnaire fichier. Grace à ça, l'ESP32 est capable de conserver des fichier HTML/CSS/JS. Ce qui aide grandement
  pour la création du site hébergé sur le serveur (le fameux ESP32).
  A savoir : -Pour envoyer ces fichiers à l'ESP32, il faut utilise IDE Arduino en mode admin. et aller dans tools->"ESP32 Sketch Data Upload"
             -Les fichiers en question doivent être dans un dossier nommé "data" qui doit lui-même être dans le même dossier que le code.
  Il est possible d'écrire de la data dans l'ESP32 mais nous préférons passer par l'Arduino et sa carteSD pour le moment.
  Le seul endroit où le SPIFFS est vraiment appelé, c'est dans asynch_server.io
*/

//____________________________SETUP_SPIFFS_____________________________//

void setup_SPIFFS(){

  //print_available_memory();
  if(!SPIFFS.begin()){
    Serial.println("SPIFFS Mount Failed");
    SPIFFS.format();
    return;
  }

  listDir(SPIFFS, "/", 1);
  
  //Serial.println("\n\nSPIFFS Mount succed");
}
//____________________________USEFULL FUNCTIONS_______________________//
void print_available_memory(){
  Serial.print("SPIFFS.usedBytes() : ");
  Serial.println(SPIFFS.usedBytes());
  Serial.print("SPIFFS.totalBytes() : ");
  Serial.println(SPIFFS.totalBytes());
}
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());

            if(levels>=0){
              listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
    Serial.println("");
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
    file.close();
}
void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- file deleted");
    } else {
        Serial.println("___________Delete failed");
    }
}
//____________________________TEST FUNCTIONS__________________________//

void test_SPIFFS(){
    //listDir(SPIFFS, "/", 0);
  writeFile(SPIFFS, "/hello.txt", "Hello ");
  appendFile(SPIFFS, "/hello.txt", "World!\r\n");
  Serial.println("");
  readFile(SPIFFS, "/hello.txt");

  Serial.println("");
    //deleteFile(SPIFFS, "/hello.txt");
  Serial.println( "Test complete" );
}
void testFileIO(fs::FS &fs, const char * path){
    Serial.printf("Testing file I/O with %s\r\n", path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }

    size_t i;
    Serial.print("___________Writing" );
    uint32_t start = millis();
    for(i=0; i<2048; i++){
        if ((i & 0x001F) == 0x001F){
          Serial.print(".");
        }
        file.write(buf, 512);
    }
    Serial.println("");
    uint32_t end = millis() - start;
    Serial.printf(" - %u bytes written in %u ms\r\n", 2048 * 512, end);
    file.close();

    file = fs.open(path);
    start = millis();
    end = start;
    i = 0;
    if(file && !file.isDirectory()){
        len = file.size();
        size_t flen = len;
        start = millis();
        Serial.print("___________Reading" );
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F){
              Serial.print(".");
            }
            len -= toRead;
        }
        Serial.println("");
        end = millis() - start;
        Serial.printf("- %u bytes read in %u ms\r\n", flen, end);
        file.close();
    } else {
        Serial.println("- failed to open file for reading");
    }
}
