void animation(void) {

  lcd.createChar(0, (const unsigned char []){B11111,B10000,B10000,B10000,B11111,B00001,B00001,B11111});
  lcd.createChar(1, (const unsigned char []){B10001,B11011,B10101,B10001,B10001,B10001,B10001,B10001});
  lcd.createChar(2, (const unsigned char []){B00100,B01010,B10001,B11111,B10001,B10001,B10001,B10001});
  lcd.createChar(3, (const unsigned char []){B11110,B10001,B10001,B11110,B11000,B10100,B10010,B10001});
  lcd.createChar(4, (const unsigned char []){B11111,B00100,B00100,B00100,B00100,B00100,B00100,B00100});
  lcd.createChar(5, (const unsigned char []){B11111,B10000,B10000,B11111,B10000,B10000,B10000,B11111});
  lcd.createChar(6, (const unsigned char []){B11100,B10010,B10001,B10001,B10001,B10001,B10010,B11100});
  lcd.createChar(7, (const unsigned char []){B11111,B10001,B10101,B10111,B10101,B10001,B11111,B00000});

  lcd.clear();

  lcd.setCursor(9,0);
  lcd.write(byte(0));

  lcd.setCursor(10,0);
  lcd.write(byte(3));
  _delay_ms(750);

  for(unsigned char i=9;i>4;i--){
    lcd.setCursor(i,0);
    lcd.write(32);
    lcd.setCursor(i-1,0);
    lcd.write(byte(0));
    _delay_ms(100);
  }
  _delay_ms(650);

  char b = 5;
  for (unsigned char i = 1; i < 5 && b < 20 ; i++, b++) {
    lcd.setCursor(b, 0);
    lcd.write(byte(i));
    _delay_ms(135);
  }

  lcd.setCursor((++b)++, 0);
  lcd.write(byte(3));
  _delay_ms(135);

  lcd.setCursor(b++, 0);
  lcd.write(byte(5));
  _delay_ms(135);

  lcd.setCursor(b++, 0);
  lcd.write(byte(2));
  _delay_ms(135);

  lcd.setCursor(b++, 0);
  lcd.write(byte(6));
  _delay_ms(135);

  lcd.setCursor(b++, 0);
  lcd.write(byte(5));
  _delay_ms(135);

  lcd.setCursor(b++, 0);
  lcd.write(byte(3));
  _delay_ms(135);

  lcd.setCursor(b, 0);
  lcd.write(byte(7));

  _delay_ms(1500);

  
}
