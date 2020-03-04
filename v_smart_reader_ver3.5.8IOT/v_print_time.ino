void print_time(void) {

  struct _time my_time = {{0}, {0}, {0}, {0}, {0}, {0}};
  get_time(&my_time);

  char _time[20] = {0};
  strcpy(_time, "20");
  strcat(_time, my_time._year);
  strcat(_time, my_time._month);
  strcat(_time, my_time._monthDay);
  strcat(_time, " ");
  strcat(_time, my_time._hour);
  strcat(_time, ":");
  strcat(_time, my_time._minute);
  strcat(_time, ":");
  strcat(_time, my_time._second);
  
  send_to_lcd(_time, 0, 0, false);
}
