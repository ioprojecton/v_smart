#define NOT_BUSY() (PORTB&=~(1<<PB4))
#define BUSY() (PORTB|=(1<<PB4))
#define READY_TO_RECEIVE() (PORTB|=(1<<PB3))
#define NOT_READY_TO_RECEIVE() (PORTB&=~(1<<PB3))
#define NO_DATA() (PIND & (1<<PD2))

#define DataPin1 3
#define DataPin2 4
#define DataPin3 5
#define DataPin4 6
#define DataPin5 7
#define DataPin6 8
#define DataPin7 9
#define Datapin8 10

unsigned long current_time = 0;

void setup() {
  // put your setup code here, to run once:
  DDRD = 0;
  DDRD |= (1 << DDD1);
  DDRB = 0;
  DDRB |= (1 << PB3) | (1 << PB4);

  PORTD = 0;
  PORTB = 0;
  PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
  PORTD |= (1 << PD7) | (1 << PD6) | (1 << PD5) | (1 << PD4) | (1 << PD3) | (1 << PD2);

  UBRR0L = 0;
  UCSR0B = (1 << TXEN0);
}

void loop() {
  // put your main code here, to run repeatedly:
  NOT_BUSY();

  READY_TO_RECEIVE();

  current_time = millis();

  while (NO_DATA());

  BUSY();

  if ((millis() - current_time) > 300) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = '\n';
  }

  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = (PIND >> 3) | (PINB << 5);

  NOT_READY_TO_RECEIVE();

  _delay_us(50);
}
