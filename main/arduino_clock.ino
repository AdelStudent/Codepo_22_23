
/*
void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Check if the RTC module is connected
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Set the RTC to the current date and time
  // Uncomment the following line and modify the values if needed
  // rtc.adjust(DateTime(__DATE__, __TIME__));

  // Uncomment the following line to manually set the date and time
  // rtc.adjust(DateTime(2023, 7, 3, 12, 0, 0));

  // Comment the above two lines if you want to retain the previous date and time

  // Check if the RTC lost power and if so, set the date and time to the compiled date and time
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  // Get the current date and time from the RTC module
  DateTime now = rtc.now();

  // Print the current date and time
  Serial.print("Current Date: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" - ");

  Serial.print("Current Time: ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);

  Serial.println();

  delay(1000); // Wait for 1 second before printing the date and time again
}
*/