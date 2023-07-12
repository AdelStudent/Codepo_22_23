void LCD_init() {
  // put your setup code here, to run once:
  LCD.init();
  LCD.display();
  LCD.backlight();
  LCD.clear();
}

void LCD_print_IP(String IP_adress){
  LCD.clear();
  Serial.println("LCD affiche : "+IP_adress);
  LCDprint(0,0,"IP :");
  //LCDprint(1,0,"197.87.17.16");
  LCDprint(1,0,IP_adress);
}

void LCDprint(int start_line,int start_column, String my_string){
  LCD.setCursor(start_column,start_line); 
  int length = my_string.length();
  for (int i=0; i<length; i++) {
    LCD.print(my_string[i]);
  }
}
