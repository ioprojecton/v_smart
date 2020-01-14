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

  listener(a);

  switch (process_text(a)) {
    
    case TOTAL_CYCLES:
      send_to_lcd("     Cycle#", 0, 0, true);
      char cycle_number_ascii[6];
      memset(cycle_number_ascii, '\0', sizeof(cycle_number_ascii));//filling it with zero
      for (unsigned char i = 0, b = 0; i < strlen(a); i++) {
        if (isdigit(a[i])) {
          cycle_number_ascii[b++] = a[i];
          lcd.write(a[i]);
        }
      }
      cycle_number = (unsigned int)atoi(cycle_number_ascii);

      have_cycle_number = true;

      ///sdcard make newfile with cycle_num and write a[]
      return true;
      break;
    //...............
    //..............
    //............

    case CYCLE_COMPLETE:
      //sd card close file
      _complete = true;
      my_serial_flush();//to get rid of trailing '\r's
      // no need to touch cycle_stoppped
      scroll_text();
      have_cycle_number = false; //serial is available have to start from beginning

      break;

    case STOPPED://manually
      //sd card close file
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


      //write to sd card;
      return true;
      break;
  }

  return false;
}
