void greeting(void) {
  animation();
  send_to_lcd(" Datalogger V4.9-M  ", 0, 1, false);
  _delay(2000);

  send_to_lcd(time_zones(&current_zone), 0, 0, true);
  send_to_lcd("PRESS TO CHANGE", 2, 1, false);

  pinMode(buttonPin, INPUT_PULLUP);
  bool m_state = !digitalRead(buttonPin);
  unsigned long m_time = millis();
  bool m_lastState = m_state;
  bool m_changed = false;
  unsigned long m_lastChange = m_time;
  const unsigned char m_dbTime = 25;

  unsigned long _time = millis();
  while (millis() - _time <= 5000) {
    bool pinVal = !digitalRead(buttonPin);
    unsigned long ms = millis();
    if (ms - m_lastChange < m_dbTime) m_changed = false;

    else
    {
      m_lastState = m_state;
      m_state = pinVal;
      m_changed = (m_state != m_lastState);
      if (m_changed) m_lastChange = ms;
    }

    m_time = ms;

    if (m_state && m_changed) {
      if (current_zone + 1 > 5) current_zone = 0;
      else ++current_zone;
      send_to_lcd(time_zones(&current_zone), 0, 0, true);
      send_to_lcd("       SET     ", 0, 1, false);
      _time = millis();
    }
  }
  send_to_lcd(blank, 0, 1, false);
}
