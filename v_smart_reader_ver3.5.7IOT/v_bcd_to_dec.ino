unsigned char bcdToDec(char val) {
  return val == -1 ? 0 : ((val >> 4) * 10) + (val % 16);

}
