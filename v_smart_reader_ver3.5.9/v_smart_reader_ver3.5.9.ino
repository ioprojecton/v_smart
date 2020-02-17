#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <SdFat.h>
#include <ctype.h>
#include <EEPROM.h>
#ifndef F_CPU
#define F_CPU 96000000UL //define CPU clock
#endif
#include <util/delay.h>

#define DEBUG 1
#define _sizeof(x) (unsigned int)(sizeof(x)/sizeof(x[0]))
#define INPUT_BUFFER_SIZE 64
#define TOTAL_CYCLES 1
#define STERILIZING 2
#define NOTHING_USEFUL 3
#define STOPPED 4
#define CYCLE_COMPLETE 5
#define BEGIN 6
#define RLED 2
#define buttonPin 9
#define VENTING_CHAMBER 7

#if DEBUG
#define Serial1 Serial
#endif

struct _time{
  char _second[3];
  char _minute[3];
  char _hour[3];
  char _monthDay[3];
  char _month[4];
  char _year[3];
} ;

bool m11_new = false;
unsigned int EEPROM_zone = 306;
unsigned int EEPROM_DST = 300;
bool _dst = false;
bool _complete = false;
const char *blank = "                    ";
unsigned char eeprom_address = 0;
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

LiquidCrystal lcd(A7, A6, A9, A8, A3, A2, A1);//
SdFat sd;
SdFile file;
const unsigned char chipSelect = 10;
unsigned char current_zone;

//////
void setup() {
  EEPROM.get(EEPROM_zone, current_zone);
  EEPROM.get(EEPROM_DST, _dst);
  Serial1.begin(9600);
  lcd.begin(20, 2);
  pinMode(RLED, OUTPUT);
  greeting();
  while (!check_sd_card());

}
void loop() {
  if (Serial1.available()) client_checker();
  else if (!have_cycle_number) print_time();
  // put your main code here, to run repeatedly:

}
