void my_serial_flush(void) {
  unsigned long _time = 0;
  const unsigned int max_time = 1000;

  _time = millis();

  while (millis() - _time <= max_time) Serial1.read();
 
}
