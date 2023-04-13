void setup_SPIFFS(){

  print_available_memory();
//  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
  if(!SPIFFS.begin()){
    
      Serial.println("SPIFFS Mount Failed");
      SPIFFS.format();
      return;
  }

  listDir(SPIFFS, "/", 1);
//  test_SPIFFS();
  
  Serial.println("\n\nSPIFFS Mount succed");
}

void print_available_memory(){
  Serial.print("SPIFFS.usedBytes() : ");
  Serial.println(SPIFFS.usedBytes());
  Serial.print("SPIFFS.totalBytes() : ");
  Serial.println(SPIFFS.totalBytes());
}

void test_SPIFFS(){
  //listDir(SPIFFS, "/", 0);
  writeFile(SPIFFS, "/hello.txt", "Hello ");
  appendFile(SPIFFS, "/hello.txt", "World!\r\n");
  Serial.println("");
  readFile(SPIFFS, "/hello.txt");

  Serial.println("");
//  deleteFile(SPIFFS, "/hello.txt");
  Serial.println( "Test complete" );
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
void write_HTML(){
  String my_page = "";
  my_page+= "<!DOCTYPE html>";
  my_page+= "<html>";
  my_page+= "<head>";
  my_page+= "  <title>Button and Light Example</title>";
  my_page+= "  <link rel='stylesheet' type='text/css' href='style.css'>";
  my_page+= "</head>";
  my_page+= "<body>";
  my_page+= "  <div class='button-group'>";
  my_page+= "    <h3 class='button-label'>Button_New</h3>";
  my_page+= "    <button onclick='onButton()' style='width: 40%;'>ON</button>";
  my_page+= "    <button onclick='offButton()' style='width: 40%;'>OFF</button>";
  my_page+= "  </div>";
  my_page+= "";
  my_page+= "  <div class='button-group'>";
  my_page+= "    <h3 class='button-label'>Button_Voltage</h3>";
  my_page+= "    <button onclick='print_Voltage()' style='width: 40%;'>Print_Voltage</button>";
  my_page+= "  </div>";
  my_page+= "";
  my_page+= "  <div>";
  my_page+= "    <h3>Heure et date</h3>";
  my_page+= "    <p><span id = 'valeur_mesure'>0</span></p>";
  my_page+= "    <p><span id = 'voltage'>0</span></p>";
  my_page+= "";
  my_page+= "  </div>";
  my_page+= "  <div>";
  my_page+= "    <i><a href='https://www.youtube.com/watch?v=uWmPXwQ17Hw'>Bonne musique</a></i>";
  my_page+= "  </div>";
  my_page+= "";
  my_page+= "";
  my_page+= "  <script src='script.js'></script>";
  my_page+= "</body>";
  my_page+= "</html>";


  const char* myCharArray = my_page.c_str();
  writeFile(SPIFFS, "/index.html", myCharArray);
}
void write_CSS(){
  String my_page = "";
  my_page+= ".light {";
  my_page+= "    width: 50px;";
  my_page+= "    height: 50px;";
  my_page+= "    border-radius: 50%;";
  my_page+= "    margin: 10px;";
  my_page+= "    display: inline-block;";
  my_page+= "  }";
  my_page+= "";
  my_page+= "  .on {";
  my_page+= "    background-color: yellow;";
  my_page+= "  }";
  my_page+= "";
  my_page+= "  .off {";
  my_page+= "    background-color: white;";
  my_page+= "  }";
  my_page+= "";
  my_page+= "  .button-group {";
  my_page+= "    margin-top: 50px;";
  my_page+= "  }";
  my_page+= "";
  my_page+= "  .light-group {";
  my_page+= "    margin-top: 50px;";
  my_page+= "  }";
  my_page+= "";

  const char* myCharArray = my_page.c_str();
  writeFile(SPIFFS, "/style.css", myCharArray);
}
void write_JAVASCRIPT(){
  String my_page = "";
  my_page+= "function print_Voltage(){";
  my_page+= "  var xhttp = new XMLHttpRequest();";
  my_page+= "  xhttp.onreadystatechange = function(){";
  my_page+= "    if(this.readyState == 4 && this.status == 200){";
  my_page+= "      document.getElementById('voltage').innerHTML = this.responseText;";
  my_page+= "    }";
  my_page+= "  };";
  my_page+= "";
  my_page+= "  xhttp.open(\"GET\", \"get_voltage\", true);";
  my_page+= "  xhttp.send();";
  my_page+= "}";
  my_page+= "";
  my_page+= "function onButton(){";
  my_page+= "  //The behaviour of this function is to send a request to the path \"on\" in the main.cpp file";
  my_page+= "    //Once the request is sent, the ESP32 will execute the function that is triggered by the path \"on\"";
  my_page+= "  var xhttp = new XMLHttpRequest(); // create a new XMLHttpRequest object wich is used to send and receive data from a server";
  my_page+= "                                      //It allows the main thread to send and receive data from a server without blocking the main thread";
  my_page+= "  xhttp.open(\"GET\", \"on\", true); // true for asynchronous = non-blocking request";
  my_page+= "                                  // on is the path to the on function in the main.cpp file";
  my_page+= "                                  // Get is the method = how the data is sent";
  my_page+= "";
  my_page+= "  xhttp.send(); // send the request";
  my_page+= "}";
  my_page+= "function offButton(){";
  my_page+= "  var xhttp = new XMLHttpRequest();";
  my_page+= "  xhttp.open(\"GET\", \"off\", true); // true for asynchronous = non-blocking request";
  my_page+= "                                    // off is the path to the off function in the main.cpp file";
  my_page+= "  xhttp.send(); // send the request";
  my_page+= "}";
  my_page+= "";
  my_page+= "setInterval(function getData(){";
  my_page+= "  var xhttp = new XMLHttpRequest();";
  my_page+= "";
  my_page+= "  xhttp.onreadystatechange = function(){";
  my_page+= "    if(this.readyState == 4 && this.status == 200){";
  my_page+= "      //When the request is ready (4) and the status is OK (200)";
  my_page+= "        //then, the responseText is the data sent from the ESP32 to the server";
  my_page+= "";
  my_page+= "      //this.responseText is the data sent from the ESP32 to the server";
  my_page+= "        //and it gonna change the value with the id valeur_mesure";
  my_page+= "      document.getElementById('valeur_mesure').innerHTML = this.responseText;";
  my_page+= "    }";
  my_page+= "  }; // end of onreadystatechange function";
  my_page+= "  xhttp.open(\"GET\", \"get_luminosite\", true); // true for asynchronous = non-blocking request";
  my_page+= "  xhttp.send(); // send the request";
  my_page+= "";
  my_page+= "}, 5000); // end of setInterval function with 5000ms period";

  const char* myCharArray = my_page.c_str();
  writeFile(SPIFFS, "/script.js", myCharArray);
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
