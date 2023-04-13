#include<WiFi.h>
#include<WebServer.h>
#include "time.h"
#include "sntp.h"

#include "FS.h"
#include "SPIFFS.h"

#include<Arduino.h>
#include<ESPAsyncWebSrv.h>
#include<SPIFFS.h> // SPIFFS is a file system that is used to store files on the ESP32 and manage them


/* You only need to format SPIFFS the first time you run a
   test or else use the SPIFFS plugin to create a partition
   https://github.com/me-no-dev/arduino-esp32fs-plugin */
#define FORMAT_SPIFFS_IF_FAILED true



//WiFi Connection
const char *ssid = "LAPTOP-435R1L8O";
const char *password = "FripouilleWifi";

//Server
//WebServer server(80);
AsyncWebServer server(80); // Create AsyncWebServer object on port 80 because it is the default port for HTTP

//Time/Date Manager
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)
