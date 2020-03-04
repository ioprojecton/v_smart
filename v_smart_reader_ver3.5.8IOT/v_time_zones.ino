const char* time_zones(unsigned char *u) {
  
  const char *p[] = {"   EASTERN TIME", "   CENTRAL TIME", "  MOUNTAIN TIME", "   PACIFIC TIME", "   ANTLANTIC TIME", "  NEWFOUNLAND TIME"};

  EEPROM.put(EEPROM_zone, *u);

  return *u <= 5 ? p[*u] : NULL;
  
}
