/*
Pour la personne qui va lire ce code:
  La communication avec l'Arduino se fait via procédure UART. Pour cale nous utilisons les port Rx/Tx qui correspondent à:
    -Rx = pin G16
    -Tx = pin G17  
*/


#include <WiFi.h>
#include <WebServer.h>
#include "time.h"
#include "sntp.h"

#include "FS.h"

#include<Arduino.h>
#include<ESPAsyncWebSrv.h>
#include<SPIFFS.h> // SPIFFS is a file system that is used to store files on the ESP32 and manage them

#include "esp_task_wdt.h" //Allow to reset ESP32's watchdog. Otherwise, sending too much data would generate an error 

//__________________UART Arduino Comm_______________//
#define RXD2 16
#define TXD2 17
bool already_answering = false; //This variable allows us to NOT send any query to Arduino if it send us something.
                                  //Otherwise, we could send queries as "get_pv_voltage" beside giving the answer as "23/04/23 13:30"

//__________________SPIFFS_Manager__________________//
#define FORMAT_SPIFFS_IF_FAILED true
/* You only need to format SPIFFS the first time you run a
   test or else use the SPIFFS plugin to create a partition
   https://github.com/me-no-dev/arduino-esp32fs-plugin 
*/

unsigned long lastWifiChecking = 0; // variable to store the time of the last time we heard Arduino

//__________________Test_____________________________//
const int led = 2;

//__________________WiFi_Connection__________________//
/*
const char *ssid = "LAPTOP-435R1L8O";
const char *password = "FripouilleWifi";
*/

const char *ssid = "cameskin";
const char *password = "@cameskin@2021";
const char* domain = "www.mobatelisuite.com";

//__________________Server___________________________//
//WebServer server(80);
AsyncWebServer server(80); // Create AsyncWebServer object on port 80 because it is the default port for HTTP

//__________________Time/Date Manager________________//
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)
//const char* time_zone = "WAT-1";
/*This sets the time zone to West Africa Time (WAT), which is one hour ahead of Coordinated Universal Time (UTC). Kinshasa is 
  located in the WAT time zone, so this string will set the correct time zone for the ESP32 to determine the local time in Kinshasa.

  Note that the string format is "TZ-STD,OFFSET", where TZ is the time zone abbreviation, STD is the standard time abbreviation, 
  and OFFSET is the time offset from UTC in hours. In this case, the time zone abbreviation is WAT, the standard time abbreviation is -1 
  (indicating a one-hour offset from UTC), and the time offset is -1 hours.
*/




