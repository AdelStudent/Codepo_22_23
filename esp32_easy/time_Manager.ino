/*
Pour la personne qui va lire ce code:
  Le Time_Manager a pour principale but de déterminer l'heure et la date local ainsi que de la return sous une forme qui nous intéresse.
*/

//____________________________SETUP_SPIFFS_____________________________//
void setup_ESP32_time(){
  /*Overall, this function sets up the ESP32 to synchronize its internal clock with an NTP server, 
    ensuring that the device has an accurate and reliable time reference for time-based operations.
    
    The sntp_set_time_sync_notification_cb() function sets a callback function that is called when the time 
    is successfully synchronized with the NTP server. This callback function is timeavailable() in this case.

    The sntp_servermode_dhcp() function enables the Dynamic Host Configuration Protocol (DHCP) mode for SNTP (Simple Network Time Protocol) 
    server. This is an optional step that allows the ESP32 to obtain the IP address of the NTP server automatically.

    The configTime() function is used to configure the time zone and NTP servers to use for synchronization. The gmtOffset_sec and 
    daylightOffset_sec parameters represent the offset from Greenwich Mean Time (GMT) for the time zone where the ESP32 is located.
    The ntpServer1 and ntpServer2 parameters specify the IP addresses or domain names of the primary and secondary NTP servers to use 
    for synchronization.
  */
  // set notification call-back function
  sntp_set_time_sync_notification_cb( timeavailable );
  sntp_servermode_dhcp(1);    // (optional)
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
}

//____________________________USEFULL FUNCTIONS_______________________//
String get_time(){
  //  This function ask localTime to Internet and return it with the correct form for parsing tests

  // create a time structure
  tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    //Voici ce que l'on envoie si on n'a pas réussit à avoir la date/heure
    Serial.println("No time available (yet)");
    return "__/__/__ __:__";
  }

  // format the date and time
  String date = String(timeinfo.tm_mday < 10 ? "0" : "") + String(timeinfo.tm_mday, DEC) + "/" + String(timeinfo.tm_mon + 1 < 10 ? "0" : "") + String(timeinfo.tm_mon + 1, DEC) + "/" + String(timeinfo.tm_year + 1900, DEC);
  String time = String(timeinfo.tm_hour < 10 ? "0" : "") + String(timeinfo.tm_hour, DEC) + ":" + String(timeinfo.tm_min < 10 ? "0" : "") + String(timeinfo.tm_min, DEC) + ":" + String(timeinfo.tm_sec < 10 ? "0" : "") + String(timeinfo.tm_sec, DEC);
  String datetime = date + " " + time;

  Serial.println("Here's the date : "+datetime);
  return datetime;
}
void timeavailable(struct timeval *t){
  // THIS IS a Callback function (get called when time adjusts via NTP)
  Serial.println("Got time adjustment from NTP!");
  //printLocalTime();
}

//____________________________TEST FUNCTIONS__________________________//
void printLocalTime(){
  //test function to learn about getLocalTime and displaying
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
void printLocalTime_full(){
  //test function to learn about getLocalTime and displaying
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %d/%B/%Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}
