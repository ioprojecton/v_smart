void greeting(void) {

  send_to_lcd("     Smartreader_V  ", 0, 0, true);

  send_to_lcd(" Datalogger V4.9-M  ", 0, 1, false);

 delay(2000); // must write smaller delay function!
}
