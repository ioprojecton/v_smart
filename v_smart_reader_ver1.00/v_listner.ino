void listener(char a[]) {

  unsigned int  i = 0;
  unsigned long _time = 0;
  bool flag = false;
  const unsigned int timeout = 1000;

  _time = millis();

  do {
    if (Serial1.available()) {
      a[i] = Serial1.read();
      if (a[i] >= 10 && a[i] <= 127) {
        flag = true;
        //Serial.write(a[i]);
        (i == (INPUT_BUFFER_SIZE - 1)) ? i-- : i++;
      }
    }
  } while ((a[i] != '\r') && (millis() - _time) <= timeout);

  if (flag) a[--i] = '\0';

  return;
}
