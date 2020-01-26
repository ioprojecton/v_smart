#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <SdFat.h>
#include <ctype.h>
#include <EEPROM.h> 

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

#if DEBUG
#define Serial1 Serial
#endif

bool m11_new=false;
unsigned int EEPROM_zone = 306;
unsigned int EEPROM_DST = 300;
bool _dst = false;
bool _complete = false;
const char *blank = "                    ";
unsigned char eeprom_address = 0;
bool data_log_eeprom = false;
unsigned int cycle_number = 0;
bool have_cycle_number = false;
bool client_checker(void);
void listener(char a[]);
unsigned char process_text(char a[]);
void send_to_lcd(const char a[], unsigned char col, unsigned char row, bool option);
void sd_card_init(void);
void send_to_lcd(const char a[], unsigned char col, unsigned char row);
void _delay(const unsigned int delay_time);
void my_serial_flush(void);
void scroll_text(void);
unsigned char bcdToDec(char val);
void get_time(char _second[], char _minute[], char _hour[], char _monthday[], char _month[], char _year[]);
void prefix_shm(char a[]);
void print_time(void);
const char* time_zones(unsigned int *u);
void animation(void);

LiquidCrystal lcd(A7, A6, A9, A8, A3, A2, A1);//
SdFat sd;
SdFile file;
const unsigned char chipSelect = 10;
unsigned int current_zone;

//////
void setup() {
  EEPROM.get(EEPROM_zone, current_zone);
  EEPROM.get(EEPROM_DST, _dst);
  Serial1.begin(9600);
  Serial.begin(9600);
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
