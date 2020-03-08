#define NOT_BUSY() (PORTB&=~(_BV(PB4)))
#define BUSY() (PORTB|=_BV(PB4))
#define READY_TO_RECEIVE() (PORTB|=_BV(PB3))
#define NOT_READY_TO_RECEIVE() (PORTB&=~(_BV(PB3)))

unsigned long current_time = 0;

void setup() {
  // put your setup code here, to run once:
  DDRD = 0;
  DDRD |= _BV(DDD1);
  DDRB = 0;
  DDRB |= _BV(DDB3) | _BV(DDB4);

  PORTD = 0;
  PORTB = 0;
  PORTB |= _BV(PB0) | _BV(PB1) | _BV(PB2);
  PORTD |= _BV(PD7) | _BV(PD6) | _BV(PD5) | _BV(PD4) | _BV(PD3) | _BV(PD2);

  UBRR0L = 0;
  UCSR0B = _BV(TXEN0);
}

void loop() {
  // put your main code here, to run repeatedly:
  NOT_BUSY();

  READY_TO_RECEIVE();

  current_time = millis();

  loop_until_bit_is_clear(PIND,PD2);

  BUSY();

  if ((millis() - current_time) > 300) {
    loop_until_bit_is_set(UCSR0A,UDRE0);
    UDR0 = '\n';
  }

  loop_until_bit_is_set(UCSR0A,UDRE0);
  
  UDR0 = (PIND >> 3) | (PINB << 5);

  NOT_READY_TO_RECEIVE();

  _delay_us(50);
}
