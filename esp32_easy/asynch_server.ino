/*
    When the user clicks the button in the HTML file, the onclick="onButton()" function in the 
        JavaScript code will be executed. This function sends a GET request to the server at the "/on" 
        path.

    When the server receives the GET request at the "/on" path, the server.on() function in the Arduino 
        sketch will call the lambda function that's defined. This lambda function can then perform any 
        actions we want on the ESP32, such as turning on an LED or performing some other task.

    So, when the user clicks the button in the HTML file, it triggers a chain of events that ultimately
        results in the ESP32 performing a specific action.
*/

//____________________________SETUP WIFI and SERVER_____________________________//
void setup_wifi(){
    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.print("local ip: ");
  Serial.println(WiFi.localIP());
}
void setup_asynch_server(){
    //We setup the behaviour of our server (ESP32) once it receive a query from the javascript
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        // When we go to the root("/") of the server, send the index.html file with the text/html content type  
            //The HTTP_GET means that we are only accepting GET requests from the client from the root
        request->send(SPIFFS, "/index.html", "text/html");// Send the HTML file to the client
        Serial.println("index.html just sended!");
    });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
        Serial.println("style.css just sended!");
    });
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/script.js", "text/javascript");
        Serial.println("script.js just sended!");
    });
    
    

    

    server.on("/get_pv_voltage", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("/get_pv_voltage on the PATH !");
        String valStr = exchange_data_arduino();

        request->send(200, "text/plain", valStr);
    });
    server.on("/get_pv_current", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("/get_voltage on the PATH !");
        String valStr = exchange_data_arduino();

        request->send(200, "text/plain", valStr);
    });
    server.on("/get_battery_voltage", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("/get_voltage on the PATH !");
        String valStr = exchange_data_arduino();

        request->send(200, "text/plain", valStr);
    });
    server.on("/get_battery_current", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("/get_voltage on the PATH !");
        String valStr = exchange_data_arduino();

        request->send(200, "text/plain", valStr);
    });
    server.on("/get_battery_current", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("/get_voltage on the PATH !");
        String valStr = exchange_data_arduino();

        request->send(200, "text/plain", valStr);
    });

    server.on("/clean_screen", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("/clean_screen on the PATH !");
        String valStr = "_";

        request->send(200, "text/plain", valStr);
    });
    server.on("/get_periodic_data", HTTP_GET, [](AsyncWebServerRequest *request){
      //Serial.println("/get_periodic_data on the PATH !");
        //int val = analogRead(capteur_luminausite);

        int val = 10;
        //String valStr = String(val);
        String valStr = ask_hour_to_internet();

        request->send(200, "text/plain", valStr);
    });
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/on on the PATH !");
            //Request is the request that the client sent to the server's on path (root/on)
        digitalWrite(led, HIGH);
        request->send(200);
    });
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/off on the PATH !");
        digitalWrite(led, LOW);
        request->send(200);
    });

    server.onNotFound([](AsyncWebServerRequest *request){
      // Handle all GET requests that don't match any other route
      request->send(404, "text/plain", "Not found hehe");
    });

    server.begin(); // Start the server
    Serial.println("Server started!!");

    
}

//____________________________USEFULL FUNCTIONS_______________________//
String exchange_data_arduino(){
    String data = "";
      /*Serial1.println("Hello from ESP32!");
        while (Serial1.available()){
          String data += Serial1.readStringUntil('\n');      
          Serial.println(data);
      }*/
    int value = 0;
    int min = 0;    
    for(int i=0;i<30;i++){
      value +=1;
      min+=1;
      data += "13/04/23 11:"+String(min)+" # "+ String(value);
      //data += "<br>";
      data += "\n"; 
    }
    data +="\0";
    return data;
}
String ask_hour_to_internet(){
  //String date = get_time();
  String date = "get_time";
  
  return date;  
}
