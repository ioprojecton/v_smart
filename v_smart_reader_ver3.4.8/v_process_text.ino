unsigned char process_text(char a[]) {


  if (strstr(a, "TOTAL CYCLES") != NULL || strstr(a, "Total Cycles") != NULL) {
    send_to_lcd("     Cycle#", 0, 0, true);
    char cycle_number_ascii[6];
    memset(cycle_number_ascii, '\0', sizeof(cycle_number_ascii));//filling it with zero
    for (unsigned char i = 0, b = 0; i < strlen(a); i++) {
      if (isdigit(a[i])) {
        cycle_number_ascii[b++] = a[i];
        lcd.write(a[i]);
      }
    }
    cycle_number = (unsigned int)atoi(cycle_number_ascii);

    have_cycle_number = true;

    return TOTAL_CYCLES;
  }

  else if (strstr(a, "Midmark - v1.0.0 ") != NULL) { // must be checked with new midmark
    m11_new = true;
    return BEGIN;
  }
  
  else if (strstr(a, "BEGIN") != NULL || strstr(a, "Midmark") != NULL) {
    _complete = false;
    return BEGIN;
  }

  else if (strstr(a, "C1") != NULL)
    return STOPPED;

  else if (strstr(a, "COMPLETE") != NULL)
    return CYCLE_COMPLETE;

  else if (strstr(a, "STERILIZING") != NULL && strstr(a, "Drying Complete") == NULL) {
    eeprom_address = 0;
    data_log_eeprom = true;
    return STERILIZING;
  }


  else return NOTHING_USEFUL;
}
