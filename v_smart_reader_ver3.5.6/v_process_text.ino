unsigned char process_text(char a[]) {


  if (strstr(a, "TOTAL CYCLES") != NULL || strstr(a, "Total Cycles") != NULL)
    return TOTAL_CYCLES;

  else if (strstr(a, "Midmark M11") != NULL) { // must be checked with new midmark
    _complete = false;
    m11_new = true;
    return BEGIN;
  }

  else if (strstr(a, "BEGIN") != NULL || strstr(a, "Midmark M9") != NULL) {
    _complete = false;
    return BEGIN;
  }

  else if (strstr(a, "C1") != NULL)
    return STOPPED;

  else if (strstr(a, "COMPLETE") != NULL)
    return CYCLE_COMPLETE;

  else if (strstr(a, "STERILIZING") != NULL && strstr(a, "STERILIZING:") == NULL)
    return STERILIZING;

  else return NOTHING_USEFUL;
}
