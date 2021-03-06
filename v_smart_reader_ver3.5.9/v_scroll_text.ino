void scroll_text(void) {

  char cycle_number_lcd[6]={0};
  
  itoa(cycle_number, cycle_number_lcd, 10);
  send_to_lcd("     Cycle# ", 0, 0, true);
  lcd.print(cycle_number_lcd);
  lcd.setCursor(0, 1);
  lcd.print("      COMPLETED     ");
  _delay_ms(2000);

  while (!Serial1.available()) {
    send_to_lcd(" Sterilization Data ", 0, 0, true);
    unsigned char i = 0;
    char tmp = 0;

    do {
      _delay_ms(50);
      EEPROM.get(eeprom_address, tmp);

      if (tmp == 255) {
        eeprom_address = 0;
        break;
      }
      if (tmp != '\0' && i <= 20) {
        lcd.setCursor(i++, 1);
        lcd.write(tmp);
      }
      else if (tmp == '\0') {
        _delay_ms(2000);
        send_to_lcd(blank, 0, 1, false);
        i = 0;
      }
      eeprom_address += sizeof(char);
    } while (tmp != 255 && !Serial1.available());
  }
}
