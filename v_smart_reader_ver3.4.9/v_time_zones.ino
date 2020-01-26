const char* time_zones(unsigned int *u) {
  const char *eastern_time = "   EASTERN TIME    ";
  const char *central_time = "   CENTRAL TIME    ";
  const char *mountain_time = "  MOUNTAIN TIME    ";
  const char *pacific_time = "   PACIFIC TIME    ";
  const char *atlantic_time = "   ANTLANTIC TIME  ";
  const char *newfoundland_time = "  NEWFOUNLAND TIME ";

  EEPROM.put(EEPROM_zone, *u);

  switch (*u) {
    case 0:
      return eastern_time;
      break;

    case 1:
      return central_time;
      break;

    case 2:
      return mountain_time;
      break;

    case 3:
      return pacific_time;
      break;

    case 4:
      return atlantic_time;
      break;

    case 5:
      return newfoundland_time;
      break;

    default:
      break;

  }
  return NULL;
}
