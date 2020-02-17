unsigned char process_text(char a[]) {


  if (strstr(a, "TOTAL CYCLES") || strstr(a, "Total Cycles"))
    return TOTAL_CYCLES;

  else if (strstr(a, "VENTING CHAMBER"))
    return VENTING_CHAMBER;

  else if (strstr(a, "Midmark M11")) { // must be checked with new midmark
    _complete = false;
    m11_new = true;
    return BEGIN;
  }

  else if (strstr(a, "BEGIN")|| strstr(a, "Midmark M9")) {
    _complete = false;
    return BEGIN;
  }

  else if (strstr(a, "C1"))
    return STOPPED;

  else if (strstr(a, "COMPLETE"))
    return CYCLE_COMPLETE;

  else if (strstr(a, "STERILIZING") && !strstr(a, "STERILIZING:"))
    return STERILIZING;

  else return NOTHING_USEFUL;
}
