void listener(char a[]) {

  unsigned int  i = 0;
  unsigned long _time = 0;
  bool flag = false;
  const unsigned int timeout = 500;//from 1ms must be adjusted

  _time = millis();

  do {
    if (Serial1.available()) {
      a[i] = Serial1.read();
      if (a[i] >= 10 && a[i] <= 127) {
        flag = true;
        i == (INPUT_BUFFER_SIZE - 1) ? i-- : i++;
      }
    }
  } while ((a[i-1] != '\r') && (millis() - _time) <= timeout);

///sd card write with '\r' i.e. sd.print("\r\n") added to the end.....decide not to check if newline is needed can be 
//written in client_checker default after each line add /r/n
  if (flag) a[--i] = '\0';

  return;
}
