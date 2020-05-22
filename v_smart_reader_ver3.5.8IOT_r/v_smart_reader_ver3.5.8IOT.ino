#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <SdFat.h>
#include <ctype.h>
#include <EEPROM.h>

#ifndef F_CPU
#define F_CPU 96000000UL
#endif

#include <util/delay.h>

#define DEBUG 0
#define _sizeof(x) (unsigned int)(sizeof(x)/sizeof(x[0]))
#define INPUT_BUFFER_SIZE 64
#define TOTAL_CYCLES 1
#define STERILIZING 2
#define NOTHING_USEFUL 3
#define STOPPED 4
#define CYCLE_COMPLETE 5
#define BEGIN 6
#define WIFI_DISCONNECTED 7
#define SETTING_UP_WIFI 10
#define GOT_IP 8
#define RLED 2
#define buttonPin 9
#define ESPIN 5

#define EEPROM_zone 2040
#define chipSelect 10

#define SPI_START 1
#define SPI_END 0

#if DEBUG
#define Serial1 Serial
#endif

struct _time {
  char _second[3];
  char _minute[3];
  char _hour[3];
  char _monthDay[3];
  char _month[4];
  char _year[3];
} ;

bool m11_new = false;

bool _complete = false;
const char *blank = "                    ";
unsigned int eeprom_address = 0;
bool data_log_eeprom = false;
unsigned int cycle_number = 0;
bool have_cycle_number = false;
void client_checker(void);
void listener(char a[]);
unsigned char process_text(char a[]);
void send_to_lcd(const char a[], unsigned char col, unsigned char row, bool option);
void sd_card_init(void);
void my_serial_flush(void);
void scroll_text(void);
unsigned char bcdToDec(char val);
void get_time(struct _time *my_time);
void prefix_shm(char *a);
void print_time(void);
const char* time_zones(unsigned char *u);
void animation(void);
void _spi(bool value);

LiquidCrystal lcd(A7, A6, A9, A8, A3, A2, A1);//
SdFat sd;
SdFile file;

unsigned char current_zone;
bool esp_flag = false;

//////
void setup() {
  EEPROM.get(EEPROM_zone, current_zone);
  Serial1.begin(9600);
  
#if DEBUG
  Serial.begin(115200);
#endif

  Serial3.begin(9600);
  lcd.begin(20, 2);
  pinMode(RLED, OUTPUT);
  pinMode(ESPIN, OUTPUT);
  digitalWrite(ESPIN, HIGH);
  greeting();
  while (!check_sd_card());
  _spi(SPI_END);
}
void loop() {
  if (Serial1.available()) {
    //spi_end and start may need a bit of time for switching from outputs to inputs not to collision with esp pinmodes _delay_ms may be needed;
    _spi(SPI_START);
    client_checker();
    _spi(SPI_END);
  }
  else if (!have_cycle_number) print_time();
  // put your main code here, to run repeatedly:

  if (Serial3.available() && !Serial1.available()) {//midmark data takes priority over esp8266
    _spi(SPI_END); // dont forget to set it back
    //Serial.print("ESP AVAILABLE");
    esp_flag = true;
    client_checker();
    esp_flag = false;
  }
}
