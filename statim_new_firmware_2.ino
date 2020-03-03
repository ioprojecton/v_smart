#include <ctype.h>
#include <util/delay.h>
#define BUSY() (PORTB|=(1<<PB4))
#define NOT_BUSY() (PORTB&=~(1<<PB4))
#define READY_TO_RECEIVE() (PORTB|=(1<<PB3))
#define NOT_READY_TO_RECEIVE() (PORTB&=~(1<<PB3))
#define NO_DATA() (PIND&(1<<PD2))
#define nStrobe 2
#define Busy 12
#define nAck 11
#define DataPin1 3
#define DataPin2 4
#define DataPin3 5
#define DataPin4 6
#define DataPin5 7
#define DataPin6 8
#define DataPin7 9
#define Datapin8 10
unsigned long current_time;

void setup()
{
  DDRD = 0;
  DDRB = 0;
  PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
  DDRB |= (1 << DDB3) | (1 << DDB4);
  PORTB &= ~(1 << PB5);

  UBRR0L = 25;
  UCSR0B = (1 << TXEN0);
}

void loop()
{


  NOT_BUSY();

  READY_TO_RECEIVE();

  current_time = millis();

  while (NO_DATA());

  BUSY();

  char Char = 0;

  for (unsigned char _position = 0, b = DataPin1; _position < 7 && b <= Datapin8; Char |= (digitalRead(b++) << _position++));

  if ((millis() - current_time) > 300) {
    while (!( UCSR0A & (1 << UDRE0)));
    UDR0 = '\n';
  }

  while (!( UCSR0A & (1 << UDRE0)));
  UDR0 = Char;

  NOT_READY_TO_RECEIVE();

  _delay_us(100);
}