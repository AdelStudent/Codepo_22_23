// Date and time functions using just software, based on millis() & timer



void setup_arduino_rtc(){
  
  //rtc.adjust(DateTime(2023, 7, 21, 14, 53, 40));
  //rtc.begin(DateTime(2023, 7, 21, 14, 53, 40));
  
  Arduino_rtc.begin();
  synch_Arduino_DS3231();
  Serial.println("DS3231 Time: "+get_date_DS3231_rtc());
  Serial.println("Arduino Time: "+get_date_arduino_rtc());
}



void synch_Arduino_DS3231(){
  DateTime now = rtc.now();
  Arduino_rtc.setTime(now.hour(),now.minute(),now.second());
  Arduino_rtc.setDate(now.day(),now.month(),now.year());
  
}
void print_time_RTC(){
    DateTime now = rtc.now();

    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(' ');
    
    
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    delay(3000);
}
void print_time_Arduino(){
    int hour = Arduino_rtc.getHours();
    int minute = Arduino_rtc.getMinutes();
    int seconds = Arduino_rtc.getSeconds();
    
    int day = Arduino_rtc.getDay();
    int month = Arduino_rtc.getMonth();
    int year = Arduino_rtc.getYear();

    Serial.print(day, DEC);
    Serial.print('/');
    Serial.print(month, DEC);
    Serial.print('/');
    Serial.print(year, DEC);
    Serial.print(' ');
    
    
    Serial.print(hour, DEC);
    Serial.print(':');
    Serial.print(minute, DEC);
    Serial.print(':');
    Serial.print(seconds, DEC);
    Serial.println();

    delay(3000);
}

String get_date_arduino_rtc(){
  String hour = String(Arduino_rtc.getHours());
  String minute = String(Arduino_rtc.getMinutes());
  String seconds = String(Arduino_rtc.getSeconds());
  
  String day =String(Arduino_rtc.getDay());
  String month = String(Arduino_rtc.getMonth());
  String year = String(Arduino_rtc.getYear());

  String date = day+"/"+month+"/"+year+" "+hour+":"+minute+":"+seconds;

  return date;
}

String get_date_DS3231_rtc(){
  DateTime now = rtc.now();

  String hour = String(now.hour());
  String minute = String(now.minute());
  String seconds = String(now.second());
  
  String day =String(now.day());
  String month = String(now.month());
  String year = String(now.year());

  String date = day+"/"+month+"/"+year+" "+hour+":"+minute+":"+seconds;

  return date;
}