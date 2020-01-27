void get_time(char _second[], char _minute[], char _hour[], char _monthday[], char _month[], char _year[]) {
#define DS1307_ADDRESS 0x68

  Wire.begin();
  //Wire.setClock(400000L);use only withds3232
  Wire.beginTransmission(DS1307_ADDRESS);

  Wire.write(byte(0));
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  itoa(bcdToDec(Wire.read()), _second, 10);
  prefix_shm(_second);

  itoa(bcdToDec(Wire.read()), _minute, 10);
  prefix_shm(_minute);

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

  itoa(md, _monthday, 10);

  unsigned char m = bcdToDec(Wire.read());

  unsigned char y = bcdToDec(Wire.read());

  if (((m == 3 && md >= 14 - (1 + ((y + 2000) * 5 >> 2)) % 7) || (m > 3 && m < 11) || (m == 11 && md < 7 - (1 + (5 * (y + 2000) >> 2)) % 7)) && !_dst) ++hr;
  else EEPROM.put(EEPROM_DST, true);

  if (((m == 11 && md >= 7 - (1 + (5 * (y + 2000) >> 2)) % 7) || (m > 11 && m < 3) || (m == 3 && md < 14 - (1 + ((y + 2000) * 5 >> 2)) % 7)) && !_dst) --hr;
  else EEPROM.put(EEPROM_DST, false);

  itoa(hr, _hour, 10);
  prefix_shm(_hour);
  
  itoa(y, _year, 10);

  const char *p[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

  strcat(_month, p[--m]);

}
