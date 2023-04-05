#include <LiquidCrystal.h>
#include <WiFi.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     0
#define UTC_OFFSET_DST 0

const int piin = 6; //Digital pin  

//void spinner() { //est une animation 
//  static int8_t counter = 0;
//  const char* glyphs = "\xa1\xa5\xdb";
//  lcd.setCursor(15, 1);
//  lcd.print(glyphs[counter++]);
//  if (counter == strlen(glyphs)) {
//    counter = 0;
//  }
//}

void LocalTimeandIPadress() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    lcd.setCursor(0, 1);
    lcd.println("Connection Err");
    return;
  }

  lcd.setCursor(8, 1);
  lcd.println(&timeinfo, "%H:%M:%S");
  

  lcd.setCursor(0, 1);
  lcd.println(&timeinfo, "%d/%m");

  lcd.setCursor(0, 0);
  lcd.print(WiFi.localIP());
}

void LCDinitialisation(){
  lcd.begin(16,2);
  pinMode(piin, INPUT);
}

void ConnectWIFI(){
  lcd.setCursor(0,0);
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print("WiFi ");

  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    //spinner();
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("Online");
  lcd.setCursor(0, 1);
  lcd.println("Updating time...");

}

void setup() {
  Serial.begin(115200);
  LCDinitialisation();
  ConnectWIFI();

  lcd.clear();

  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

void loop() {
  LocalTimeandIPadress();
  delay(250);
}