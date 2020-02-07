unsigned char bcdToDec(char val) {
  if (val < 0) Serial.println("Timer not ready");
  return TODEC(val);
}
