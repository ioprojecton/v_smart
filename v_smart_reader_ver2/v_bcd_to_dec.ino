unsigned char bcdToDec(unsigned char val) {
  return ((val >> 4) * 10) + (val & 0x0F);
}
