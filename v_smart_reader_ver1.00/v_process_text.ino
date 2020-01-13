byte process_text(char a[]) {


  if (strstr(a, "TOTAL CYCLES") != NULL)
    return TOTAL_CYCLES;

  else if (strstr(a, "C1") != NULL)
    return STOPPED;

  else if (strstr(a, "TOTAL PROCESS TIME") != NULL)
    return CYCLE_COMPLETE;

  else if (strstr(a, "HEATING") != NULL)
    return HEATING;


  else if (strstr(a, "STERILIZING") != NULL)
    return STERILIZING;


  else if (strstr(a, "MIN TEMP") != NULL)
    return MIN_TEMP;

  else if (strstr(a, "MAX TEMP") != NULL)
    return MAX_TEMP;

  else if (strstr(a, "MIN PRESS") != NULL)
    return MIN_PRESS;

  else if (strstr(a, "MAX PRESS") != NULL)
    return MAX_PRESS;

  else if (strstr(a, "VENTING") != NULL)
    return VENTING;

  else if (strstr(a, "DRYING") != NULL)
    return DRYING;

  else if (strstr(a, "TOTAL PROCESS") != NULL)
    return TOTAL_PROCESS;

  else return NOTHING_USEFUL;
}
