void scroll_text(void) {
  char cycle_number_lcd[6];
  memset(cycle_number_lcd, '\0', sizeof(cycle_number_lcd));
  itoa(cycle_number, cycle_number_lcd, 10);
  send_to_lcd("Cycle#", 0, 0, true);
  lcd.print(cycle_number_lcd);
  lcd.setCursor(0,1);
  lcd.print("      COMPLETED     ");
  

  while (!Serial1.available()) {
  //what it should scroll???
  //all data that must be scrolled can be written to EEPROM then accessed from here;
  }
}
