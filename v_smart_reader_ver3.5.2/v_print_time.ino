void print_time(void) {
  char _second[3];
  memset(_second, '\0', sizeof(_second));
  char _minute[3];
  memset(_minute, '\0', sizeof(_minute));
  char _hour[3];
  memset(_hour, '\0', sizeof(_hour));
  char _monthDay[3];
  memset(_monthDay, '\0', sizeof(_monthDay));
  char _month[4];
  memset(_month, '\0', sizeof(_month));
  char _year[3];
  memset(_year, '\0', sizeof(_year));

  get_time(_second, _minute, _hour, _monthDay, _month, _year);
  char _time[20];
  memset(_time, '\0', sizeof(_time));
  strcat(_time, "20");
  strcat(_time, _year);
  strcat(_time, _month);
  strcat(_time, _monthDay);
  strcat(_time, " ");
  strcat(_time, _hour);
  strcat(_time, ":");
  strcat(_time, _minute);
  strcat(_time, ":");
  strcat(_time, _second);

  send_to_lcd(_time, 0, 0, false);
}
