/*
Pour la personne qui va lire ce code:
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
  esp_task_wdt_init(15, true);
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

    //____________________________SETUP Web Page_____________________________//
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

    //____________________________BUTTON MANAGING____________________________//
    button_downloader();
    
    //____________________________USEFULL FUNCTIONS
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
    server.onNotFound([](AsyncWebServerRequest *request){
      // Handle all GET requests that don't match any other route
      request->send(404, "text/plain", "Not found hehe");
    });
    //____________________________SERVER LAUNCHING___________________________//
    server.begin(); // Start the server
    Serial.println("Server started!!");

    
}

//____________________________USEFULL FUNCTIONS_______________________//
String exchange_data_arduino(String query){
    String answer ="";
    
    if(already_answering){
      answer = "Veuillez attendre quelques instants, l'ESP32 est en train de répondre à l'Arduino";
    }else{
      answer = send_query_Arduino(query,15); //On attend 5secondes avant d'abandonner la réponse de la query
    }

    String data = "";
    data+= answer+"\n";
    return data;
}
String ask_hour_to_internet(){
  //String date = get_time();
  String date = "get_time";
  
  return date;  
}
void button_downloader(){

    //PV
    server.on("/download_pv_current", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_pv_current on the PATH !");
      String valStr = exchange_data_arduino("get_pv_current");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"pv_current.txt\"");
      request->send(response);
    });

    //Batteries
    server.on("/download_battery_temperature", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_battery_temperature on the PATH !");
      String valStr = exchange_data_arduino("get_battery_temperature");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"battery_temperature.txt\"");
      request->send(response);
    });
    server.on("/download_battery_pack_voltage", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_battery_pack_voltage on the PATH !");
      String valStr = exchange_data_arduino("get_battery_pack_voltage");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"battery_pack_voltage.txt\"");
      request->send(response);
    });
    server.on("/download_battery_voltage_1", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_battery_voltage_1 on the PATH !");
      String valStr = exchange_data_arduino("get_battery_voltage_1");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"battery_voltage_1.txt\"");
      request->send(response);
    });
    server.on("/download_battery_voltage_2", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_battery_voltage_2 on the PATH !");
      String valStr = exchange_data_arduino("get_battery_voltage_2");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"battery_voltage_2.txt\"");
      request->send(response);
    });
    server.on("/download_battery_voltage_3", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_battery_voltage_3 on the PATH !");
      String valStr = exchange_data_arduino("get_battery_voltage_3");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"battery_voltage_3.txt\"");
      request->send(response);
    });
    server.on("/download_battery_voltage_4", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_battery_voltage_4 on the PATH !");
      String valStr = exchange_data_arduino("get_battery_voltage_4");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"battery_voltage_4.txt\"");
      request->send(response);
    });
    

    server.on("/download_battery_pack_current", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_battery_pack_current on the PATH !");
      String valStr = exchange_data_arduino("get_battery_pack_current");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"battery_pack_current.txt\"");
      request->send(response);
    });
    server.on("/download_battery_soc", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_battery_soc on the PATH !");
      String valStr = exchange_data_arduino("get_battery_soc");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"battery_soc.txt\"");
      request->send(response);
    });
    server.on("/download_battery_soh", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_battery_soh on the PATH !");
      String valStr = exchange_data_arduino("get_battery_soh");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"battery_soh.txt\"");
      request->send(response);
    });
    
    server.on("/download_charge_current", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_charge_current on the PATH !");
      String valStr = exchange_data_arduino("get_charge_current");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"charge_current.txt\"");
      request->send(response);
    });

    //Rapport
    server.on("/download_report", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/download_report on the PATH !");
      String valStr = exchange_data_arduino("get_report");

      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", valStr);
      response->addHeader("Content-Disposition", "attachment; filename=\"rapport_complet.txt\"");
      request->send(response);
    });      
  
}
void old_async_server_setup(){
  /*Au départ, nous voulions juste afficher les datas. Cependant, certaines limitations d'affichage nous empêchent d'afficher plus de 
    300 lignes. Dès lors, nous optons pour des buttons sur le site qui permette de directement télécharger le fichiers voulu.
    C'est juste mieux, on communique plus de data, plus vite et, du cote de la CAMESKIN, ils ont moins d'opérations à faire.
  */
  //____________________________PV DATA
  server.on("/get_pv_voltage", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/get_pv_voltage on the PATH !");
      String valStr = exchange_data_arduino("get_pv_voltage");

      request->send(200, "text/plain", valStr);
  });
  server.on("/get_pv_current", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/get_pv_current on the PATH !");
      String valStr = exchange_data_arduino("get_pv_current");

      request->send(200, "text/plain", valStr);
  });

  //____________________________BATTERY DATA
  server.on("/get_battery_voltage", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/get_battery_voltage on the PATH !");
      String valStr = exchange_data_arduino("get_battery_voltage");

      request->send(200, "text/plain", valStr);
  });
  server.on("/get_battery_current", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/get_battery_current on the PATH !");
      String valStr = exchange_data_arduino("get_battery_current");

      request->send(200, "text/plain", valStr);
  });

  server.on("/get_battery_SOC", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/get_battery_SOC on the PATH !");
      String valStr = exchange_data_arduino("get_battery_SOC");

      request->send(200, "text/plain", valStr);
  });
  server.on("/get_battery_SOH", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/get_battery_SOH on the PATH !");
      String valStr = exchange_data_arduino("get_battery_SOH");

      request->send(200, "text/plain", valStr);
  });

  //____________________________CHARGE DATA
  server.on("/get_charge_current", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("/get_charge_current on the PATH !");
      String valStr = exchange_data_arduino("get_charge_current");

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
}



