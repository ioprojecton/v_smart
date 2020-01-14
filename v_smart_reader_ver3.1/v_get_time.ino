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
  itoa(bcdToDec(Wire.read()), _hour, 10);
  Wire.read(); //dow
  itoa(bcdToDec(Wire.read()), _monthday, 10);

  unsigned char m=bcdToDec(Wire.read());

  switch(m){
    case 1:
    strcat(_month,"JAN");
    break;

    case 2:
    strcat(_month,"FEB");
    break;

    case 3:
    strcat(_month,"MAR");
    break;

    case 4:
    strcat(_month,"APR");
    break;

    case 5:
    strcat(_month,"MAY");
    break;

    case 6:
    strcat(_month,"JUN");
    break;

    case 7:
    strcat(_month,"JUL");
    break;

    case 8:
    strcat(_month,"AUG");
    break;

    case 9:
    strcat(_month,"SEP");
    break;

    case 10:
    strcat(_month,"OCT");
    break;

    case 11:
    strcat(_month,"NOV");
    break;

    case 12:
    strcat(_month,"DEC");
    break;

    default:
    break;
  }
  
  itoa(bcdToDec(Wire.read()), _year, 10);

  prefix_shm(_second);
  prefix_shm(_minute);
  prefix_shm(_hour);


}

/*//debug
unsigned char s=bcdToDec(Wire.read());
unsigned char m=bcdToDec(Wire.read());
unsigned char h=bcdToDec(Wire.read());
bcdToDec(Wire.read());
unsigned char md=bcdToDec(Wire.read());
unsigned char mo=bcdToDec(Wire.read());
unsigned char y=bcdToDec(Wire.read());

Serial.print(h);
Serial.write(':');
Serial.print(m);
Serial.write(':');
Serial.print(s);
Serial.write(':');
Serial.print(md);
Serial.write(':');
Serial.print(mo);
Serial.write(':');
Serial.print(y);
*/
