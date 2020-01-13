void send_to_lcd(const char a[], unsigned char col, unsigned char row, bool option) {

  if (option) lcd.clear(); //automatically will set to 0,0 position

  for (unsigned char i = 0; (i < (unsigned char)strlen(a)) && strlen(a) <= 20;lcd.setCursor(col++, row), lcd.write(a[i++]));
}


//
