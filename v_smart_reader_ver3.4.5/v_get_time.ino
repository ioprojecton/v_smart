void get_time(char _second[], char _minute[], char _hour[], char _monthday[], char _month[], char _year[]) {
#define DS1307_ADDRESS 0x68

  Wire.begin();
  //Wire.setClock(400000L);use only withds3232
  Wire.beginTransmission(DS1307_ADDRESS);

  Wire.write(byte(0));
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  itoa(bcdToDec(Wire.read()), _second, 10);

  itoa(bcdToDec(Wire.read()), _minute, 10);

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

  !(m ^ 3) && md >= 14 - (1 + ((y + 2000) * 5 >> 2)) % 7 && !_dst ? ++hr : EEPROM.put(EEPROM_DST, true);

  !(m ^ 11) && md >= 7 - (1 + (5 * (y + 2000) >> 2)) % 7 && _dst ? --hr : EEPROM.put(EEPROM_DST, false);

  itoa(hr, _hour, 10);

  itoa(y, _year, 10);

  switch (m) {
    case 1:
      strcat(_month, "JAN");
      break;

    case 2:
      strcat(_month, "FEB");
      break;

    case 3:
      strcat(_month, "MAR");
      break;

    case 4:
      strcat(_month, "APR");
      break;

    case 5:
      strcat(_month, "MAY");
      break;

    case 6:
      strcat(_month, "JUN");
      break;

    case 7:
      strcat(_month, "JUL");
      break;

    case 8:
      strcat(_month, "AUG");
      break;

    case 9:
      strcat(_month, "SEP");
      break;

    case 10:
      strcat(_month, "OCT");
      break;

    case 11:
      strcat(_month, "NOV");
      break;

    case 12:
      strcat(_month, "DEC");
      break;

    default:
      break;
  }

  //itoa(bcdToDec(Wire.read()), _year, 10);

  prefix_shm(_second);
  prefix_shm(_minute);
  prefix_shm(_hour);


}
