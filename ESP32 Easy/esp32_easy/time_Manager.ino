void timeavailable(struct timeval *t){
  // Callback function (get's called when time adjusts via NTP)
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}
String get_time(){
  // get the current time
  time_t now = time(nullptr);

  // create a time structure
  tm timeinfo;
  localtime_r(&now, &timeinfo);

  // format the date and time
  String date = String(timeinfo.tm_mday, DEC) + "/" + String(timeinfo.tm_mon + 1, DEC) + "/" + String(timeinfo.tm_year + 1900, DEC);
  String time = String(timeinfo.tm_hour, DEC) + ":" + String(timeinfo.tm_min, DEC) + ":" + String(timeinfo.tm_sec, DEC);
  String datetime = date + " " + time;

  return datetime;
}


void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
void printLocalTime_full(){
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