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
  if (!sd.chdir()) Serial.println("access to root failed");
  char tmp_year[5];
  memset (tmp_year, '\0', sizeof(tmp_year));
  strcat(tmp_year, "20");
  strcat(tmp_year, _year);
  if (!sd.exists(tmp_year)) {
    if (!sd.mkdir(tmp_year)) Serial.println("cant create directory");
  }//must be terminated

  sd.chdir(tmp_year);

  if (!sd.exists(_month)) {
    if (!sd.mkdir(_month)) Serial.println("cant make nested directory");//terminate
  }

  sd.chdir(_month);

  //some flag should be checked before writing to sdcard
  //no need to do this .... without cycle number filename wont be changed other than tmp so it will be always overwritten
  //which means cycle wasnt normally started or stopped
  //only cycles that start and finish normally will be saved
  //open or make year/month/tmp.txt start writing with /r/n at the end
  switch (process_text(a)) {

    case CYCLE_COMPLETE:
      //sd card close file
      _complete = true;
      char tmp_cycle_number[9];
      memset(tmp_cycle_number, '\0', sizeof(tmp_cycle_number));
      itoa(cycle_number, tmp_cycle_number, 10);
      strcat(tmp_cycle_number, ".txt");

      if (!file.open("tmp.txt", O_WRONLY | O_CREAT | O_APPEND)) Serial.println("cant make file first"); //all wrong returns should
      //terminate the whole program with error code
      else Serial.println("tmp.txt is open");

      file.print(_time);
      file.print("  ");
      file.println(a);
      file.print("\r\n\r\n");

      if (!file.rename(tmp_cycle_number))  Serial.println("cant rename");
      else Serial.println("file renamed");

      file.close();

      sd.remove("tmp.txt");

      my_serial_flush();//to get rid of trailing '\r's
      // no need to touch cycle_stoppped
      scroll_text();
      have_cycle_number = false; //serial is available have to start from beginning

      break;

    case STOPPED://manually
      //sd card close file
      sd.remove("tmp.txt");
      _complete = false;
      char cycle_number_lcd[6];
      memset(cycle_number_lcd, '\0', sizeof(cycle_number_lcd));
      itoa(cycle_number, cycle_number_lcd, 10);
      send_to_lcd("Cycle#", 0, 0, true);
      lcd.print(cycle_number_lcd);
      lcd.setCursor(0, 1);
      lcd.print("  Manually Stopped  ");
      my_serial_flush();//better to flush all serial and stop printing on lcd or writting on sd card
      have_cycle_number = false;
      break;

    default:
      if (!have_cycle_number) {
        send_to_lcd(blank, 0, 0, false);
        send_to_lcd(_time, 0, 0, false);
      }
      send_to_lcd(blank, 0, 1, false);
      send_to_lcd(a, 0, 1, false);

      if (!file.open("tmp.txt", O_WRONLY | O_CREAT | O_APPEND)) Serial.println("cant make file third"); //all wrong returns should
      //terminate the whole program with error code

      file.print(_time);
      file.print("  ");
      file.println(a);
      file.print("\r\n\r\n");
      file.close();
      return true;
      break;
  }

  return false;
}
