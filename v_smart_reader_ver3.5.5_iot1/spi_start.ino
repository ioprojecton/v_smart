void spi_start(void) {
  digitalWrite(ESPIN, HIGH);
  pinMode(chipSelect, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}
