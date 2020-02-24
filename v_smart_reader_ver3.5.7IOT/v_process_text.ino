unsigned char process_text(char a[]) {


  if (strstr(a, "TOTAL CYCLES") || strstr(a, "Total Cycles"))
    return TOTAL_CYCLES;

  else if (strstr(a, "WiFi Disconnected"))
    return WIFI_DISCONNECTED;

  else if (strstr(a, "Setting up WiFi"))
    return SETTING_UP_WIFI;

  else if (strstr(a, "IPa"))
    return GOT_IP;

  else if (strstr(a, "Midmark M11 - v1.0.0")) { // must be checked with new midmark
    m11_new = true;
    return BEGIN;
  }

  else if (strstr(a, "BEGIN") || strstr(a, "Midmark M9"))
    return BEGIN;

  else if (strstr(a, "C1"))
    return STOPPED;

  else if (strstr(a, "COMPLETE"))
    return CYCLE_COMPLETE;

  else if (strstr(a, "STERILIZING") && !strstr(a, "STERILIZING:"))
    return STERILIZING;

  else return NOTHING_USEFUL;
}
