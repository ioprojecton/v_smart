#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <SdFat.h>
#include <ctype.h>

#define DEBUG 1
#define _sizeof(x) (unsigned int)(sizeof(x)/sizeof(x[0]))
#define INPUT_BUFFER_SIZE 150
#define TOTAL_CYCLES 1
#define HEATING 2
#define STERILIZING 3
#define MIN_TEMP 4
#define MAX_TEMP 5
#define MIN_PRESS 6
#define MAX_PRESS 7
#define VENTING 8
#define TOTAL_PROCESS_TIME 9
#define DRYING 10
#define NOTHING_USEFUL 11
#define STOPPED 12
#define CYCLE_COMPLETE 13
#define BEGIN 14
#define RLED 2

#if DEBUG
#define Serial1 Serial
#endif

unsigned int cycle_number=0;
bool have_cycle_number=false;
bool client_checker(void);
void listener(char a[]);
byte process_text(char a[]);
void send_to_lcd(const char a[],unsigned char col, unsigned char row,bool option);
void sd_card_init(void);
void send_to_lcd(const char a[], unsigned char col, unsigned char row);
void _delay(const unsigned int delay_time);
void my_serial_flush(void);
void scroll_text(void);
unsigned char bcdToDec(unsigned char val);
void get_time(char _second[], char _minute[], char _hour[], char _monthday[], char _month[], char _year[]);
void prefix_shm(char a[]);

//vars used from original project
LiquidCrystal lcd(A7, A6, A9, A8, A3, A2, A1);
SdFat sd;
SdFile file;
const int chipSelect = 10;
char fileLoc[40];
char dir[10];
char charSerial[24];
bool _complete=false;
//////
void setup() {
  //Serial1.setRX(0);
  //Serial1.setTX(1);
  Serial1.begin(9600);
  Serial.begin(9600);
  lcd.begin(20, 2);
  pinMode(9, INPUT_PULLUP); 
   pinMode(RLED, OUTPUT);
  greeting();
  
  //sd_card_init();
  // put your setup code here, to run once:

}

void loop() {
  if(Serial1.available()) client_checker();
 
  // put your main code here, to run repeatedly:

}
