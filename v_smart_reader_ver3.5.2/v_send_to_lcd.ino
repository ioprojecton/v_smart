void send_to_lcd(const char a[], unsigned char col, unsigned char row, bool option) {

  if (option) lcd.clear();

  if (strlen(a) > 20) {
    char b[strlen(a) + 1];
    memset(b, '\0', sizeof(b));

    for (unsigned char i = 0, c = 0, flag = 0; i < strlen(a); i++) {

      if (a[i] == ' ' && a[i + 1] == ' ') continue;

      else if (a[i] == ' ' && a[i + 1] != ' ' && !flag) {
        flag = 1;
        continue;
      }
      else b[c++] = a[i];
    }

    for (unsigned char *i = b; i < b + (unsigned char)strlen(b); lcd.setCursor(col++, row), lcd.write(*i++));
    return;
  }
  for (unsigned char *i = a; i < a + (unsigned char)strlen(a); lcd.setCursor(col++, row), lcd.write(*i++));
}


//
