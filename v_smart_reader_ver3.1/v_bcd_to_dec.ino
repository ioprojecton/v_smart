unsigned char bcdToDec(unsigned char val) {
  return ((val/16*10) + (val%16)); // ((val>>4)*10)+(val&0x7F)
}
