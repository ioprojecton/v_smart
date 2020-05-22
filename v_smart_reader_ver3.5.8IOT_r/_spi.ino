void _spi(bool value){
  value?digitalWrite(ESPIN, HIGH):SPI.end();
  pinMode(chipSelect, value?OUTPUT:INPUT);
  pinMode(13, value?OUTPUT:INPUT);
  pinMode(12, value?OUTPUT:INPUT);
  pinMode(11, value?OUTPUT:INPUT);
  if(!value) digitalWrite(ESPIN, LOW);
  return;
}
