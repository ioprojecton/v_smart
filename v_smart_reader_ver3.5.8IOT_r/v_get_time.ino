void get_time(struct _time *my_time) {
#define DS1307_ADDRESS 0x68

  Wire.begin();

  //#ifdef DS3232
  //Wire.setClock(400000UL);
  //#endif

  Wire.beginTransmission(DS1307_ADDRESS);

  Wire.write(byte(0));
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  itoa(bcdToDec(Wire.read()), my_time->_second, 10);
  prefix_shm(my_time->_second);

  itoa(bcdToDec(Wire.read()), my_time->_minute, 10);
  prefix_shm(my_time->_minute);

  unsigned char hr = bcdToDec(Wire.read());

  switch (current_zone) {

    case 1:
      !hr ? hr = 23 : --hr;
      break;

    case 2:
      !hr ? hr = 22 : (!(hr ^ 1) ? hr = 23 : hr -= 2);
      break;

    case 3:
      !hr ? hr = 23 : (!(hr ^ 1) ? hr = 22 : (!(hr ^ 2) ? hr = 23 : hr -= 3));
      break;

    case 4: case 5:
      !(hr ^ 23) ? hr = 0 : ++hr;
      break;

    default:
      break;
  }


  Wire.read(); //dow

  unsigned char md = bcdToDec(Wire.read());

  itoa(md, my_time->_monthDay, 10);

  unsigned char m = bcdToDec(Wire.read());

  unsigned char y = bcdToDec(Wire.read());

  if ((m == 3 && md >= 14 - (1 + ((y + 2000) * 5 >> 2)) % 7) || (m > 3 && m < 11) || (m == 11 && md < 7 - (1 + (5 * (y + 2000) >> 2)) % 7)) ++hr;

  itoa(hr, my_time->_hour, 10);
  prefix_shm(my_time->_hour);

  itoa(y, my_time->_year, 10);

  const char *p[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

  strcpy(my_time->_month, p[--m]);

  return ;
}
