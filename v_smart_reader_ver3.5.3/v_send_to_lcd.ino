void send_to_lcd(const char a[], unsigned char col, unsigned char row, bool option) {

  if (option) lcd.clear();

  if (strlen(a) > 20) {
    char b[strlen(a) + 1];
    memset(b, '\0', sizeof(b));
    char *p = a;
 
    while (*p++ == ' ');
  
    --p; // may need to deal with this if will give a problem
    
    for (char *c = b; p < a + (strlen(a)) ;) {
      if (*p == ' ' && *(p + 1) == ' ') p++;
      else *c++ = *p++;
    }

    for (char *i = b; i < b + strlen(b); lcd.setCursor(col++, row), lcd.write(*i++));
    return;
  }
  for (char *i = a; i < a + strlen(a); lcd.setCursor(col++, row), lcd.write(*i++));
}


//
