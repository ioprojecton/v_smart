unsigned char bcdToDec(char val) {
  if (val < 0) Serial.println("Timer not ready");
  return val == -1 ? 0 : ((val >> 4) * 10) + (val % 16);

}
