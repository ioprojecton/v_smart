void listener(char a[]) {

  unsigned char  i = 0;
  unsigned long _time = 0;
  const unsigned int timeout = 500;//from 1ms must be adjusted

  _time = millis();

  do {
    if (Serial1.available()) {
      a[i] = Serial1.read();
      i == (INPUT_BUFFER_SIZE - 1) ? i-- : i++;
    }
  } while (((a[i - 1] != '\r') && (a[i - 1] != '\n') ) && (millis() - _time) <= timeout);

  a[--i] = '\0';

  if (data_log_eeprom && *a) { //a[0]

    if (strlen(a) > 20) {
      char b[strlen(a) + 1];
      memset(b, '\0', sizeof(b));

      char *p = a;

      if (*p == ' ') {
        while (*p++ == ' ');
        --p;
      }

      for (char *c = b; p < a + (strlen(a)); ) {
        if (*p == ' ' && *(p + 1) == ' ') p++;
        else *c++ = *p++;
      }

      for (char *i = b; i <= b + strlen(b); i++) {
        EEPROM.put(eeprom_address, *i);
        eeprom_address += sizeof(char);
      }
    }

    else {
      for (char *i = a; i <= a + strlen(a); i++) {
        EEPROM.put(eeprom_address, *i);
        eeprom_address += sizeof(char);
      }
    }
  }
}
