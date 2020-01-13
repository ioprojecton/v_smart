void get_time(char _second[], char _minute[], char _hour[], char _monthday[], char _month[], char _year[]) {
#define DS1307_ADDRESS 1101000

  Wire.begin();
  Wire.setClock(400000L);
  Wire.beginTransmission(DS1307_ADDRESS);

  const unsigned char zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  itoa(bcdToDec(Wire.read()), _second, 10);
  itoa(bcdToDec(Wire.read()), _minute, 10);
  itoa(bcdToDec(Wire.read() & 0b111111), _hour, 10);
  Wire.read();
  itoa(bcdToDec(Wire.read()), _monthday, 10);
  itoa(bcdToDec(Wire.read()), _month, 10);
  itoa(bcdToDec(Wire.read()), _year, 10);

  prefix_shm(_second);
  prefix_shm(_minute);
  prefix_shm(_hour);

}
