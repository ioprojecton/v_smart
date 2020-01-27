bool client_checker(void) {
  char a[INPUT_BUFFER_SIZE];
  memset(a, 0, sizeof(a));
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

  static bool _stopped = false;

  listener(a);

  while (!check_sd_card());
  if (!sd.chdir()) send_to_lcd("Access to / failed",0,1,false);
  char tmp_year[5];
  memset (tmp_year, '\0', sizeof(tmp_year));
  strcat(tmp_year, "20");
  strcat(tmp_year, _year);
  if (!sd.exists(tmp_year)) {
    if (!sd.mkdir(tmp_year)) send_to_lcd("Can`t make directory",0,1,false);
  }//must be terminated

  sd.chdir(tmp_year);

  if (!sd.exists(_month)) {
    if (!sd.mkdir(_month)) send_to_lcd("Can`t make directory",0,1,false);
  }

  sd.chdir(_month);

  switch (process_text(a)) {

    case CYCLE_COMPLETE:
      //sd card close file
      _complete = true;
      char tmp_cycle_number[9];
      memset(tmp_cycle_number, '\0', sizeof(tmp_cycle_number));
      itoa(cycle_number, tmp_cycle_number, 10);
      strcat(tmp_cycle_number, ".txt");

      if (!file.open("tmp.txt", O_WRONLY | O_CREAT | O_APPEND)) send_to_lcd("Can`t make file",0,1,false);
      file.print("\r\n");
      file.println(a);

      if (!file.rename(tmp_cycle_number)) send_to_lcd("Can`t rename file",0,1,false);
      file.close();
      sd.remove("tmp.txt");
      my_serial_flush();
      scroll_text();
      have_cycle_number = false;
      break;

    case STOPPED:
      _complete = false;
      char cycle_number_lcd[6];
      memset(cycle_number_lcd, '\0', sizeof(cycle_number_lcd));
      itoa(cycle_number, cycle_number_lcd, 10);
      send_to_lcd("Cycle#", 0, 0, true);
      lcd.print(cycle_number_lcd);
      lcd.setCursor(0, 1);
      lcd.print("  Manually Stopped  ");
      if (!file.open("tmp.txt", O_WRONLY | O_CREAT | O_APPEND)) send_to_lcd("Can`t make file",0,1,false);
      file.print("\r\n");
      file.println(a);
      file.close();
      my_serial_flush();
      have_cycle_number = false;
      break;

    case BEGIN:
      if (!m11_new) {
      char date_time[21];
      memset(date_time, '\0', sizeof(date_time));
      strcat(date_time, _month);
      strcat(date_time, " ");
      strcat(date_time, _monthDay);
      strcat(date_time, " 20");
      strcat(date_time, _year);
      strcat(date_time, "    ");
      strcat(date_time, _hour);
      strcat(date_time, ":");
      strcat(date_time, _minute);

      if (!file.open("tmp.txt", O_WRONLY | O_CREAT | O_APPEND)) send_to_lcd("Can`t make file",0,1,false);
      file.println(a);
      file.print("\r\n");
      file.println("------------------------");
      file.println("   Date        Time");
      file.println(date_time);
      file.println("------------------------");
      file.close();}
      send_to_lcd(blank, 0, 1, false);
      send_to_lcd(a, 0, 1, false);
      break;

    default:
      if (!have_cycle_number) {
        send_to_lcd(blank, 0, 0, false);
        send_to_lcd(_time, 0, 0, false);
      }
      send_to_lcd(blank, 0, 1, false);
      send_to_lcd(a, 0, 1, false);

      if (!file.open("tmp.txt", O_WRONLY | O_CREAT | O_APPEND)) send_to_lcd("Can`t make file",0,1,false);
      file.print("\r\n");
      file.println(a);
      file.close();
      return true;
      break;
  }

  return false;
}
