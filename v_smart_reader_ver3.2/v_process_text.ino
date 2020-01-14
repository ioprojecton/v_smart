unsigned char process_text(char a[]) {


  if (strstr(a, "TOTAL CYCLES") != NULL)
    return TOTAL_CYCLES;

  else if (strstr(a, "BEGIN") != NULL){
    _complete = false;
    return BEGIN;
  }

  else if (strstr(a, "C1") != NULL)
    return STOPPED;

  else if (strstr(a, "COMPLETE") != NULL)
    return CYCLE_COMPLETE;

  else if (strstr(a, "STERILIZING") != NULL) {
    eeprom_address=0;
    data_log_eeprom = true;
    return STERILIZING;
  }

  else return NOTHING_USEFUL;
}
