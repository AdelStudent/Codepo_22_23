/*
Pour la personne qui va lire ce code:
    -Le DS3231 est une horloge utilisant sa propre pile, cela permet de conserver le cours du temps même lorsque
      l'Arduino est éteint.
    -Le rôle de ce paquet de fonction est d'horodater les mesures, est de lancer le RTC_DS3231 (rtc) et celui
      d'Arduino afin des les synchroniser. Directement demander l'heure au composant était aussi possible mais
      nous préférons rester dans la logique de centraliser les informations autour de l'Arduino.
    -Ce point bonus est mis en pause pour le moment, due à un problème de pins. L'écran LCD occupe les pins SCL/SDA qui sont
      nécessaire au DS3231 et les pin SCL1/SDA1 ne semble pas fonctionner.
*/
//____________________________USEFULL FUNCTIONS_______________________//
//___________SETUP
void setup_arduino_rtc(){
  
  //rtc.begin();
  //rtc.adjust(DateTime(2023, 7, 25, 15, 55, 40)); //Permet de set la date/heure (à commenter après)
  
  
  Arduino_rtc.begin();
  synch_Arduino_DS3231();
  //Serial.println("DS3231 Time: "+get_date_DS3231_rtc());
  Serial.println("Arduino Time: "+get_date_arduino_rtc());
}

//____________________________USEFULL FUNCTIONS_______________________//

void synch_Arduino_DS3231(){
  //DateTime now = rtc.now();
  //Arduino_rtc.setTime(now.hour(),now.minute(),now.second());
  //Arduino_rtc.setDate(now.day(),now.month(),now.year());

  Arduino_rtc.setTime(16,23,34);
  Arduino_rtc.setDate(26,7,2023);

  
  
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