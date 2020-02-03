void spi_end(void) {
  SPI.end();
  pinMode(chipSelect, INPUT);
  pinMode(13, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  digitalWrite(ESPIN, LOW);
}
