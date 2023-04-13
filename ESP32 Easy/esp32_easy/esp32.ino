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


void setup_wifi(){
    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.print("local ip: ");
  Serial.println(WiFi.localIP());
}
void setup_ESP32_time(){
  // set notification call-back function
  sntp_set_time_sync_notification_cb( timeavailable );
  sntp_servermode_dhcp(1);    // (optional)
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
    //printLocalTime();
  Serial.println("Timer begin succeed");
}
void setup_ESP32(){

  //-----------------WIFI-------------------
  setup_wifi();
  //-----------------SPIFFS-----------------
  setup_SPIFFS();
  //-----------------SERVER-----------------
  setup_asynch_server();
  //-----------------DATE-------------------
  setup_ESP32_time();
}