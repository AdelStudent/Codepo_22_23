//____________________________SETUP_Function_____________________________//
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