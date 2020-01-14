void send_to_lcd(const char a[], unsigned char col, unsigned char row, bool option) {

  if (option) lcd.clear(); //automatically will set to 0,0 position

  if (strlen(a) > 20) {
    char c = 0;
    char b[strlen(a)];
    memset(b, '\0', sizeof(b));

    for (char i = 0, flag = 0; i < strlen(a); i++) {

      if (a[i] == ' ' && a[i + 1] == ' ') continue;

      else if (a[i] == ' ' && a[i + 1] != ' ' && !flag) {
        flag = 1;
        continue;
      }
      else b[c++] = a[i];
    }
    b[c] = '\0';
    
    for (unsigned char i = 0; i < (unsigned char)strlen(b); lcd.setCursor(col++, row), lcd.write(b[i++]));
    
    return;
  }
  for (unsigned char i = 0; i < (unsigned char)strlen(a); lcd.setCursor(col++, row), lcd.write(a[i++]));
}


//
