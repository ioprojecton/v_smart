void listener(char a[]) {

  unsigned char  i = 0;
  unsigned long _time = 0;
  bool flag = false;
  const unsigned int timeout = 500;//from 1ms must be adjusted

  _time = millis();

  do {
    if (Serial1.available()) {
      a[i] = Serial1.read();
      if (a[i] >= 10 && a[i] <= 127) {
        flag = true;
        i == (INPUT_BUFFER_SIZE - 1) ? i-- : i++;
      }
    }
  } while (((a[i - 1] != '\r') && (a[i - 1] != '\n') ) && (millis() - _time) <= timeout);

  if (flag) a[--i] = '\0';

  if (strstr(a, "VENTING") != NULL)
  {
    EEPROM.put(eeprom_address + 1, 255);
    eeprom_address = 0;
    data_log_eeprom = false;
  }

  if (data_log_eeprom && a) {
    if (strlen(a) > 20) {
      unsigned char c = 0;
      char b[strlen(a)];
      memset(b, '\0', sizeof(b));

      for (unsigned char i = 0, flag = 0; i < strlen(a); i++) { //char to unsigned char

        if (a[i] == ' ' && a[i + 1] == ' ') continue;

        else if (a[i] == ' ' && a[i + 1] != ' ' && !flag) {
          flag = 1;
          continue;
        }
        else b[c++] = a[i];
      }
      b[c] = '\0';
      for (unsigned char i = 0; i <= strlen(b); i++) {
        EEPROM.put(eeprom_address, b[i]);
        eeprom_address += sizeof(char);
      }
    }
    else {
      for (unsigned char i = 0; i <= strlen(a); i++) {
        EEPROM.put(eeprom_address, a[i]);
        eeprom_address += sizeof(char);
      }
    }
  }


}
