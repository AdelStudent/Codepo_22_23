#include <WiFi.h>
#include "time.h"
#include "sntp.h"

const char *ssid = "LAPTOP-435R1L8O";
const char *password = "FripouilleWifi";


const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


void timeavailable(struct timeval *t){
  // Callback function (get's called when time adjusts via NTP)
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}
void setup_ESP32_time(){
  // set notification call-back function
  sntp_set_time_sync_notification_cb( timeavailable );
  sntp_servermode_dhcp(1);    // (optional)
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
}
void setup()
{
  Serial.begin(115200);
  setup_ESP32_time();

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");

}

void loop()
{
  delay(5000);
  printLocalTime();     // it will take some time to sync time :)
}
