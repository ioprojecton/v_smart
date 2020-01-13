bool client_checker(void) {
  char a[INPUT_BUFFER_SIZE];
  memset(a, 0, sizeof(a));
  const char *blank = "                    ";

  listener(a);
  switch (process_text(a)) {

    case TOTAL_CYCLES:
      send_to_lcd("     Cycle#", 0, 0, true);
      char cycle_number_ascii[6];
      memset(cycle_number_ascii, '\0', sizeof(cycle_number_ascii));
      for (unsigned char i = 0, b = 0; i < strlen(a); i++) {
        if (isdigit(a[i])) {
          cycle_number_ascii[b++] = a[i];
          lcd.write(a[i]);
        }
      }
      cycle_number = (unsigned int)atoi(cycle_number_ascii);

      cycle_display = true;
      return true;
      break;
    //...............
    //..............
    //............

    case STOPPED://manually
      cycle_display = !cycle_display;
      char cycle_number_lcd[6];
      memset(cycle_number_lcd, '\0', sizeof(cycle_number_lcd));
      itoa(cycle_number, cycle_number_lcd, 10);
      send_to_lcd("Cycle#", 0, 0, true);
      lcd.print(cycle_number_lcd);
      lcd.write(' ');
      lcd.print("Stopped");
      cycle_display = !cycle_display;
      break;

    default:
      if (cycle_display) {
        send_to_lcd(blank, 0, 1, false);
        send_to_lcd(a, 0, 1, false);
      }
      else send_to_lcd(a, 0, 0, true);
      //write to sd card;
      return true;
      break;
  }

  return false;
}
